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


#define TRACE

ThreadSchedulerSortedList::ThreadSchedulerSortedList(void)
{
}


ThreadSchedulerSortedList::ThreadSchedulerSortedList(List<EventQueue^> ^E, TabellaOrario ^tabo, tabellaItinerari ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w,ManagerStatoLineaATC ^manATC,ManagerStatoLineaIXL ^manIXL, ConfigurazioneVelocita ^cvel)
{
	if(E->Count>2){
		EQueueIXL=E[0];
		EQueueATC=E[1];
		EQueueATO=E[2];
	}
	mapTrenoLogFisico=mapTreno;
	tabOrario=tabo;
	tabItinerari=tabi;
	confVelocita=cvel;
	wdogs=w;
	managerATC=manATC;
	managerIXL=manIXL;
	ipixl="127.0.0.1";
	RaccoltaTrenoRequestCDB  = gcnew Dictionary<KeyListTrain^,List<int>^> ();
	_shouldStop=false;
	ListSortedTrains = gcnew System::Collections::Generic::SortedList<KeyListTrain^, Train^>();
	timeRicIXL;
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
			//Thread::Sleep(100);
			//wdogs->onNext();
			ControllaMSG_ATO();
			ControllaMSG_IXL();

			for each (KeyValuePair<KeyListTrain^, Train^> ^KVTrain in ListSortedTrains)
			{
				switch (KVTrain->Value->getStatoTreno())
				{
				case PRONTO:
					break;
				case USCITASTAZIONE:{
					KeyListTrain^ key = KVTrain->Key;
					Train^ train = KVTrain->Value;
					//itinerario uscita
					KeyValuePair<int, int> ^itistazione = train->getStazioneItinerario();
					int itinUscita = itistazione->Value;
					int idstazione = itistazione->Key;

					int resultprecCdbU = tabItinerari->get_CdbPrecItinerario(idstazione,itinUscita);

					//int resultSuccCdbU = tabItinerari->get_CdbSuccItinerario(idstazione,itinUscita);

					//se esiste un itinerario di uscita
					if(itinUscita>0){

						DateTime mezzanotte = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
						TimeSpan ^oraattuale =  (DateTime::Now - mezzanotte);
						int tempo = (int)oraattuale->TotalSeconds/30;
						int  costante= 3;
						int resutl = ((int)train->getOrarioPartenza())-costante;
						//	int statocdbuscitaitinerario = managerIXL->StatoCDB(resultSuccCdbU)->getQ_STATOCDB();
						// controllo posizione e tempo 
						if(((managerATC->getCDB(resultprecCdbU)->getNID_OPERATIONAL()==train->getTRN())|managerATC->getCDB(resultprecCdbU)->getNID_ENGINE()==train->getPhysicalTrain()->getEngineNumber())& (resutl<=tempo | true)){//&
							//	( statocdbuscitaitinerario==typeStateCDB::cdbLibero | true)){

							//todo : se ti trovi nel posto giusto


							//se l'itinerario � libero
							//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
							//che riporti il cambiamento dello stato dell'itinerario
							if(!RaccoltaTrenoRequestCDB->ContainsKey(key)){
								List<int>^cdbricPrenotazione = RequestItinerarioIXL(idstazione,itinUscita);
								if(cdbricPrenotazione!=nullptr){
									RaccoltaTrenoRequestCDB->Add(key,cdbricPrenotazione);
								}
							}
							//statoInterno=StateSimpleSchedule::RicItinerarioEntrata;

							//indicelistaitinerari++;

						}


					}else{
						train->setStatoTreno(StateTrain::ENTRATASTAZIONE);
					}
					break;
									}
				case ENTRATASTAZIONE: {

					KeyListTrain^ key = KVTrain->Key;
					Train^ train = KVTrain->Value;
					//itinerario uscita
					KeyValuePair<int, int> ^itistazione = train->getStazioneItinerario();

					int initEntrata = itistazione->Value;
					int idstazione = itistazione->Key;
					//se esiste un itinerario di entrata
					if(initEntrata>0){
						int resultprecE = tabItinerari->get_CdbPrecItinerario(idstazione,initEntrata);
						Event ^eventATC = EQueueATC->getEvent();

						if(eventATC!=nullptr){
							//Console::WriteLine("PReLEVATO: {0}",eventATC->ToString());
							//se il treno si trova sul cdb giusto
							if(((eventATC->getEventStateCDB()->getNID_CDB()==resultprecE) & (eventATC->getEventStateCDB()->getNID_OPERATIONAL()==train->getTRN() | eventATC->getEventStateCDB()->getNID_ENGINE()==train->getPhysicalTrain()->getEngineNumber())) |((
								managerATC->getCDB(resultprecE)->getNID_OPERATIONAL()==train->getTRN() )|managerATC->getCDB(resultprecE)->getNID_ENGINE()==train->getPhysicalTrain()->getEngineNumber())){
									//se l'itinerario � libero
									//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
									//che riporti il cambiamento dello stato dell'itinerario
									if(!RaccoltaTrenoRequestCDB->ContainsKey(key)){
										List<int>^cdbricPrenotazione = RequestItinerarioIXL(idstazione,initEntrata);
										if(cdbricPrenotazione!=nullptr){
											RaccoltaTrenoRequestCDB->Add(key,cdbricPrenotazione);
										}
									}

							}
						}else{
							//se il treno si trova sul cdb giusto
							// messo a true per fare test
							if(managerATC->getCDB(resultprecE)->getNID_OPERATIONAL()==train->getTRN()){
								//se l'itinerario � libero
								//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
								//che riporti il cambiamento dello stato dell'itinerario
								if(!RaccoltaTrenoRequestCDB->ContainsKey(key)){
									List<int>^cdbricPrenotazione = RequestItinerarioIXL(idstazione,initEntrata);
									if(cdbricPrenotazione!=nullptr){
										RaccoltaTrenoRequestCDB->Add(key,cdbricPrenotazione);
									}
								}
							}
						}
					}else{
						train->setStatoTreno(StateTrain::USCITASTAZIONE);
					}




					break;
									  }
				case NONPRONTO:
					break;
				case TERMINATO:
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

void ThreadSchedulerSortedList::ControllaMSG_IXL(){
	Event ^eventoIXL;
	eventoIXL = EQueueIXL->getEvent();
	if(eventoIXL!=nullptr){
		StateCDB ^eventocambiostatocdb = eventoIXL->getEventStateCDB();
		if(eventocambiostatocdb->getQ_STATOCDB()==typeStateCDB::cdbImpegnato ){
			List<KeyListTrain^> ^elemetidaeliminare = gcnew List<KeyListTrain^>();
			for each (KeyValuePair<KeyListTrain^,List<int>^> ^kvpair in RaccoltaTrenoRequestCDB)
			{
				if(kvpair->Value->Contains(eventocambiostatocdb->getNID_CDB())){
					kvpair->Value->Remove(eventocambiostatocdb->getNID_CDB());
				}
				if(kvpair->Value->Count==0){
					elemetidaeliminare->Add(kvpair->Key);
					ListSortedTrains[kvpair->Key]->goNextItinerario();
				}

			}
			for each (KeyListTrain ^var in elemetidaeliminare)
			{
				RaccoltaTrenoRequestCDB->Remove(var);
			}
		}
	}
}

void ThreadSchedulerSortedList::ControllaMSG_ATO(){
	DateTime time=DateTime::Now;
	Event ^eventoATO;
	StateObject ^inviato;
	// aspetta che si presenti un treno
	eventoATO = EQueueATO->getEvent();
	if(eventoATO!=nullptr){
		physicalTrain ^phisical = eventoATO->getEventPresentTrain();
		int enginenumber = phisical->getEngineNumber();
		Console::WriteLine("Si � presentato il treno {0}",enginenumber);

		// se trovi che ha numero logico nella mappa mapTrenoLogFisico 
		if(mapTrenoLogFisico->get_Map()->ContainsKey(enginenumber)){
			TrenoFisicoLogico ^infotrenofisico = mapTrenoLogFisico->get_Map()[enginenumber];
			int trn = infotrenofisico->getIdTrenoLogico(0);
			int lastpos =infotrenofisico->getCDBLastPosition();

			// cerchi se c'� una missione per lui nella tabella orario
			if((tabOrario->get_TabellaOrario()->ContainsKey(trn)) & (trn>0)){
				//trova gli itinerari  del treno
				List<Fermata^> ^listaitinerari = tabOrario->getItinerariFor(trn);
				int prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(listaitinerari[0]->getIdStazione(),listaitinerari[0]->getIditinerarioUscita());
				// cerca se si trova nella stazione in cui deve partire
				if(lastpos==prevfirstcdbu){


					//se il treno si trova sul cdb giusto
					if(((managerATC->getCDB(prevfirstcdbu)->getNID_OPERATIONAL()==trn)|managerATC->getCDB(prevfirstcdbu)->getNID_ENGINE()==enginenumber)|true){

						// gli assegni TRN e MISSION
						if(inviato==nullptr){
							Console::WriteLine("Il treno {0} si trova al posto giusto per partire e gli invio WAKE-UP, TRN={1} e MISSION",enginenumber,trn);
							inviato = InizializzeATO(trn,phisical);
							time=DateTime::Now;
						}
						while (inviato->fine!=1){
							//aspetta un po
							TimeSpan sec = DateTime::Now - time;
							if(sec.TotalSeconds>200){
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
							listaitinerari[0]->getOrarioPartenza();
							Train ^treno = gcnew Train(trn,phisical,listaitinerari);
							//Creo KeyListTrain
							int priorita = 1;
							KeyListTrain ^key = gcnew KeyListTrain(priorita,trn,enginenumber,listaitinerari[0]->getOrarioPartenza());
							ListSortedTrains->Add(key,treno);
						}

					}
				}
			}
		}




	}
}


void ThreadSchedulerSortedList::RequestStop()
{
	_shouldStop = true;

}



void ThreadSchedulerSortedList::Init(){
	Console::WriteLine("Inizio Inizializzazione dello Scheduler");
	//TODO: in questa fase ad es. controllare che lo stato di tutti i cdb proveniente dall'IXL sia consistente
	Console::WriteLine("Fine Inizializzazione dello Scheduler");
}



bool ThreadSchedulerSortedList::controllacdb(List<int>^lcdb){
	bool res=true;
	for each (int cdb in lcdb)
	{
		StateCDB ^statocorrentecdb = managerIXL->StatoCDB(cdb);
		if(statocorrentecdb!=nullptr){
			if(statocorrentecdb->getQ_STATOCDB()!=typeStateCDB::cdbLibero){
				return false;
			}
		}else{
			return false;
		}
		if(RaccoltaTrenoRequestCDB!=nullptr){
			for each (KeyValuePair<KeyListTrain^,List<int>^> ^kvpair in RaccoltaTrenoRequestCDB)
			{
				if(kvpair->Value->Contains(cdb)){
					return false;
				}
			}

		}
	}

	return res;
}


StateObject ^ThreadSchedulerSortedList::InizializzeATO(int trn, physicalTrain ^Treno)
{
	try
	{

		Messaggi ^wakeUpPkt = gcnew Messaggi();

		wakeUpPkt->setNID_MESSAGE(MessATO::UnconditionCommand);

		wakeUpPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		wakeUpPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(typeCmdData::WAKE_UP);
		//set time
		DateTime orarioSupporto3 = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
		TimeSpan ^sinceMidnight =  DateTime::Now - orarioSupporto3;
		wakeUpPkt->setT_TIME((int)sinceMidnight->TotalSeconds/30);

		// Buffer for reading data
		array<Byte>^bytes_buffer1 =wakeUpPkt->serialize();


		Messaggi ^trainRunningNumberPkt = gcnew Messaggi();


		trainRunningNumberPkt->setNID_MESSAGE(MessATO::UnconditionCommand);
		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		trainRunningNumberPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(typeCmdData::TRN);

		trainRunningNumberPkt->setT_TIME((int)sinceMidnight->TotalSeconds/30);

		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_OPERATIONAL(trn);


		// Buffer for reading data
		array<Byte>^bytes_buffer2 = trainRunningNumberPkt->serialize();

		Messaggi ^missionPlanPkt = gcnew Messaggi();

		missionPlanPkt->setNID_MESSAGE(MessATO::MissionPlan);
		missionPlanPkt->get_pacchettoMissionData()->setNID_PACKET(160);
		missionPlanPkt->setT_TIME((int)sinceMidnight->TotalSeconds/30);

		tabOrario->setMissionPlanMessage(trn, missionPlanPkt->get_pacchettoMissionData(), confVelocita->getProfiloVelocita(trn));



		// Buffer for reading data
		array<Byte>^bytes_buffer3 = missionPlanPkt->serialize();

		// Creates the Socket to send data over a TCP connection.
		Socket ^sock = gcnew Socket( System::Net::Sockets::AddressFamily::InterNetwork,System::Net::Sockets::SocketType::Stream,System::Net::Sockets::ProtocolType::Tcp );
		sock->SendBufferSize = 0;

		String ^IP = gcnew String(Treno->getIpAddress());
		sock->Connect(IP, Treno->getTcpPort());

		//NetworkStream ^myStream = gcnew NetworkStream(sock);
		sock->Send(bytes_buffer1,bytes_buffer1->Length, System::Net::Sockets::SocketFlags::None);
		//sock->BeginSend(bytes_buffer1, 0, wakeUpPkt->getSize(),System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedulerTrain::SendCallback ), sock);
		//myStream->Write(bytes_buffer1, 0, wakeUpPkt->getSize());
#ifdef TRACE

		Logger::Info(wakeUpPkt->getNID_MESSAGE(),"ATS->ATO",IP->ToString(),wakeUpPkt->getSize(),BitConverter::ToString(bytes_buffer1),"ThreadSchedulerTrain::WakeUP");

#endif // TRACE
		sock->Send(bytes_buffer2,bytes_buffer2->Length, System::Net::Sockets::SocketFlags::None);
		//sock->BeginSend(bytes_buffer2, 0, trainRunningNumberPkt->getSize() ,System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedulerTrain::SendCallback ), sock);
		//myStream->Write(bytes_buffer2, 0, trainRunningNumberPkt->getSize());
#ifdef TRACE

		Logger::Info(trainRunningNumberPkt->getNID_MESSAGE(),"ATS->ATO",IP->ToString(),trainRunningNumberPkt->getSize(),BitConverter::ToString(bytes_buffer2),"ThreadSchedulerTrain::TRN");

#endif // TRACE
		sock->Send(bytes_buffer3,bytes_buffer3->Length, System::Net::Sockets::SocketFlags::None);
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


			Console::WriteLine("Ack Ricevuto da {0} esito: {1}",pktAck->getNID_ENGINE(), pktAck->get_pacchettoAcknowledgement()->getQ_MISSION_RESPONSE() );

			if(so->enginenumber!=pktAck->getNID_ENGINE()){
				Console::WriteLine("Ack Ricevuto da {0} ma era atteso da: {1}",pktAck->getNID_ENGINE(),so->enginenumber);
			}


			if( pktAck->get_pacchettoAcknowledgement()->getQ_MISSION_RESPONSE()==1){
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
	}


}


List<int> ^ThreadSchedulerSortedList::RequestItinerarioIXL(int idstazione , int iditinerario){
	List<int> ^listaNIDcdb = tabItinerari->get_Cdb_Itinerario(idstazione,iditinerario);

	if(controllacdb(listaNIDcdb)){

		if(SendBloccItinIXL(idstazione+iditinerario,typeCmdItinerari::creazione)){


			timeRicIXL=DateTime::Now;

			return listaNIDcdb;
		}
	}

	return nullptr;

}

bool ThreadSchedulerSortedList::SendBloccItinIXL(int NID_ITIN, int Q_CMDITIN){
	try{
		int portixl=4011;
		Messaggi ^cmdItini = gcnew Messaggi();


		cmdItini->setNID_MESSAGE(MessIXL::ComandoItinerari);
		cmdItini->get_pacchettoComandoItinerari()->setNID_PACKET(10);
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