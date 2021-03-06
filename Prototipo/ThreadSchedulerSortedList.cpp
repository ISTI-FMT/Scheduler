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
using namespace LivenessCheck;


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
	liveness = gcnew Liveness(areeCritiche->get_limitiAree());
	RaccoltaTrenoRequestCDB  = gcnew Dictionary<Train^,List<int>^> ();
	EQueueCambioOrario = gcnew EventQueue<List<Fermata^>^>();
	_shouldStop=false;

	//settare a true per ignorare i controlli sulle aree critiche
	_blockAreeCritiche = true;
	//ListSortedTrains = gcnew System::Collections::Generic::SortedList<KeyListTrain^, Train^>();


	ListTrainModel ^model = gcnew ListTrainModel();
	listatrenipresentati = gcnew List<physicalTrain^>();
	view = gcnew Prototipo::ListTrainView(tabItinerari,EQueueCambioOrario);
	model->Subscribe(view);
	view->AddModel(model);
	controlListtrain = gcnew ControllerListTrain(model);

	//Application::Run(view);
	view->Visible=true;
}

bool ThreadSchedulerSortedList::CheckLiveness(int trn, int nextCdb)
{
	//Eseguo il controllo sulla liveness.
	//Al momento il controllo non tiene in considerazione le aree critiche perch�, al momento, le aree critiche sono ricevute in input staticamente
	//e non tengono conto di quali treni sono effettivamente in movimento ma considerano tutti i treni del sistema contemporaneamente
	System::Collections::Generic::Stack<Movimento^>^ path = liveness->LivenessCheck(trn, nextCdb, false);
	if (path == nullptr)
	{
		Console::WriteLine("Check liveness fallito! TRN: {0}",trn);
	}

	return path != nullptr;
}

void ThreadSchedulerSortedList::Schedule(){
	try
	{
		Console::WriteLine("Hi!! I'm Schedule");
		//inizializzazione ATS
		Init();

		//DateTime time=DateTime::Now;

		while(!_shouldStop){
			//dormi un po 100  millisecondi cosi da eseguire un ciclo ogni 100 ms
			//controlListtrain->Sort();
			Thread::Sleep(100);
			wdogs->onNext();
			ControllaMSG_ATO();
			ControllaMSG_IXL();
			ControllaEventiCambioOrario();
			List<Train^>^ TrainTermined = gcnew List<Train^>();
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

					List<Fermata^> ^listafermate = tabOrario->getFermateFor(Train->getTRN());

					//int prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(listaitinerari[0]->getIdStazione(),listaitinerari[0]->getIditinerarioUscita());
					int prevfirstcdbu = 0;
					int bin = 0;
					if(listafermate!=nullptr  & listafermate->Count>0 ){
						int iu = listafermate[0]->getIditinerarioEntrata();
						int ie = listafermate[0]->getIditinerarioUscita();
						if((iu>0)|(ie>0))
						{
							prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(listafermate[0]->getIdStazione(),listafermate[0]->getIditinerarioUscita());
						}
						else
						{
							bin = listafermate[0]->getBinarioProgrammato();
							prevfirstcdbu = tabItinerari->get_CdbFermata(listafermate[0]->getIdStazione(),bin);
						}
					}
					/*int idTRenoCDBPrecIT = managerATC->getCDB(prevfirstcdbu)->getNID_OPERATIONAL();
					int nid_engineTRenoCDBPrecIT = managerATC->getCDB(prevfirstcdbu)->getNID_ENGINE();*/

					//  tempo 
					if((resutl<=tempo | true)){//&

						if ((areeCritiche->richiestaCdb(prevfirstcdbu, Train->getTRN())|(_blockAreeCritiche)))
						{
							if (!_blockLiveness)
							{
								MissioneLiveness^ missione = gcnew MissioneLiveness(Train->getTRN());
								List<int>^ cdbs = tabOrario->getCDBSignificativiFor(Train->getTRN());
								missione->Cdbs = cdbs->ToArray();
								liveness->AggiungiMissione(missione);
								liveness->MuoviTreno(Train->getTRN(), prevfirstcdbu);
							}

							controlListtrain->changeStato(Train,StateTrain::USCITASTAZIONE);
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
							if ((areeCritiche->richiestaCdb(lastcdbiti, Train->getTRN()))|(_blockAreeCritiche))
							{
								if (_blockLiveness || CheckLiveness(Train->getTRN(), lastcdbiti))
								{
									if(!RaccoltaTrenoRequestCDB->ContainsKey(Train))
									{
										List<int>^cdbricPrenotazione = RequestItinerarioIXL(idstazione,itinUscita);
										if(cdbricPrenotazione!=nullptr){
											if (!_blockLiveness)
											{
												liveness->MuoviTreno(Train->getTRN(), lastcdbiti);
											}

											RaccoltaTrenoRequestCDB->Add(Train,cdbricPrenotazione);
										}
									}
								}
							}else{

								Console::WriteLine("Blocco per area critica {0}", Train->getTRN());
							}
						}
					}
					else
					{

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
									//se l'itinerario � libero
									//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
									//che riporti il cambiamento dello stato dell'itinerario

									//Controllo che l'acquisizione del prossimo cdb non crei deadlock
									List<int> ^cdbItinerario =  tabItinerari->get_Cdb_Itinerario(idstazione,initEntrata);
									int lastcdbiti = cdbItinerario[cdbItinerario->Count-1];
									if ((areeCritiche->richiestaCdb(lastcdbiti, Train->getTRN()))|(_blockAreeCritiche))
									{
										if (_blockLiveness || CheckLiveness(Train->getTRN(), lastcdbiti))
										{
											if(!RaccoltaTrenoRequestCDB->ContainsKey(Train)){

												List<int>^cdbricPrenotazione = RequestItinerarioIXL(idstazione,initEntrata);
												if(cdbricPrenotazione!=nullptr){
													if (!_blockLiveness)
													{
														liveness->MuoviTreno(Train->getTRN(), lastcdbiti);
													}
													RaccoltaTrenoRequestCDB->Add(Train,cdbricPrenotazione);
												}
											}
										}
									}else{

										Console::WriteLine("Blocco treno {0}  per area critica", Train->getTRN());

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
								if ((areeCritiche->richiestaCdb(lastcdbiti, Train->getTRN()))|(_blockAreeCritiche))
								{
									if (_blockLiveness || CheckLiveness(Train->getTRN(), lastcdbiti))
									{
										//se l'itinerario � libero
										//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
										//che riporti il cambiamento dello stato dell'itinerario
										if(!RaccoltaTrenoRequestCDB->ContainsKey(Train)){

											List<int>^cdbricPrenotazione = RequestItinerarioIXL(idstazione,initEntrata);

											if(cdbricPrenotazione!=nullptr){
												if (!_blockLiveness)
												{
													liveness->MuoviTreno(Train->getTRN(), lastcdbiti);
												}
												RaccoltaTrenoRequestCDB->Add(Train,cdbricPrenotazione);
											}
										}
									}
								}else{

									Console::WriteLine("Blocco per area critica {0}", Train->getTRN());
								}
							}
						}
					}else{

						controlListtrain->OnNextIt(Train);
					}




					break;
												  }
				case StateTrain::NONPRONTO:
					break;
				case StateTrain::TERMINATO:{
					liveness->RimuoviMissione(Train->getTRN());

					List<int>^ licdb = tabItinerari->get_Cdb_Itinerario( Train->getStazioneItinerario()->Key, Train->getStazioneItinerario()->Value);
					int cdbfinecorsa = licdb[licdb->Count-1];
					int nid_engineTRenoCDBPrecIT = managerATC->getCDB(cdbfinecorsa)->getNID_ENGINE();
					if(managerATC->getCDB(cdbfinecorsa)->getNID_OPERATIONAL()==Train->getTRN()|nid_engineTRenoCDBPrecIT==Train->getPhysicalTrain()->getEngineNumber()){
						TrainTermined->Add(Train);
					}

					break;}
				default:
					break;
				}
			}
			for each (Train^ var in TrainTermined)
			{
				controlListtrain->OnDelete(var);

				if( mapTrenoLogFisico->get_Map()[ var->getPTN()]->getNextLogicTrain()>0){
					List<int>^ licdb = tabItinerari->get_Cdb_Itinerario( var->getStazioneItinerario()->Key, var->getStazioneItinerario()->Value);
					mapTrenoLogFisico->get_Map()[ var->getPTN()]->setCDBLastPosition(licdb[licdb->Count-1]);
					physicalTrain^ ftrain = var->getPhysicalTrain();
					ftrain->setStateObject(nullptr);
					listatrenipresentati->Add(ftrain);

					Pronto_ATO();
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
		//	DateTime time=DateTime::Now;
		//	TimeSpan ^sec =  TimeSpan::Zero;
		//da migliorare
		//	while ((inviato->fine!=1) & (sec->TotalSeconds<10)){
		//	sec = DateTime::Now - time;

		//reinvia


		//	}
		if(inviato->fine==1){
			//aggiorna modello se ack � giusto
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
	}else{

		TimeSpan ^sec = DateTime::Now - timeRicIXL;

		if(sec->TotalSeconds>5){

			for each (KeyValuePair<Train^,List<int>^> ^kvpair in RaccoltaTrenoRequestCDB)
			{
				KeyValuePair<int, int> ^stait =	kvpair->Key->getStazioneItinerario();
				SendBloccItinIXL(stait->Key+stait->Value, QCmdItinerari::creazione);

			}
		}

	}
}

void ThreadSchedulerSortedList::ControllaMSG_ATO(){


	// aspetta che si presenti un treno
	Event<physicalTrain^> ^eventoATO = EQueueATO->getEvent();
	if(eventoATO!=nullptr){
		physicalTrain ^phl = eventoATO->getEvent();
		listatrenipresentati->Add(phl);
		Console::WriteLine("Si � presentato il treno {0}",phl->getEngineNumber());

	}
	Pronto_ATO();
}
void ThreadSchedulerSortedList::Pronto_ATO(){
	List<physicalTrain^> ^listremove=gcnew List<physicalTrain^>();
	for each (physicalTrain ^phisical in listatrenipresentati)
	{

		StateObject ^inviato = phisical->getStateObject();
		int enginenumber = phisical->getEngineNumber();


		// se trovi che ha numero logico nella mappa mapTrenoLogFisico 
		if(mapTrenoLogFisico->get_Map()->ContainsKey(enginenumber)){
			TrenoFisicoLogico ^infotrenofisico = mapTrenoLogFisico->get_Map()[enginenumber];
			int trn = infotrenofisico->getCurrentLogicTrain();//getIdTrenoLogico(0);
			int lastpos =infotrenofisico->getCDBLastPosition();

			// cerchi se c'� una missione per lui nella tabella orario
			if((tabOrario->get_TabellaOrario()->ContainsKey(trn)) & (trn>0)){
				//trova gli itinerari  del treno
				List<Fermata^> ^listafermate = tabOrario->getFermateFor(trn);

				//int prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(listaitinerari[0]->getIdStazione(),listaitinerari[0]->getIditinerarioUscita());
				int prevfirstcdbu = 0;
				int bin = 0;
				if(listafermate!=nullptr  & listafermate->Count>0 ){
					int iu = listafermate[0]->getIditinerarioEntrata();
					int ie = listafermate[0]->getIditinerarioUscita();
					if((iu>0)|(ie>0))
					{
						prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(listafermate[0]->getIdStazione(),listafermate[0]->getIditinerarioUscita());
					}
					else
					{
						bin = listafermate[0]->getBinarioProgrammato();
						prevfirstcdbu = tabItinerari->get_CdbFermata(listafermate[0]->getIdStazione(),bin);
					}
				}
				// prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(listaitinerari[0]->getIdStazione(),listaitinerari[0]->getIditinerarioUscita());
				// cerca se si trova nella stazione in cui deve partire
				if(lastpos==prevfirstcdbu){
					StateCDB ^statocorrentecdb = managerIXL->StatoCDB(lastpos);
					if(statocorrentecdb!=nullptr){
						//cerca se il binario in cui la sera prima ho lasciato il treno � occupato
						if((QStateCDB)statocorrentecdb->getQ_STATOCDB()==QStateCDB::cdbOccupato){

							// gli assegni TRN e MISSION
							if(inviato==nullptr){
								Console::WriteLine("Il treno {0} si trova al posto giusto per partire e gli invio WAKE-UP, TRN={1} e MISSION",enginenumber,trn);
								inviato = InizializzeATO(trn,phisical);
								Console::WriteLine(inviato->time);
								phisical->setStateObject(inviato);

							}
							TimeSpan ^sec = TimeSpan::Zero; 
							if((inviato->fine!=1)){
								//aspetta un po

								sec = DateTime::Now - inviato->time;
								if(sec->TotalSeconds>30){
									//riinvia
									inviato->fine=0;
									if(inviato->workSocket!=nullptr){
										inviato->workSocket->Close();
									}
									inviato = InizializzeATO(trn,phisical);
									phisical->setStateObject(inviato);
									Console::WriteLine(inviato->time);
									Console::WriteLine("Il treno {0} non ha risposto con l'ack all'assegnazione della missione",enginenumber);
								}


							}
							if(inviato->fine==1){
								//Creo il treno
								Console::WriteLine("ok {0}",listafermate[0]->getOrarioPartenza());

								List<Fermata^> ^listafermate = tabOrario->getFermateFor(trn); //tabOrario->getItinerariFor(trn);//
								int priorita = 1;
								Train ^treno = gcnew Train(priorita,trn,phisical,listafermate);
								//Creo KeyListTrain
								listremove->Add(phisical);
								controlListtrain->OnSetTrain(treno);
							}
						}
					}
				}
			}
		}

	}

	for each (physicalTrain ^phisical in listremove)
	{
		listatrenipresentati->Remove(phisical);
	}


}


void ThreadSchedulerSortedList::RequestStop()
{
	view->RequestStop();
	_shouldStop = true;

}



void ThreadSchedulerSortedList::Init(){

	//Console::WriteLine("Inizio Inizializzazione dello Scheduler");
	//TODO: in questa fase ad es. controllare che lo stato di tutti i cdb proveniente dall'IXL sia consistente
	//Console::WriteLine("Fine Inizializzazione dello Scheduler");



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
		String ^infotrain = trn.ToString()+"/"+Treno->getEngineNumber();
		Logger::Info(missionPlanPkt->getNID_MESSAGE(),"ATS->ATO"+"{"+infotrain+"}",IP->ToString(),missionPlanPkt->getSize(),BitConverter::ToString(bytes_buffer3),"ThreadSchedulerTrain::MissionPlan");
		Logger::Info(missionPlanPkt->toPrint(),"ThreadSchedulerTrain::MissionPlan"+"{"+infotrain+"}");
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
// -1 perch� la prima fermata non viene considerata negli N_ITER
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
		String ^infotrain = trn.ToString()+"/"+Treno->getEngineNumber();
		Logger::Info(wakeUpPkt->getNID_MESSAGE(),"ATS->ATO"+"{"+infotrain+"}",IP->ToString(),wakeUpPkt->getSize(),BitConverter::ToString(bytes_buffer1),"ThreadSchedulerTrain::WakeUP");

#endif // TRACE
		sock->Send(bytes_buffer2,bytes_buffer2->Length, System::Net::Sockets::SocketFlags::None);
		//Send(sock,bytes_buffer2);
		//sock->BeginSend(bytes_buffer2, 0, trainRunningNumberPkt->getSize() ,System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedulerTrain::SendCallback ), sock);
		//myStream->Write(bytes_buffer2, 0, trainRunningNumberPkt->getSize());
#ifdef TRACE

		Logger::Info(trainRunningNumberPkt->getNID_MESSAGE(),"ATS->ATO"+"{"+infotrain+"}",IP->ToString(),trainRunningNumberPkt->getSize(),BitConverter::ToString(bytes_buffer2),"ThreadSchedulerTrain::TRN");

#endif // TRACE
		sock->Send(bytes_buffer3,bytes_buffer3->Length, System::Net::Sockets::SocketFlags::None);
		//Send(sock,bytes_buffer3);
		//sock->BeginSend(bytes_buffer3, 0, missionPlanPkt->getSize() ,System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedulerTrain::SendCallback ), sock);
		//myStream->Write(bytes_buffer3, 0, missionPlanPkt->getSize());
#ifdef TRACE
		
		Logger::Info(missionPlanPkt->getNID_MESSAGE(),"ATS->ATO"+"{"+infotrain+"}",IP->ToString(),missionPlanPkt->getSize(),BitConverter::ToString(bytes_buffer3),"ThreadSchedulerTrain::MissionPlan");
		Logger::Info(missionPlanPkt->toPrint(),"ThreadSchedulerTrain::MissionPlan"+"{"+infotrain+"}");
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
	timeRicIXL  = DateTime::Now;
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
		Logger::Info(cmdItini->toPrint(),"ThreadSchedulerTrain::BloccoItinerarioIXL");
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