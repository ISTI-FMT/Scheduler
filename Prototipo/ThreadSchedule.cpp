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
		while(true){
			Thread::Sleep(500);
			wdogs->onNext();
			// aspetta che si presenti un treno
			Event ^eventoATO = EQueueATO->getEvent();
			if(eventoATO!=nullptr){
				int enginenumber = eventoATO->getEventPresentTrain()->getEngineNumber();
				// se trovi che ha numero logico nella mappa mapTrenoLogFisico e si trova nella stazione in cui deve partire

				if(mapTrenoLogFisico->get_Map()->ContainsKey(enginenumber)){
					TrenoFisicoLogico ^infotrenofisico = mapTrenoLogFisico->get_Map()[enginenumber];
					int trn = infotrenofisico->getIdTrenoLogico(0);
					int lastpos =infotrenofisico->getCDBLastPosition();
				
					// cerchi se c'è una missione per lui nella tabella orario
					if((tabOrario->get_TabellaOrario()->ContainsKey(trn)) & (trn>0)){
						//trova gli itinerari  del treno
						List<Fermata^> ^listaitinerari = tabOrario->getItinerariFor(trn);
						int prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(listaitinerari[0]->getIdStazione(),listaitinerari[0]->getIditinerarioUscita());

						if(lastpos==prevfirstcdbu){
							Console::WriteLine("Si trova al posto giusto per partire e gli assegno la missione");
							// gli assegni TRN e MISSION
							bool inviato = SendTCPMsg(trn,eventoATO->getEventPresentTrain()); 
							if(inviato){
								Console::WriteLine(" MSG INVIATO ");

								//List<Fermata^> ^listaitinerari = tabOrario->getItinerariFor(trn);
								for each (Fermata ^fermvar in listaitinerari)
								{

									int resultprecE = tabItinerari->get_CdbPrecItinerario(fermvar->getIdStazione(),fermvar->getIditinerarioEntrata());
									int resultprecU = tabItinerari->get_CdbPrecItinerario(fermvar->getIdStazione(),fermvar->getIditinerarioUscita());

									//itinerario entrata
									if(fermvar->getIditinerarioEntrata()>0){
										//finche nn sono nella posizione giusta
										bool bandiera=true;
										while(bandiera){
											wdogs->OverNext();
											Event ^eventATC = EQueueATC->getEvent();
											if(eventATC!=nullptr){
												if(eventATC->getEventStateCDB()->getNID_CDB()==resultprecE){
													//se l'itinerario è libero
													//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
													//che riporti il cambiamento dello stato dell'itinerario
													richestaItinerarioIXL(fermvar->getIditinerarioEntrata()+fermvar->getIdStazione());


													bandiera=false;
												}else{
													Thread::Sleep(500);
												}

											}else{
												Thread::Sleep(500);
											}

										}
									}
										
									//itinerario uscita
									if(fermvar->getIditinerarioUscita()>0){

										DateTime mezzanotte = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
										TimeSpan ^oraattuale =  (DateTime::Now - mezzanotte);
										int tempo = (int)oraattuale->TotalSeconds/30;
										int  costante= 3;
										int resutl = ((int)fermvar->getOrarioPartenza())-costante;

										while(resutl>=tempo){
											Thread::Sleep(500);
											mezzanotte = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
											oraattuale =  (DateTime::Now - mezzanotte);
											tempo = (int)oraattuale->TotalSeconds/30;
											wdogs->OverNext();
										}
										//controllo posizione 
										if(managerATC->getCDB(resultprecU)->getNID_OPERATIONAL()==trn){
										}
										
										//todo : se ti trovi nel posto giusto


										//se l'itinerario è libero
										//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL 
										//che riporti il cambiamento dello stato dell'itinerario
										richestaItinerarioIXL(fermvar->getIditinerarioUscita()+fermvar->getIdStazione());

									}



								}


							}else{
								//dovresti riprovare ad inviarlo
							Console::WriteLine(" MSG NON INVIATO ");
						}

						}else{
							Console::WriteLine(" MSG NON INVIATO ");
						}

					}
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


bool ThreadSchedule::SendTCPMsg(int trn, phisicalTrain ^Treno)
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

		NetworkStream ^myStream = gcnew NetworkStream(sock);

		myStream->Write(bytes_buffer1, 0, wakeUpPkt->getSize());
#ifdef TRACE

		Logger::Info(wakeUpPkt->getNID_MESSAGE(),"ATS",IP->ToString(),wakeUpPkt->getSize(),BitConverter::ToString(bytes_buffer1),"ThreadSchedule");

#endif // TRACE
		myStream->Write(bytes_buffer2, 0, trainRunningNumberPkt->getSize());
#ifdef TRACE

		Logger::Info(trainRunningNumberPkt->getNID_MESSAGE(),"ATS",IP->ToString(),trainRunningNumberPkt->getSize(),BitConverter::ToString(bytes_buffer2),"ThreadSchedule");

#endif // TRACE
		myStream->Write(bytes_buffer3, 0, missionPlanPkt->getSize());
#ifdef TRACE

		Logger::Info(missionPlanPkt->getNID_MESSAGE(),"ATS",IP->ToString(),missionPlanPkt->getSize(),BitConverter::ToString(bytes_buffer3),"ThreadSchedule");

#endif // TRACE

		Messaggi ^pktAck = gcnew Messaggi();



		// Buffer for reading data
		array<Byte>^bytes_buffer4 = gcnew array<Byte>(17);

		myStream->Read(bytes_buffer4, 0, 17);
		pktAck->deserialize(bytes_buffer4);

#ifdef TRACE

		Logger::Info(pktAck->getNID_MESSAGE(),IP->ToString(),"ATS",pktAck->getSize(),BitConverter::ToString(bytes_buffer4),"ThreadSchedule");

#endif // TRACE




		cout << "RESPONSE\n" << pktAck->get_pacchettoAcknowledgement()->getQ_MISSION_RESPONSE();


		cout << "DONE\n";
		myStream->Close();
		sock->Close();
		return true;
	}
	catch ( Exception^ e ) 
	{
		Console::WriteLine( "SocketException: {0}", e->Message );
#ifdef TRACE
		Logger::Exception(e,"ThreadSchedule");  
#endif // TRACE
		return false;
	}


}


//se l'itinerario è libero
//continuo ad inviare il msg finche nn arriva un evento di stato della linea IXL che 
//che riporti il cambiamento dello stato dell'itinerario
bool ThreadSchedule::richestaItinerarioIXL(int iditinerario){
	bool loop=false;
	if((managerIXL->getItinerario(iditinerario)->getQ_STATOITIN()==typeStateItineraio::itinerarioStatoNonInAtto) | (true)){
		do{
			SendBloccItinIXL(iditinerario,typeCmdItinerari::creazione);
			Thread::Sleep(500);
			if(EQueueIXL->getEvent()!=nullptr){
				if(iditinerario=EQueueIXL->getEvent()->getEventStateItinerario()->getNID_ITIN() ){
					if( EQueueIXL->getEvent()->getEventStateItinerario()->getQ_STATOITIN()==typeStateItineraio::itinerarioStatoInAtto){
						loop=false;
					}
				}
			}
		}while(loop);
	}else{
		Console::WriteLine("itinerario nn libero");
		return false;

	}
	return true;

}