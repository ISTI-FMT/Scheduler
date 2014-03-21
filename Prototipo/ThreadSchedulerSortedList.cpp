#include "ThreadSchedulerSortedList.h"


using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Runtime::InteropServices;
using namespace System::Globalization;
using namespace System::Xml;
using namespace System::Configuration;


#define TRACE
#define UNIFI

ThreadSchedulerSortedList::ThreadSchedulerSortedList(void)
{
}


ThreadSchedulerSortedList::ThreadSchedulerSortedList(EventQueue<StateCDB^> ^E0,EventQueue<StateCDB^>^E1,EventQueue<physicalTrain^>^E2, TabellaOrario ^tabo, TabellaStazioni ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w,ManagerStatoLineaATC ^manATC,ManagerStatoLineaIXL ^manIXL, ConfigurazioneVelocita ^cvel, AreeCritiche^ aCritiche)
{

	EQueueIXL=E0;
	EQueueATC=E1;
	EQueueATO=E2;

	mapTrenoLogFisico=mapTreno;
	tabOrario=tabo;
	tabItinerari=tabi;
	confVelocita=cvel;
	areeCritiche = aCritiche;
	wdogs=w;
	managerATC=manATC;
	managerIXL=manIXL;

	try {

		ipixl = ConfigurationSettings::AppSettings["ip_IXL"] != nullptr ? ConfigurationSettings::AppSettings["ip_IXL"]->ToString() : "127.0.0.1";
		// Console::WriteLine("IP IXL ",ipixl);
	} catch(System::Configuration::ConfigurationException  ^error){
		ipixl="127.0.0.1";

	}
	Console::WriteLine("IP IXL {0}",ipixl);
	RaccoltaTrenoRequestCDB  = gcnew Dictionary<Train^,List<int>^> ();
	EQueueCambioOrario = gcnew EventQueue<List<Fermata^>^>();
	_shouldStop=false;
	//ListSortedTrains = gcnew System::Collections::Generic::SortedList<KeyListTrain^, Train^>();
	timeRicIXL;

	ListTrainModel ^model = gcnew ListTrainModel();

	view = gcnew Prototipo::ListTrainView(tabItinerari,EQueueCambioOrario);
	model->Subscribe(view);
	view->AddModel(model);
	controlListtrain = gcnew ControllerListTrain(model);

	//Application::Run(view);
	view->Visible=true;



}



void ThreadSchedulerSortedList::Schedule(){
	try
	{
		Console::WriteLine("Hi!! I'm Schedule");
		//inizializzazione ATS
		Init();



		DateTime time=DateTime::Now;


		while(!_shouldStop){
			//dormi un po 100  millisecondi cosi da eseguire un ciclo ogni 100 ms
			//controlListtrain->Sort();
			Thread::Sleep(100);
			wdogs->onNext();
			ControllaMSG_ATO();
			ControllaMSG_IXL();
			ControllaEventiCambioOrario();

			for each (Train^ Train in controlListtrain->getListTrain())
			{
				switch (Train->getStatoTreno())
				{
				case StateTrain::PRONTO:{

					DateTime mezzanotte = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
						TimeSpan ^oraattuale =  (DateTime::Now - mezzanotte);
						int tempo = (int)oraattuale->TotalSeconds/30;
						int  costante= 3;
						int resutl = ((int)Train->getOrarioPartenza())-costante;

						List<Fermata^> ^listaitinerari = tabOrario->getItinerariFor(Train->getTRN());
						int prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(listaitinerari[0]->getIdStazione(),listaitinerari[0]->getIditinerarioUscita());

						int idTRenoCDBPrecIT = managerATC->getCDB(prevfirstcdbu)->getNID_OPERATIONAL();
						int nid_engineTRenoCDBPrecIT = managerATC->getCDB(prevfirstcdbu)->getNID_ENGINE();

						// controllo posizione e tempo 
						if(((idTRenoCDBPrecIT==Train->getTRN())|nid_engineTRenoCDBPrecIT==Train->getPhysicalTrain()->getEngineNumber())& (resutl<=tempo | true)){//&

							if (areeCritiche->richiestaCdb(prevfirstcdbu, Train->getTRN()))
							{
								Train->setStatoTreno(StateTrain::USCITASTAZIONE);
							}
						}

					break;}
				case StateTrain::USCITASTAZIONE:{

					//itinerario uscita
					KeyValuePair<int, int> ^itistazione = Train->getStazioneItinerario();
					int itinUscita = itistazione->Value;
					int idstazione = itistazione->Key;

					int resultprecCdbU = tabItinerari->get_CdbPrecItinerario(idstazione,itinUscita);
					int nextCdbU = tabItinerari->get_CdbSuccItinerario(idstazione,itinUscita);

					//se esiste un itinerario di uscita
					if(itinUscita>0){

						DateTime mezzanotte = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
						TimeSpan ^oraattuale =  (DateTime::Now - mezzanotte);
						int tempo = (int)oraattuale->TotalSeconds/30;
						int  costante= 3;
						int resutl = ((int)Train->getOrarioPartenza())-costante;

						int idTRenoCDBPrecIT = managerATC->getCDB(resultprecCdbU)->getNID_OPERATIONAL();
						int nid_engineTRenoCDBPrecIT = managerATC->getCDB(resultprecCdbU)->getNID_ENGINE();
						// controllo posizione e tempo 
						if(((idTRenoCDBPrecIT==Train->getTRN())|nid_engineTRenoCDBPrecIT==Train->getPhysicalTrain()->getEngineNumber())& (resutl<=tempo | true)){//&
							//	( statocdbuscitaitinerario==typeStateCDB::cdbLibero | true)){

							//Controllo che l'acquisizione del prossimo cdb non crei deadlock
							List<int> ^cdbItinerario =  tabItinerari->get_Cdb_Itinerario(idstazione,itinUscita);
							int lastcdbiti = cdbItinerario[cdbItinerario->Count-1];
							if (areeCritiche->richiestaCdb(lastcdbiti, Train->getTRN()))
							{
								if(!RaccoltaTrenoRequestCDB->ContainsKey(Train))
								{
									List<int>^cdbricPrenotazione = RequestItinerarioIXL(idstazione,itinUscita);
									if(cdbricPrenotazione!=nullptr){
										RaccoltaTrenoRequestCDB->Add(Train,cdbricPrenotazione);
									}
								}
							}
						}
					}
					else
					{
						Train->setStatoTreno(StateTrain::ENTRATASTAZIONE);
						controlListtrain->OnNextIt(Train);
					}
					break;
									}
				case StateTrain::ENTRATASTAZIONE: {


					//itinerario uscita
					KeyValuePair<int, int> ^itistazione = Train->getStazioneItinerario();

					int initEntrata = itistazione->Value;
					int idstazione = itistazione->Key;
					//se esiste un itinerario di entrata
					if(initEntrata>0){
						int resultprecE = tabItinerari->get_CdbPrecItinerario(idstazione,initEntrata);
						int nextCdbE = tabItinerari->get_CdbSuccItinerario(idstazione,initEntrata);
						Event<StateCDB^> ^eventATC = EQueueATC->getEvent();

						if(eventATC!=nullptr){
							int idTRenoCDBPrecIT = managerATC->getCDB(resultprecE)->getNID_OPERATIONAL();
							int nid_engineTRenoCDBPrecIT = managerATC->getCDB(resultprecE)->getNID_ENGINE();
							//se il treno si trova sul cdb giusto

							if(((eventATC->getEvent()->getNID_CDB()==resultprecE) & (eventATC->getEvent()->getNID_OPERATIONAL()==Train->getTRN() | eventATC->getEvent()->getNID_ENGINE()==Train->getPhysicalTrain()->getEngineNumber())) |((
								idTRenoCDBPrecIT==Train->getTRN() )|nid_engineTRenoCDBPrecIT==Train->getPhysicalTrain()->getEngineNumber())){
									//se l'itinerario è libero
									//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
									//che riporti il cambiamento dello stato dell'itinerario

									//Controllo che l'acquisizione del prossimo cdb non crei deadlock
									List<int> ^cdbItinerario =  tabItinerari->get_Cdb_Itinerario(idstazione,initEntrata);
									int lastcdbiti = cdbItinerario[cdbItinerario->Count-1];
									if (areeCritiche->richiestaCdb(lastcdbiti, Train->getTRN()))
									{
										if(!RaccoltaTrenoRequestCDB->ContainsKey(Train)){

											List<int>^cdbricPrenotazione = RequestItinerarioIXL(idstazione,initEntrata);
											if(cdbricPrenotazione!=nullptr){
												RaccoltaTrenoRequestCDB->Add(Train,cdbricPrenotazione);
											}
										}
									}

							}
						}else{
							//se il treno si trova sul cdb giusto
							// messo a true per fare test
							int nid_engineTRenoCDBPrecIT = managerATC->getCDB(resultprecE)->getNID_ENGINE();
							if(managerATC->getCDB(resultprecE)->getNID_OPERATIONAL()==Train->getTRN()|nid_engineTRenoCDBPrecIT==Train->getPhysicalTrain()->getEngineNumber()){

								List<int> ^cdbItinerario =  tabItinerari->get_Cdb_Itinerario(idstazione,initEntrata);
								int lastcdbiti = cdbItinerario[cdbItinerario->Count-1];
								//Controllo che l'acquisizione del prossimo cdb non crei deadlock
								if (areeCritiche->richiestaCdb(lastcdbiti, Train->getTRN()))
								{
									//se l'itinerario è libero
									//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
									//che riporti il cambiamento dello stato dell'itinerario
									if(!RaccoltaTrenoRequestCDB->ContainsKey(Train)){
										List<int>^cdbricPrenotazione = RequestItinerarioIXL(idstazione,initEntrata);

										if(cdbricPrenotazione!=nullptr){
											RaccoltaTrenoRequestCDB->Add(Train,cdbricPrenotazione);
										}
									}
								}
							}
						}
					}else{
						Train->setStatoTreno(StateTrain::USCITASTAZIONE);
						controlListtrain->OnNextIt(Train);
					}




					break;
									  }
				case StateTrain::NONPRONTO:
					break;
				case StateTrain::TERMINATO:
					break;
				default:
					break;
				}
			}
		}
	}
	catch ( ThreadAbortException^ abortException ) 
	{
#ifdef TRACE
		Logger::Exception(abortException,"ThreadSchedule");  
#endif // TRACE
		Console::WriteLine( dynamic_cast<String^>(abortException->ExceptionState) );
	}
}
void  ThreadSchedulerSortedList::ControllaEventiCambioOrario(){
	Event<List<Fermata^>^> ^eventoOrario= EQueueCambioOrario->getEvent();
	if(eventoOrario!=nullptr){

		Console::WriteLine("ciao");
		Train ^train = eventoOrario->getEventAttribute();
		List<Fermata^> ^nuoviorari = eventoOrario->getEvent();


		//invia messaggio all'ato
		StateObject ^inviato =	SendUpdateMissionATO(train->getTRN(),train->getPhysicalTrain(),nuoviorari);
		//aspetta ack
		DateTime time=DateTime::Now;
		TimeSpan ^sec =  TimeSpan::Zero;

		while ((inviato->fine!=1) & (sec->TotalSeconds<10)){
			sec = DateTime::Now - time;

			//reinvia


		}
		if(inviato->fine==1){
			//aggiorna modello se ack è giusto
			controlListtrain->AggiornaOrario(train, nuoviorari);
		}

	}
}

void ThreadSchedulerSortedList::ControllaMSG_IXL(){
	Event<StateCDB^> ^eventoIXL;
	eventoIXL = EQueueIXL->getEvent();
	if(eventoIXL!=nullptr){
		StateCDB ^eventocambiostatocdb = eventoIXL->getEvent();
		if(eventocambiostatocdb->getQ_STATOCDB()==(int)QStateCDB::cdbImpegnato ){
			List<Train^> ^elemetidaeliminare = gcnew List<Train^>();
			for each (KeyValuePair<Train^,List<int>^> ^kvpair in RaccoltaTrenoRequestCDB)
			{
				if(kvpair->Value->Contains(eventocambiostatocdb->getNID_CDB())){
					kvpair->Value->Remove(eventocambiostatocdb->getNID_CDB());
				}
				if(kvpair->Value->Count==0){
					elemetidaeliminare->Add(kvpair->Key);
					controlListtrain->OnNextIt(kvpair->Key);
				}

			}
			for each (Train ^var in elemetidaeliminare)
			{
				RaccoltaTrenoRequestCDB->Remove(var);
			}
		}
	}
}

void ThreadSchedulerSortedList::ControllaMSG_ATO(){
	DateTime time=DateTime::Now;

	StateObject ^inviato;
	// aspetta che si presenti un treno
	Event<physicalTrain^> ^eventoATO = EQueueATO->getEvent();
	if(eventoATO!=nullptr){
		physicalTrain ^phisical = eventoATO->getEvent();
		int enginenumber = phisical->getEngineNumber();
		Console::WriteLine("Si è presentato il treno {0}",enginenumber);

		// se trovi che ha numero logico nella mappa mapTrenoLogFisico 
		if(mapTrenoLogFisico->get_Map()->ContainsKey(enginenumber)){
			TrenoFisicoLogico ^infotrenofisico = mapTrenoLogFisico->get_Map()[enginenumber];
			int trn = infotrenofisico->getIdTrenoLogico(0);
			int lastpos =infotrenofisico->getCDBLastPosition();

			// cerchi se c'è una missione per lui nella tabella orario
			if((tabOrario->get_TabellaOrario()->ContainsKey(trn)) & (trn>0)){
				//trova gli itinerari  del treno
				List<Fermata^> ^listaitinerari = tabOrario->getItinerariFor(trn);
				int prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(listaitinerari[0]->getIdStazione(),listaitinerari[0]->getIditinerarioUscita());
				// cerca se si trova nella stazione in cui deve partire
				if(lastpos==prevfirstcdbu){


					//se il treno si trova sul cdb giusto
				//	if(((managerATC->getCDB(prevfirstcdbu)->getNID_OPERATIONAL()==trn)|managerATC->getCDB(prevfirstcdbu)->getNID_ENGINE()==enginenumber)|true){

						// gli assegni TRN e MISSION
						if(inviato==nullptr){
							Console::WriteLine("Il treno {0} si trova al posto giusto per partire e gli invio WAKE-UP, TRN={1} e MISSION",enginenumber,trn);
							inviato = InizializzeATO(trn,phisical);
							time=DateTime::Now;
						}
						TimeSpan ^sec = TimeSpan::Zero; 
						while ((inviato->fine!=1) & (sec->TotalSeconds<20)){
							//aspetta un po
							sec = DateTime::Now - time;
							if(sec->TotalSeconds>20){
								//riinvia
								inviato->fine=0;
								if(inviato->workSocket!=nullptr){
									inviato->workSocket->Close();
								}
								inviato = InizializzeATO(trn,phisical);
								time=DateTime::Now;
								Console::WriteLine(time);
								Console::WriteLine("Il treno {0} non ha risposto con l'ack all'assegnazione della missione",enginenumber);
							}


						}
						if(inviato->fine==1){
							//Creo il treno
							Console::WriteLine("ok {0}",listaitinerari[0]->getOrarioPartenza());

							List<Fermata^> ^listafermate = tabOrario->getFermateFor(trn);
							int priorita = 1;
							Train ^treno = gcnew Train(priorita,trn,phisical,listafermate);
							//Creo KeyListTrain

							//KeyListTrain ^key = gcnew KeyListTrain(priorita,trn,enginenumber);
							//ListSortedTrains->Add(key,treno);
							controlListtrain->OnSetTrain(treno);
						}

					//}
				}
			}
		}




	}
}


void ThreadSchedulerSortedList::RequestStop()
{
	view->RequestStop();
	_shouldStop = true;

}



void ThreadSchedulerSortedList::Init(){

	Console::WriteLine("Inizio Inizializzazione dello Scheduler");
	//TODO: in questa fase ad es. controllare che lo stato di tutti i cdb proveniente dall'IXL sia consistente
	Console::WriteLine("Fine Inizializzazione dello Scheduler");



}


//controlla che funzioni sempre sembra che fai delle richieste e non ci siano le condizioni
bool ThreadSchedulerSortedList::controllacdb(List<int>^lcdb){
	bool res=true;
	for each (int cdb in lcdb)
	{
		StateCDB ^statocorrentecdb = managerIXL->StatoCDB(cdb);
		if(statocorrentecdb!=nullptr){
			if(statocorrentecdb->getQ_STATOCDB()!=(int)QStateCDB::cdbLibero){
				return false;
			}
		}else{
			return false;
		}
		if(RaccoltaTrenoRequestCDB!=nullptr){
			for each (KeyValuePair<Train^,List<int>^> ^kvpair in RaccoltaTrenoRequestCDB)
			{
				if(kvpair->Value->Contains(cdb)){
					return false;
				}
			}

		}
	}

	return res;
}


void ThreadSchedulerSortedList::Connect(EndPoint ^remoteEP, Socket ^client) {
	client->BeginConnect(remoteEP, 
		gcnew AsyncCallback(ConnectCallbackMethod), client );
	mre->WaitOne();

}

void ThreadSchedulerSortedList::ConnectCallbackMethod(IAsyncResult ^ar) {
	try {
		// Retrieve the socket from the state object.
		Socket ^client = (Socket^) ar->AsyncState;

		// Complete the connection.
		client->EndConnect(ar);

		Console::WriteLine("Socket connected to {0}",  client->RemoteEndPoint->ToString());

		mre->Set();
	} catch (Exception ^e) {
		Console::WriteLine(e->ToString());
		mre->Set();
	}
}


void ThreadSchedulerSortedList::Send(Socket ^client, array<Byte> ^data){
	client->BeginSend(data, 0, data->Length,System::Net::Sockets::SocketFlags::None,
		gcnew AsyncCallback(SendCallbackMethod), client);

}
void ThreadSchedulerSortedList::SendCallbackMethod(IAsyncResult ^ar){
	try {
		// Retrieve the socket from the state object.
		Socket ^client = (Socket^) ar->AsyncState;

		// Complete sending the data to the remote device.
		int bytesSent = client->EndSend(ar);
		Console::WriteLine("Sent {0} bytes to server.", bytesSent);

		// Signal that all bytes have been sent.
		//sendDone.Set();
	} catch (Exception ^e) {
		Console::WriteLine(e->ToString());
	}
}

StateObject ^ThreadSchedulerSortedList::SendUpdateMissionATO(int trn,physicalTrain ^Treno,List<Fermata^> ^stops){
	try
	{

		Messaggi ^missionPlanPkt = gcnew Messaggi(MessageID::MissionPlan);
		//missionPlanPkt->get_pacchettoMissionData()->setNID_PACKET(160);


		//tabOrario->setMissionPlanMessage(trn, missionPlanPkt->get_pacchettoMissionData(), confVelocita->getProfiloVelocita(trn));


		tabOrario->createMissionPlanMsg(trn, missionPlanPkt->get_pacchettoMissionData(), confVelocita->getProfiloVelocita(trn),stops);

		// Buffer for reading data
		array<Byte>^bytes_buffer3 = missionPlanPkt->serialize();

		// Creates the Socket to send data over a TCP connection.
		Socket ^sock = gcnew Socket( System::Net::Sockets::AddressFamily::InterNetwork,System::Net::Sockets::SocketType::Stream,System::Net::Sockets::ProtocolType::Tcp );
#ifdef UNIFI
		sock->SendBufferSize = 0;  
#endif // UNIFI

		String ^IP = gcnew String(Treno->getIpAddress());
		IPEndPoint ^lep = gcnew IPEndPoint(IPAddress::Parse(IP), Treno->getTcpPort());

		//Connect(lep,sock);
		//Send(sock,bytes_buffer3);
		sock->Connect(IP, Treno->getTcpPort());
		sock->Send(bytes_buffer3,bytes_buffer3->Length, System::Net::Sockets::SocketFlags::None);
#ifdef TRACE

		Logger::Info(missionPlanPkt->getNID_MESSAGE(),"ATS->ATO",IP->ToString(),missionPlanPkt->getSize(),BitConverter::ToString(bytes_buffer3),"ThreadSchedulerTrain::MissionPlan");

#endif // TRACE

		StateObject^ so2 = gcnew StateObject(Treno->getEngineNumber());
		so2->workSocket = sock;
		so2->fine=-1;
		sock->BeginReceive( so2->buffer, 0, 17,System::Net::Sockets::SocketFlags::Peek, gcnew AsyncCallback( &ThreadSchedulerSortedList::ReceiveCallback ), so2 );


		return so2;
	}
	catch ( Exception^ e ) 
	{
		Console::WriteLine( "SocketException: {0}", e->Message );
#ifdef TRACE
		Logger::Exception(e,"ThreadSchedulerTrain::SendTCPMsg");  
#endif // TRACE
		StateObject^ so2 = gcnew StateObject(Treno->getEngineNumber());

		return so2;
	}
}

/*void ThreadSchedulerSortedList::setMissionPlanMsg(int TRN, pacchettoMissionData ^pkt, List<ProfiloVelocita^>^pvel, List<Fermata^> ^stops)
{


// se il teno esiste
if(stops!=nullptr)
{
//Todo: V_mission D_mission tratte
if(pvel!=nullptr){
pkt->setPV(pvel);
pkt->setN_ITER1(pvel->Count-1);
}else{
pkt->setPV(gcnew ProfiloVelocita);
pkt->setN_ITER1(0);
}
// -1 perchè la prima fermata non viene considerata negli N_ITER
pkt->setN_ITER2((stops->Count) - 1);
int i=0;
for each (Fermata ^stop in stops)
{
Mission ^mission= gcnew Mission();
mission->setQ_DOORS(stop->getLatoAperturaPorte());

int orarioPartenza = (int)stop->getOrarioPartenza();

mission->setT_START_TIME(orarioPartenza);
mission->setT_DOORS_TIME( (int )stop->gettempoMinimoAperturaPorte());

if(tabItinerari!=nullptr ){
if(stop->getIditinerarioEntrata()!=0){
lrbg ^infobalise = tabItinerari->get_infobalise(stop->getIdStazione(),stop->getIditinerarioEntrata());
if(infobalise!=nullptr){
mission->setNID_LRGB(infobalise->nid_lrgb);
mission->setD_STOP(infobalise->d_stop);
}
}
if(i==0){
lrbg ^infobalise = tabItinerari->get_infobalise(stop->getIdStazione(),stop->getIditinerarioUscita());
if(infobalise!=nullptr){

mission->setNID_LRGB(infobalise->nid_lrgb);
mission->setD_STOP(infobalise->d_stop);
}
}

}
i++;
pkt->setMission(mission);



}
}
}*/

StateObject ^ThreadSchedulerSortedList::InizializzeATO(int trn, physicalTrain ^Treno)
{
	try
	{

		Messaggi ^wakeUpPkt = gcnew Messaggi(MessageID::UnconditionCommand);
		//wakeUpPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		wakeUpPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(QCmdData::WAKE_UP);


		// Buffer for reading data
		array<Byte>^bytes_buffer1 =wakeUpPkt->serialize();


		Messaggi ^trainRunningNumberPkt = gcnew Messaggi(MessageID::UnconditionCommand);
		//trainRunningNumberPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		trainRunningNumberPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(QCmdData::TRN);



		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_OPERATIONAL(trn);


		// Buffer for reading data
		array<Byte>^bytes_buffer2 = trainRunningNumberPkt->serialize();

		Messaggi ^missionPlanPkt = gcnew Messaggi(MessageID::MissionPlan);
		//missionPlanPkt->get_pacchettoMissionData()->setNID_PACKET(160);

		tabOrario->setMissionPlanMessage(trn, missionPlanPkt->get_pacchettoMissionData(), confVelocita->getProfiloVelocita(trn));



		// Buffer for reading data
		array<Byte>^bytes_buffer3 = missionPlanPkt->serialize();

		// Creates the Socket to send data over a TCP connection.
		Socket ^sock = gcnew Socket( System::Net::Sockets::AddressFamily::InterNetwork,System::Net::Sockets::SocketType::Stream,System::Net::Sockets::ProtocolType::Tcp );
#ifdef UNIFI
		sock->SendBufferSize = 0;  
#endif // UNIFI


		String ^IP = gcnew String(Treno->getIpAddress());

		IPEndPoint ^lep = gcnew IPEndPoint(IPAddress::Parse(IP), Treno->getTcpPort());

		//Connect(lep,sock);
		sock->Connect(IP, Treno->getTcpPort());

		//NetworkStream ^myStream = gcnew NetworkStream(sock);
		sock->Send(bytes_buffer1,bytes_buffer1->Length, System::Net::Sockets::SocketFlags::None);
		//Send(sock,bytes_buffer1);
		//sock->BeginSend(bytes_buffer1, 0, wakeUpPkt->getSize(),System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedulerTrain::SendCallback ), sock);
		//myStream->Write(bytes_buffer1, 0, wakeUpPkt->getSize());
#ifdef TRACE

		Logger::Info(wakeUpPkt->getNID_MESSAGE(),"ATS->ATO",IP->ToString(),wakeUpPkt->getSize(),BitConverter::ToString(bytes_buffer1),"ThreadSchedulerTrain::WakeUP");

#endif // TRACE
		sock->Send(bytes_buffer2,bytes_buffer2->Length, System::Net::Sockets::SocketFlags::None);
		//Send(sock,bytes_buffer2);
		//sock->BeginSend(bytes_buffer2, 0, trainRunningNumberPkt->getSize() ,System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedulerTrain::SendCallback ), sock);
		//myStream->Write(bytes_buffer2, 0, trainRunningNumberPkt->getSize());
#ifdef TRACE

		Logger::Info(trainRunningNumberPkt->getNID_MESSAGE(),"ATS->ATO",IP->ToString(),trainRunningNumberPkt->getSize(),BitConverter::ToString(bytes_buffer2),"ThreadSchedulerTrain::TRN");

#endif // TRACE
		sock->Send(bytes_buffer3,bytes_buffer3->Length, System::Net::Sockets::SocketFlags::None);
		//Send(sock,bytes_buffer3);
		//sock->BeginSend(bytes_buffer3, 0, missionPlanPkt->getSize() ,System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedulerTrain::SendCallback ), sock);
		//myStream->Write(bytes_buffer3, 0, missionPlanPkt->getSize());
#ifdef TRACE

		Logger::Info(missionPlanPkt->getNID_MESSAGE(),"ATS->ATO",IP->ToString(),missionPlanPkt->getSize(),BitConverter::ToString(bytes_buffer3),"ThreadSchedulerTrain::MissionPlan");

#endif // TRACE
		//sock->Shutdown(System::Net::Sockets::SocketShutdown::Send);
		StateObject^ so2 = gcnew StateObject(Treno->getEngineNumber());
		so2->workSocket = sock;
		so2->fine=-1;
		sock->BeginReceive( so2->buffer, 0, 17,System::Net::Sockets::SocketFlags::Peek, gcnew AsyncCallback( &ThreadSchedulerSortedList::ReceiveCallback ), so2 );


		return so2;
	}
	catch ( Exception^ e ) 
	{
		Console::WriteLine( "SocketException: {0}", e->Message );
#ifdef TRACE
		Logger::Exception(e,"ThreadSchedulerTrain::SendTCPMsg");  
#endif // TRACE
		StateObject^ so2 = gcnew StateObject(Treno->getEngineNumber());

		return so2;
	}


}

void ThreadSchedulerSortedList::ReceiveCallback(IAsyncResult^ asyncResult){

	StateObject^ so = safe_cast<StateObject^>(asyncResult->AsyncState);
	Socket^ s = so->workSocket;
	try{
		int read = s->EndReceive( asyncResult );

		if ( read < 0 )
		{

			s->BeginReceive( so->buffer, 0, 17,System::Net::Sockets::SocketFlags::Peek, gcnew AsyncCallback( &ThreadSchedulerSortedList::ReceiveCallback ), so );
		}
		else
		{
			Messaggi ^pktAck = gcnew Messaggi();


			pktAck->deserialize(so->buffer);

#ifdef TRACE
			String ^ip = (((IPEndPoint^)(s->RemoteEndPoint) )->Address)->ToString();
			Logger::Info(pktAck->getNID_MESSAGE(),"ATO->ATS",ip,pktAck->getSize(),BitConverter::ToString(so->buffer),"ThreadSchedulerTrain::Ack");

#endif // TRACE


			Console::WriteLine("Ack Ricevuto da {0} esito: {1}",pktAck->getNID_ENGINE(), (int) pktAck->get_pacchettoAcknowledgement()->getQ_MISSION_RESPONSE() );

			if(so->enginenumber!=pktAck->getNID_ENGINE()){
				Console::WriteLine("Ack Ricevuto da {0} ma era atteso da: {1}",pktAck->getNID_ENGINE(),so->enginenumber);
			}


			if( pktAck->get_pacchettoAcknowledgement()->getQ_MISSION_RESPONSE()==(int)QMissionResponse::MissioneAccettata){
				s->Close();
				so->fine=1;

			}else{

				//All of the data has been read

				s->Close();
				so->fine=0;
			}
		}
	}catch(Exception ^e){

		Console::WriteLine("hai chiuso il sock ma l'ATO {0} non ha mandato L'ack",so->enginenumber);
		Console::WriteLine("########################");
		Console::WriteLine("Exception ",e->ToString());
		Console::WriteLine("########################");
	}


}


List<int> ^ThreadSchedulerSortedList::RequestItinerarioIXL(int idstazione , int iditinerario){
	List<int> ^listaNIDcdb = tabItinerari->get_Cdb_Itinerario(idstazione,iditinerario);
	int nextcdb = tabItinerari->get_CdbSuccItinerario(idstazione,iditinerario);
	if(nextcdb>0){
		StateCDB ^statocorrentecdb = managerIXL->StatoCDB(nextcdb);
		if(statocorrentecdb!=nullptr){
			if(statocorrentecdb->getQ_STATOCDB()!=(int)QStateCDB::cdbLibero){
				return nullptr;
			}
		}else{
			return nullptr;
		}
	}
	if(controllacdb(listaNIDcdb)){

		if(SendBloccItinIXL(idstazione+iditinerario, QCmdItinerari::creazione)){
			return listaNIDcdb;
		}
	}

	return nullptr;

}

bool ThreadSchedulerSortedList::SendBloccItinIXL(int NID_ITIN, QCmdItinerari Q_CMDITIN){
	try{

		int portixl=4011;
		try{
			if(!Int32::TryParse( System::Configuration::ConfigurationSettings::AppSettings["port_UDP_send"],portixl)){
				portixl=4011;
			}
		} catch(System::Configuration::ConfigurationException  ^error){
			String ^eerr = error->Message;
			portixl=4011;
		}
		Console::WriteLine("PORT UDP Send: {0}",portixl);
		Messaggi ^cmdItini = gcnew Messaggi(MessageID::ComandoItinerari);
		//cmdItini->get_pacchettoComandoItinerari()->setNID_PACKET(10);
		cmdItini->get_pacchettoComandoItinerari()->setNID_ITIN(NID_ITIN);
		cmdItini->get_pacchettoComandoItinerari()->setQ_CMDITIN(Q_CMDITIN);

		Socket ^s = gcnew Socket(System::Net::Sockets::AddressFamily::InterNetwork, System::Net::Sockets::SocketType::Dgram,
			System::Net::Sockets::ProtocolType::Udp);

		IPAddress ^broadcast = IPAddress::Parse(ipixl);
		IPEndPoint ^ep = gcnew IPEndPoint(broadcast, portixl);

		array<Byte>^sendBytes=	cmdItini->serialize();



		s->SendTo( sendBytes , sendBytes->Length, System::Net::Sockets::SocketFlags::None, ep);
#ifdef TRACE

		Logger::Info(cmdItini->getNID_MESSAGE(),"ATS->IXL",broadcast->ToString(),cmdItini->getSize(),BitConverter::ToString(sendBytes),"ThreadSchedulerTrain::BloccoItinerarioIXL");

#endif // TRACE

		return true;

	}catch ( Exception^ eException ) 
	{
#ifdef TRACE
		Logger::Exception(eException,"ThreadSchedulerSortedList::SendBloccItinIXL");  
#endif // TRACE
		Console::WriteLine( "Errore "+eException->Message);
		return false;
	}
}