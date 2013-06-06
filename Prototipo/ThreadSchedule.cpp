#include "ThreadSchedule.h"


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


ThreadSchedule::ThreadSchedule(List<EventQueue^> ^E, TabellaOrario ^tabo, tabellaItinerari ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w)
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
				// se trovi che un numero logico nella mappa

				if(mapTrenoLogFisico->get_Map()->ContainsKey(enginenumber)){
					int trn = mapTrenoLogFisico->get_Map()[enginenumber];
					// cerchi se c'è una missione per lui nella tabella orario
					if(tabOrario->get_TabellaOrario()->ContainsKey(trn)){
						// gli assegni TRN e MISSION
						bool inviato = SendTCPMsg(trn,eventoATO->getEventPresentTrain()); 
						if(inviato){
							Console::WriteLine(" MSG INVIATO ");
							// aspetti che l'orario e se si trova nel posto giusto chiedi a IXL itinerario uscita-

							// se in posizione giusta richiedi itinerario entrata

							// ripeti passo prec prec




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
		array<Byte>^bytes_buffer1 = gcnew array<Byte>(wakeUpPkt->getSize());

		wakeUpPkt->serialize(bytes_buffer1);


		Messaggi ^trainRunningNumberPkt = gcnew Messaggi();


		trainRunningNumberPkt->setNID_MESSAGE(201);
		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		trainRunningNumberPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(TRN);

		trainRunningNumberPkt->setT_TIME((int)sinceMidnight->TotalSeconds/30);

		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_OPERATIONAL(trn);


		// Buffer for reading data
		array<Byte>^bytes_buffer2 = gcnew array<Byte>(trainRunningNumberPkt->getSize());

		trainRunningNumberPkt->serialize(bytes_buffer2);

		Messaggi ^missionPlanPkt = gcnew Messaggi();

		missionPlanPkt->setNID_MESSAGE(200);
		missionPlanPkt->get_pacchettoMissionPlan()->setNID_PACKET(160);
		missionPlanPkt->setT_TIME((int)sinceMidnight->TotalSeconds/30);

		tabOrario->setMissionPlanMessage(trn, missionPlanPkt->get_pacchettoMissionPlan());



		// Buffer for reading data
		array<Byte>^bytes_buffer3 = gcnew array<Byte>(missionPlanPkt->getSize());

		missionPlanPkt->serialize(bytes_buffer3);

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

		pktAck->set_pacchettoAcknowledgement();

		// Buffer for reading data
		array<Byte>^bytes_buffer4 = gcnew array<Byte>(pktAck->getSize());

		myStream->Read(bytes_buffer4, 0, pktAck->getSize());
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
		Console::WriteLine( "SocketException: {0}", e );
#ifdef TRACE
		Logger::Exception(e,"ThreadSchedule");  
#endif // TRACE
		return false;
	}


}