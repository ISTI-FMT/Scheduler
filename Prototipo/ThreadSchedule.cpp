#include "ThreadSchedule.h"
#include "TrenoFisicoLogico.h"


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

enum StateSimpleSchedule {StatoIgnoto = -1, PresentazioneTreno = 0, ControlloTreno = 1, RicItinerarioEntrata=3, RicItinerarioUscita=4};

ThreadSchedule::ThreadSchedule(List<EventQueue^> ^E, TabellaOrario ^tabo, tabellaItinerari ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w,ManagerStatoLineaATC ^manATC,ManagerStatoLineaIXL ^manIXL)
{
	if(E->Count>2){
		EQueueIXL=E[0];
		EQueueATC=E[1];
		EQueueATO=E[2];
	}
	mapTrenoLogFisico=mapTreno;
	tabOrario=tabo;
	tabItinerari=tabi;
	wdogs=w;
	managerATC=manATC;
	managerIXL=manIXL;
}


void ThreadSchedule::SimpleSchedule(){
	try
	{
		Console::WriteLine("Hi!! I'm SimpleSchedule");
		//inizializzazione ATS
		Init();
		int statoInterno = StateSimpleSchedule::PresentazioneTreno;
		int indicelistaitinerari=0;
		List<Fermata^> ^listaitinerari;
		DateTime time;
		StateObject ^inviato;
		int trn =0;
		while(true){
			int enginenumber;
			Event ^eventoATO;

			//dormi un po 500  millisecondi 
			Thread::Sleep(500);
			wdogs->onNext();
			switch (statoInterno)
			{
			case StateSimpleSchedule::PresentazioneTreno:
				{
					// aspetta che si presenti un treno
					eventoATO = EQueueATO->getEvent();
					if(eventoATO!=nullptr){
						enginenumber = eventoATO->getEventPresentTrain()->getEngineNumber();
						statoInterno=StateSimpleSchedule::ControlloTreno;
					}
					break;
				}
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
									Console::WriteLine("Si trova al posto giusto per partire e gli assegno la missione");
									inviato = SendTCPMsg(trn,eventoATO->getEventPresentTrain());
									time=DateTime::Now;
								}

								if(inviato->fine==1){
									//itinerario entrata

									statoInterno=StateSimpleSchedule::RicItinerarioEntrata;
								}
								else{
									//aspetta un po
									TimeSpan sec = DateTime::Now - time;
									if(sec.TotalSeconds>20){
										//riinvia
										inviato->fine=0;
										inviato->workSocket->Close();
										inviato = SendTCPMsg(trn,eventoATO->getEventPresentTrain());
										time=DateTime::Now;
										Console::WriteLine(time);
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
							//se il treno si trova sul cdb giusto
							if(((eventATC->getEventStateCDB()->getNID_CDB()==resultprecE) & (eventATC->getEventStateCDB()->getNID_OPERATIONAL()==trn)) |(
								managerATC->getCDB(resultprecE)->getNID_OPERATIONAL()==trn)){
									//se l'itinerario è libero
									//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
									//che riporti il cambiamento dello stato dell'itinerario
									if(richestaItinerarioIXL(idstazione+initEntrata)){


										statoInterno=StateSimpleSchedule::RicItinerarioUscita;
										indicelistaitinerari++;
									}
							}
						}else{
							//se il treno si trova sul cdb giusto
							if(managerATC->getCDB(resultprecE)->getNID_OPERATIONAL()==trn){
								//se l'itinerario è libero
								//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
								//che riporti il cambiamento dello stato dell'itinerario
								if(richestaItinerarioIXL(idstazione+initEntrata)){

									statoInterno=StateSimpleSchedule::RicItinerarioUscita;
									indicelistaitinerari++;

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
					int resultsuccCdbU = tabItinerari->get_CdbSuccItinerario(idstazione,itinUscita);
					//se esiste un itinerario di uscita
					if(itinUscita>0){

						DateTime mezzanotte = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
						TimeSpan ^oraattuale =  (DateTime::Now - mezzanotte);
						int tempo = (int)oraattuale->TotalSeconds/30;
						int  costante= 3;
						int resutl = ((int)listaitinerari[indicelistaitinerari]->getOrarioPartenza())-costante;
						int statocdbuscitaitinerario = managerIXL->StatoCDB(resultsuccCdbU)->getQ_STATOCDB();
						//stato cdb uscita, controllo posizione e tempo 
						if(( statocdbuscitaitinerario==typeStateCDB::cdbLibero | true)&(managerATC->getCDB(resultprecCdbU)->getNID_OPERATIONAL()==trn | true)& (resutl<=tempo)){


							//todo : se ti trovi nel posto giusto


							//se l'itinerario è libero
							//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
							//che riporti il cambiamento dello stato dell'itinerario
							if(richestaItinerarioIXL(itinUscita+idstazione)){
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



bool ThreadSchedule::SendBloccItinIXL(int NID_ITIN, int Q_CMDITIN){
	try{
		Messaggi ^cmdItini = gcnew Messaggi();


		cmdItini->setNID_MESSAGE(110);
		cmdItini->get_pacchettoComandoItinerari()->setNID_PACKET(110);
		cmdItini->get_pacchettoComandoItinerari()->setNID_ITIN(NID_ITIN);
		cmdItini->get_pacchettoComandoItinerari()->setQ_CMDITIN(Q_CMDITIN);

		Socket ^s = gcnew Socket(System::Net::Sockets::AddressFamily::InterNetwork, System::Net::Sockets::SocketType::Dgram,
			System::Net::Sockets::ProtocolType::Udp);

		IPAddress ^broadcast = IPAddress::Parse("146.48.84.52");
		IPEndPoint ^ep = gcnew IPEndPoint(broadcast, 23001);

		array<Byte>^sendBytes=	cmdItini->serialize();



		s->SendTo( sendBytes, ep);
#ifdef TRACE

		Logger::Info(cmdItini->getNID_MESSAGE(),"ATS",broadcast->ToString(),cmdItini->getSize(),BitConverter::ToString(sendBytes),"ThreadSchedule");

#endif // TRACE

		return true;

	}catch ( Exception^ eException ) 
	{
#ifdef TRACE
		Logger::Exception(eException,"ThreadSchedule");  
#endif // TRACE
		Console::WriteLine( "Errore "+eException->Message);
		return false;
	}
}





void ThreadSchedule::Init(){
	Console::WriteLine("Init Schedule session");

}


StateObject ^ ThreadSchedule::SendTCPMsg(int trn, phisicalTrain ^Treno)
{

	const int WAKE_UP = 0;
	const int CHANGE_GOA_LEVEL = 3;
	const int TRN = 4;
	const int SLEEP = 7;
	try
	{

		Messaggi ^wakeUpPkt = gcnew Messaggi();

		wakeUpPkt->setNID_MESSAGE(201);

		wakeUpPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		wakeUpPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(WAKE_UP);
		//set time
		DateTime orarioSupporto3 = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
		TimeSpan ^sinceMidnight =  DateTime::Now - orarioSupporto3;
		wakeUpPkt->setT_TIME((int)sinceMidnight->TotalSeconds/30);

		// Buffer for reading data
		array<Byte>^bytes_buffer1 =wakeUpPkt->serialize();


		Messaggi ^trainRunningNumberPkt = gcnew Messaggi();


		trainRunningNumberPkt->setNID_MESSAGE(201);
		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		trainRunningNumberPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(TRN);

		trainRunningNumberPkt->setT_TIME((int)sinceMidnight->TotalSeconds/30);

		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_OPERATIONAL(trn);


		// Buffer for reading data
		array<Byte>^bytes_buffer2 = trainRunningNumberPkt->serialize();

		Messaggi ^missionPlanPkt = gcnew Messaggi();

		missionPlanPkt->setNID_MESSAGE(200);
		missionPlanPkt->get_pacchettoMissionPlan()->setNID_PACKET(160);
		missionPlanPkt->setT_TIME((int)sinceMidnight->TotalSeconds/30);

		tabOrario->setMissionPlanMessage(trn, missionPlanPkt->get_pacchettoMissionPlan());



		// Buffer for reading data
		array<Byte>^bytes_buffer3 = missionPlanPkt->serialize();

		// Creates the Socket to send data over a TCP connection.
		Socket ^sock = gcnew Socket( System::Net::Sockets::AddressFamily::InterNetwork,System::Net::Sockets::SocketType::Stream,System::Net::Sockets::ProtocolType::Tcp );


		String ^IP = gcnew String(Treno->getIpAddress());
		sock->Connect(IP, Treno->getTcpPort());

		//NetworkStream ^myStream = gcnew NetworkStream(sock);
		sock->Send(bytes_buffer1);
		//sock->BeginSend(bytes_buffer1, 0, wakeUpPkt->getSize(),System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedule::SendCallback ), sock);
		//myStream->Write(bytes_buffer1, 0, wakeUpPkt->getSize());
#ifdef TRACE

		Logger::Info(wakeUpPkt->getNID_MESSAGE(),"ATS",IP->ToString(),wakeUpPkt->getSize(),BitConverter::ToString(bytes_buffer1),"ThreadSchedule");

#endif // TRACE
		sock->Send(bytes_buffer2);
		//sock->BeginSend(bytes_buffer2, 0, trainRunningNumberPkt->getSize() ,System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedule::SendCallback ), sock);
		//myStream->Write(bytes_buffer2, 0, trainRunningNumberPkt->getSize());
#ifdef TRACE

		Logger::Info(trainRunningNumberPkt->getNID_MESSAGE(),"ATS",IP->ToString(),trainRunningNumberPkt->getSize(),BitConverter::ToString(bytes_buffer2),"ThreadSchedule");

#endif // TRACE
		sock->Send(bytes_buffer3);
		//sock->BeginSend(bytes_buffer3, 0, missionPlanPkt->getSize() ,System::Net::Sockets::SocketFlags::None, gcnew AsyncCallback( &ThreadSchedule::SendCallback ), sock);
		//myStream->Write(bytes_buffer3, 0, missionPlanPkt->getSize());
#ifdef TRACE

		Logger::Info(missionPlanPkt->getNID_MESSAGE(),"ATS",IP->ToString(),missionPlanPkt->getSize(),BitConverter::ToString(bytes_buffer3),"ThreadSchedule");

#endif // TRACE

		StateObject^ so2 = gcnew StateObject;
		so2->workSocket = sock;
		sock->BeginReceive( so2->buffer, 0, 17,System::Net::Sockets::SocketFlags::Peek, gcnew AsyncCallback( &ThreadSchedule::ReceiveCallback ), so2 );
		so2->fine=-1;

		return so2;
	}
	catch ( Exception^ e ) 
	{
		Console::WriteLine( "SocketException: {0}", e->Message );
#ifdef TRACE
		Logger::Exception(e,"ThreadSchedule");  
#endif // TRACE
		StateObject^ so2 = gcnew StateObject;

		return so2;
	}


}
void ThreadSchedule::ReceiveCallback(IAsyncResult^ asyncResult){

	StateObject^ so = safe_cast<StateObject^>(asyncResult->AsyncState);
	Socket^ s = so->workSocket;
	try{
		int read = s->EndReceive( asyncResult );

		if ( read < 0 )
		{

			s->BeginReceive( so->buffer, 0, 17,System::Net::Sockets::SocketFlags::Peek, gcnew AsyncCallback( &ThreadSchedule::ReceiveCallback ), so );
		}
		else
		{
			Messaggi ^pktAck = gcnew Messaggi();


			pktAck->deserialize(so->buffer);

#ifdef TRACE

			Logger::Info(pktAck->getNID_MESSAGE(),"IP","ATS",pktAck->getSize(),BitConverter::ToString(so->buffer),"ThreadSchedule");

#endif // TRACE




			cout << "RESPONSE\n" << pktAck->get_pacchettoAcknowledgement()->getQ_MISSION_RESPONSE();


			cout << "DONE\n";

			//All of the data has been read

			s->Close();
			so->fine=1;
		}
	}catch(Exception ^e){

		Console::WriteLine("avevi chiuso il sock");
	}


}

void ThreadSchedule::SendCallback(IAsyncResult^ asyncResult){

	Socket^ so = safe_cast<Socket^>(asyncResult->AsyncState);

	int send = so->EndSend( asyncResult );


}

//se l'itinerario è libero
//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL che 
//che riporti il cambiamento dello stato dell'itinerario
bool ThreadSchedule::richestaItinerarioIXL(int iditinerario){
	if((managerIXL->getItinerario(iditinerario)->getQ_STATOITIN()==typeStateItineraio::itinerarioStatoNonInAtto) | (true)){

		SendBloccItinIXL(iditinerario,typeCmdItinerari::creazione);
		//Thread::Sleep(500);
		Event ^even = EQueueIXL->getEvent();
		if(even!=nullptr){
			StateItinerario ^statoi =even->getEventStateItinerario();
			if(iditinerario==statoi->getNID_ITIN() ){
				if( statoi->getQ_STATOITIN()==typeStateItineraio::itinerarioStatoInAtto  ){
					return true;
				}
			}
		}else{
			//todo: levare se solo per fare test senza produrre i msg di stato IXL
			return true;
		}

	}else{
		Console::WriteLine("itinerario nn libero ritenta");
		return false;

	}
	return false;

}