#include "ThreadSchedulerTrain.h"
#include "..\\TrenoFisicoLogico.h"
#include "..\\messaggi\\pacchettoCommandData.h"
#include "..\\ThreadSchedule.h"
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
using namespace System::Collections::Concurrent;

#define TRACE
ThreadSchedulerTrain::ThreadSchedulerTrain(phisicalTrain ^phi, List<EventQueue^> ^E, TabellaOrario ^tabo, tabellaItinerari ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w,ManagerStatoLineaATC ^manATC,ManagerStatoLineaIXL ^manIXL, ConfigurazioneVelocita ^cvel)
{
	if(E->Count>1){
		EQueueIXL=E[0];
		EQueueATC=E[1];

	}
	mapTrenoLogFisico=mapTreno;
	tabOrario=tabo;
	tabItinerari=tabi;
	confVelocita=cvel;
	wdogs=w;
	managerATC=manATC;
	managerIXL=manIXL;
	ipixl="127.0.0.1";
	listIdCdbItinRic = gcnew List<int>();
	phisical=phi;
	_shouldStop=false;
}

void ThreadSchedulerTrain::SimpleSchedule(){
	try
	{
		Console::WriteLine("Hi!! I'm SimpleSchedule");
		//inizializzazione ATS
		Init();
		int statoInterno = StateSimpleSchedule::ControlloTreno;
		int indicelistaitinerari=0;
		List<Fermata^> ^listaitinerari;
		DateTime time=DateTime::Now;
		StateObject ^inviato;
		int trn =0;
		while(!_shouldStop){
			//dormi un po 100  millisecondi cosi da eseguire un ciclo ogni 100 ms
			Thread::Sleep(100);
			wdogs->onNext();



			int enginenumber = phisical->getEngineNumber();

			TimeSpan sec = DateTime::Now - time;
			if(sec.TotalSeconds>20){
				StampaStato(statoInterno);


				time=DateTime::Now;
			}



			switch (statoInterno)
			{

			case StateSimpleSchedule::ControlloTreno: 
				{


					// se trovi che ha numero logico nella mappa mapTrenoLogFisico 
					if(mapTrenoLogFisico->get_Map()->ContainsKey(enginenumber)){
						TrenoFisicoLogico ^infotrenofisico = mapTrenoLogFisico->get_Map()[enginenumber];
						trn = infotrenofisico->getIdTrenoLogico(0);
						int lastpos =infotrenofisico->getCDBLastPosition();

						// cerchi se c'è una missione per lui nella tabella orario
						if((tabOrario->get_TabellaOrario()->ContainsKey(trn)) & (trn>0)){
							//trova gli itinerari  del treno
							listaitinerari = tabOrario->getItinerariFor(trn);
							int prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(listaitinerari[0]->getIdStazione(),listaitinerari[0]->getIditinerarioUscita());
							// cerca se si trova nella stazione in cui deve partire
							if(lastpos==prevfirstcdbu){

								// gli assegni TRN e MISSION
								if(inviato==nullptr){
									Console::WriteLine("Si trova al posto giusto per partire e gli invio WAKE-UP, TRN e MISSION");
									inviato = SendTCPMsg(trn,phisical);
									time=DateTime::Now;
								}

								if(inviato->fine==1){
									//itinerario uscita

									statoInterno=StateSimpleSchedule::RicItinerarioUscita;
								}
								else{
									//aspetta un po
									TimeSpan sec = DateTime::Now - time;
									if(sec.TotalSeconds>20){
										//riinvia
										inviato->fine=0;
										inviato->workSocket->Close();
										inviato = SendTCPMsg(trn,phisical);
										time=DateTime::Now;
										Console::WriteLine(time);
										Console::WriteLine("il treno nn ha risposto con l'ack all'assegnazione della missione");
									}

								}
							}
						}
					}
					break;
				}
			case StateSimpleSchedule::RicItinerarioEntrata: 
				{

					int initEntrata = listaitinerari[indicelistaitinerari]->getIditinerarioEntrata();
					int idstazione = listaitinerari[indicelistaitinerari]->getIdStazione();
					//se esiste un itinerario di entrata
					if(initEntrata>0){
						int resultprecE = tabItinerari->get_CdbPrecItinerario(idstazione,initEntrata);
						Event ^eventATC = EQueueATC->getEvent();

						if(eventATC!=nullptr){
							Console::WriteLine("PReLEVATO: {0}",eventATC->ToString());
							//se il treno si trova sul cdb giusto
							if(((eventATC->getEventStateCDB()->getNID_CDB()==resultprecE) & (eventATC->getEventStateCDB()->getNID_OPERATIONAL()==trn)) |(
								managerATC->getCDB(resultprecE)->getNID_OPERATIONAL()==trn)){
									//se l'itinerario è libero
									//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
									//che riporti il cambiamento dello stato dell'itinerario
									if(richestaItinerarioIXL(idstazione,initEntrata)){


										statoInterno=StateSimpleSchedule::RicItinerarioUscita;
										//indicelistaitinerari++;
									}
							}
						}else{
							//se il treno si trova sul cdb giusto
							// messo a true per fare test
							if(managerATC->getCDB(resultprecE)->getNID_OPERATIONAL()==trn){
								//se l'itinerario è libero
								//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
								//che riporti il cambiamento dello stato dell'itinerario
								if(richestaItinerarioIXL(idstazione,initEntrata)){

									statoInterno=StateSimpleSchedule::RicItinerarioUscita;
									//indicelistaitinerari++;

								}
							}
						}
					}else{
						statoInterno=StateSimpleSchedule::RicItinerarioUscita;
					}
					break;}
			case StateSimpleSchedule::RicItinerarioUscita: 
				{

					//itinerario uscita
					int itinUscita = listaitinerari[indicelistaitinerari]->getIditinerarioUscita();
					int idstazione = listaitinerari[indicelistaitinerari]->getIdStazione();

					int resultprecCdbU = tabItinerari->get_CdbPrecItinerario(idstazione,itinUscita);

					//int resultSuccCdbU = tabItinerari->get_CdbSuccItinerario(idstazione,itinUscita);

					//se esiste un itinerario di uscita
					if(itinUscita>0){

						DateTime mezzanotte = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
						TimeSpan ^oraattuale =  (DateTime::Now - mezzanotte);
						int tempo = (int)oraattuale->TotalSeconds/30;
						int  costante= 3;
						int resutl = ((int)listaitinerari[indicelistaitinerari]->getOrarioPartenza())-costante;
						//	int statocdbuscitaitinerario = managerIXL->StatoCDB(resultSuccCdbU)->getQ_STATOCDB();
						// controllo posizione e tempo 
						if((managerATC->getCDB(resultprecCdbU)->getNID_OPERATIONAL()==trn )& (resutl<=tempo | true)){//&
							//	( statocdbuscitaitinerario==typeStateCDB::cdbLibero | true)){

							//todo : se ti trovi nel posto giusto


							//se l'itinerario è libero
							//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
							//che riporti il cambiamento dello stato dell'itinerario
							if(richestaItinerarioIXL(idstazione,itinUscita)){
								statoInterno=StateSimpleSchedule::RicItinerarioEntrata;
								indicelistaitinerari++;
							}
						}


					}else{
						statoInterno=StateSimpleSchedule::RicItinerarioEntrata;
					}


					break;
				}
			default:
				break;
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


void ThreadSchedulerTrain::StampaStato(int stato) {
	switch (stato)
	{
	case StateSimpleSchedule::PresentazioneTreno:{Console::ForegroundColor = ConsoleColor::DarkGreen;Console::WriteLine("lo stato interno dello scheduler è PresentazioneTreno");break;}
	case StateSimpleSchedule::ControlloTreno:{Console::ForegroundColor = ConsoleColor::White;Console::WriteLine("lo stato interno dello scheduler è ControlloTreno");break;}
	case StateSimpleSchedule::RicItinerarioEntrata:{Console::ForegroundColor = ConsoleColor::Blue;Console::WriteLine("lo stato interno dello scheduler è RicItinerarioEntrata");break;}
	case StateSimpleSchedule::RicItinerarioUscita:{Console::ForegroundColor = ConsoleColor::Red;Console::WriteLine("lo stato interno dello scheduler è RicItinerarioUscita");break;}

	default:
		break;
	}

}


bool ThreadSchedulerTrain::SendBloccItinIXL(int NID_ITIN, int Q_CMDITIN){
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



		s->SendTo( sendBytes, ep);
#ifdef TRACE

		Logger::Info(cmdItini->getNID_MESSAGE(),"ATS->IXL",broadcast->ToString(),cmdItini->getSize(),BitConverter::ToString(sendBytes),"ThreadSchedulerTrain");

#endif // TRACE

		return true;

	}catch ( Exception^ eException ) 
	{
#ifdef TRACE
		Logger::Exception(eException,"ThreadSchedulerTrain");  
#endif // TRACE
		Console::WriteLine( "Errore "+eException->Message);
		return false;
	}
}





void ThreadSchedulerTrain::Init(){
	Console::WriteLine("Init Schedule session");
	//TODO: in questa fase controllare che lo stato di tutti i cdb proveniente dall'IXL sia consistente

}


StateObject ^ ThreadSchedulerTrain::SendTCPMsg(int trn, phisicalTrain ^Treno)
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


		String ^IP = gcnew String(Treno->getIpAddress());
		sock->Connect(IP, Treno->getTcpPort());

		//NetworkStream ^myStream = gcnew NetworkStream(sock);
		sock->Send(bytes_buffer1);
		//sock->BeginSend(bytes_buffer1, 0, wakeUpPkt->getSize(),System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedulerTrain::SendCallback ), sock);
		//myStream->Write(bytes_buffer1, 0, wakeUpPkt->getSize());
#ifdef TRACE

		Logger::Info(wakeUpPkt->getNID_MESSAGE(),"ATS->ATO",IP->ToString(),wakeUpPkt->getSize(),BitConverter::ToString(bytes_buffer1),"ThreadSchedulerTrain");

#endif // TRACE
		sock->Send(bytes_buffer2);
		//sock->BeginSend(bytes_buffer2, 0, trainRunningNumberPkt->getSize() ,System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedulerTrain::SendCallback ), sock);
		//myStream->Write(bytes_buffer2, 0, trainRunningNumberPkt->getSize());
#ifdef TRACE

		Logger::Info(trainRunningNumberPkt->getNID_MESSAGE(),"ATS->ATO",IP->ToString(),trainRunningNumberPkt->getSize(),BitConverter::ToString(bytes_buffer2),"ThreadSchedulerTrain");

#endif // TRACE
		sock->Send(bytes_buffer3);
		//sock->BeginSend(bytes_buffer3, 0, missionPlanPkt->getSize() ,System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedulerTrain::SendCallback ), sock);
		//myStream->Write(bytes_buffer3, 0, missionPlanPkt->getSize());
#ifdef TRACE

		Logger::Info(missionPlanPkt->getNID_MESSAGE(),"ATS->ATO",IP->ToString(),missionPlanPkt->getSize(),BitConverter::ToString(bytes_buffer3),"ThreadSchedulerTrain");

#endif // TRACE

		StateObject^ so2 = gcnew StateObject;
		so2->workSocket = sock;
		sock->BeginReceive( so2->buffer, 0, 17,System::Net::Sockets::SocketFlags::Peek, gcnew AsyncCallback( &ThreadSchedulerTrain::ReceiveCallback ), so2 );
		so2->fine=-1;

		return so2;
	}
	catch ( Exception^ e ) 
	{
		Console::WriteLine( "SocketException: {0}", e->Message );
#ifdef TRACE
		Logger::Exception(e,"ThreadSchedulerTrain");  
#endif // TRACE
		StateObject^ so2 = gcnew StateObject;

		return so2;
	}


}
void ThreadSchedulerTrain::ReceiveCallback(IAsyncResult^ asyncResult){

	StateObject^ so = safe_cast<StateObject^>(asyncResult->AsyncState);
	Socket^ s = so->workSocket;
	try{
		int read = s->EndReceive( asyncResult );

		if ( read < 0 )
		{

			s->BeginReceive( so->buffer, 0, 17,System::Net::Sockets::SocketFlags::Peek, gcnew AsyncCallback( &ThreadSchedulerTrain::ReceiveCallback ), so );
		}
		else
		{
			Messaggi ^pktAck = gcnew Messaggi();


			pktAck->deserialize(so->buffer);

#ifdef TRACE

			Logger::Info(pktAck->getNID_MESSAGE(),"IP","ATO->ATS",pktAck->getSize(),BitConverter::ToString(so->buffer),"ThreadSchedulerTrain");

#endif // TRACE


			Console::WriteLine("Ack Ricevuto da {0} esito: {1}",pktAck->getNID_ENGINE(), pktAck->get_pacchettoAcknowledgement()->getQ_MISSION_RESPONSE() );

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

		Console::WriteLine("hai chiuso il sock ma l'ATO non ha mandato L'ack");
	}


}

void ThreadSchedulerTrain::SendCallback(IAsyncResult^ asyncResult){

	Socket^ so = safe_cast<Socket^>(asyncResult->AsyncState);

	int send = so->EndSend( asyncResult );


}

//se l'itinerario è libero
//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL che 
//che riporti il cambiamento dello stato dell'itinerario
bool ThreadSchedulerTrain::richestaItinerarioIXL(int idstazione , int iditinerario){
	//if((managerIXL->getItinerario(idstazione+iditinerario)->getQ_STATOITIN()==typeStateItineraio::itinerarioStatoNonInAtto)){
	//controllo dei cdb che fanno parte dell'itinerario che devono essere liberi
	List<int> ^listaNIDcdb = tabItinerari->get_Cdb_Itinerario(idstazione,iditinerario);
	
	if(controllacdb(listaNIDcdb)){

		SendBloccItinIXL(idstazione+iditinerario,typeCmdItinerari::creazione);
		listIdCdbItinRic = gcnew List<int>();
		listIdCdbItinRic->AddRange(listaNIDcdb);
		//if(!listIdCdbItinRic->Contains(listaNIDcdb[0])){
		//	listIdCdbItinRic->Add(listaNIDcdb[0]);
	}
	//}else{
		//Thread::Sleep(500);
		

		if(false){
			Event ^even = EQueueIXL->getEvent();
			int len = listIdCdbItinRic->Count;
			Console::WriteLine("PReLEVATO: {0}",even->ToString());
			StateCDB ^statocdb =even->getEventStateCDB();
			if(statocdb!=nullptr){
				if(listIdCdbItinRic->Contains(statocdb->getNID_CDB()) ){
					if( statocdb->getQ_STATOCDB()==typeStateCDB::cdbImpegnato  ){
						listIdCdbItinRic->Remove(statocdb->getNID_CDB());
					}
				}
				if(listIdCdbItinRic->Count==0){
					return true;
				}
			}
		}else{
			int len = listIdCdbItinRic->Count;
			for each (int varcdb in listIdCdbItinRic)
			{
				StateCDB ^statocorrentecdb = managerIXL->StatoCDB(varcdb);
				if(statocorrentecdb!=nullptr){
					if(statocorrentecdb->getQ_STATOCDB()!=typeStateCDB::cdbImpegnato){
						return false;
					}else{
						if(statocorrentecdb->getQ_STATOCDB()==typeStateCDB::cdbImpegnato){
							len--;
						}
					}

				}

			}
			if(len==0){
				return true;
			}

		//}
	}


	//non controllo se è stato creato l'itinerario
	//return true;

	/*if(even!=nullptr){
	StateItinerario ^statoi =even->getEventStateItinerario();
	if(statoi!=nullptr){
	if(idstazione+iditinerario==statoi->getNID_ITIN() ){
	if( statoi->getQ_STATOITIN()==typeStateItineraio::itinerarioStatoInAtto  ){
	return true;
	}
	}
	}
	}*/
	//}

	//}else{
	//	Console::WriteLine("itinerario nn libero ritenta");
	//	return false;

	//}
	return false;

}

bool ThreadSchedulerTrain::controllacdb(List<int>^lcdb){
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
	}
	return res;
}

void ThreadSchedulerTrain::RequestStop()
{
	_shouldStop = true;
}