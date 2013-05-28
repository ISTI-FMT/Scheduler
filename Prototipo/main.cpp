#include "tabellaOrario\\TabellaOrario.h"
#using <System.dll>
#include "utility.h"

#include "phisicalTrainList.h"
#include "String2string.h"
#include "threads\\ThreadListenerATC_IXL.h"
#include <iostream>
#include "threads\\ThreadPresentazione.h"
#include "mapTrenoFisicoLogico.h"
#include "messaggi\\Messaggi.h"
#include "form\\SchedulerForm.h"
#include "logger\\Logger.h"
#include "Itinerari\\tabellaItinerari.h"
#include "Itinerari\\tabellaFermate.h"

using namespace System::Diagnostics;
using namespace std;
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;

using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;


/*------------------------------------------------------------------------------------
L'ATS gestisce delle connessioni TCP/IP con gli ATO dei treni sotto il suo controllo.
Attraverso queste connessioni l'ATS invia e riceve messaggi da e verso gli ATO.
------------------------------------------------------------------------------------*/

/*void TCP_Management(phisicalTrain ^Treno, TabellaOrario ^tabella)
{
	try
	{


		Messaggi ^wakeUpPkt = gcnew Messaggi();


		wakeUpPkt->setNID_MESSAGE(201);


		wakeUpPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		wakeUpPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(WAKE_UP);
		wakeUpPkt->setT_TRAIN(tabella->getFirstTRN());





		// Buffer for reading data
		array<Byte>^bytes_buffer1 = gcnew array<Byte>(wakeUpPkt->getSize());

		wakeUpPkt->serialize(bytes_buffer1);


		Messaggi ^trainRunningNumberPkt = gcnew Messaggi();


		trainRunningNumberPkt->setNID_MESSAGE(201);
		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		trainRunningNumberPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(TRN);
		trainRunningNumberPkt->setT_TRAIN(tabella->getFirstTRN());
		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_OPERATIONAL(tabella->getFirstTRN());


		// Buffer for reading data
		array<Byte>^bytes_buffer2 = gcnew array<Byte>(trainRunningNumberPkt->getSize());

		trainRunningNumberPkt->serialize(bytes_buffer2);

		Messaggi ^missionPlanPkt = gcnew Messaggi();

		missionPlanPkt->setNID_MESSAGE(200);
		missionPlanPkt->get_pacchettoMissionPlan()->setNID_PACKET(160);
		int TRN = tabella->getFirstTRN();
		tabella->setMissionPlanMessage(TRN, missionPlanPkt->get_pacchettoMissionPlan());



		// Buffer for reading data
		array<Byte>^bytes_buffer3 = gcnew array<Byte>(missionPlanPkt->getSize());

		missionPlanPkt->serialize(bytes_buffer3);

		// Creates the Socket to send data over a TCP connection.
		Socket ^sock = gcnew Socket(System::Net::Sockets::AddressFamily::InterNetwork,System::Net::Sockets::SocketType::Stream,System::Net::Sockets::ProtocolType::Tcp );


		String ^IP = gcnew String(Treno->getIpAddress());
		sock->Connect(IP, Treno->getTcpPort());

		NetworkStream ^myStream = gcnew NetworkStream(sock);

		myStream->Write(bytes_buffer1, 0, wakeUpPkt->getSize());
#ifdef TRACE

		Logger::Info(wakeUpPkt->getNID_MESSAGE(),"ATS",IP->ToString(),wakeUpPkt->getSize(),BitConverter::ToString(bytes_buffer1),"Init");

#endif // TRACE
		myStream->Write(bytes_buffer2, 0, trainRunningNumberPkt->getSize());
#ifdef TRACE

		Logger::Info(trainRunningNumberPkt->getNID_MESSAGE(),"ATS",IP->ToString(),trainRunningNumberPkt->getSize(),BitConverter::ToString(bytes_buffer2),"Init");

#endif // TRACE
		myStream->Write(bytes_buffer3, 0, missionPlanPkt->getSize());
#ifdef TRACE

		Logger::Info(missionPlanPkt->getNID_MESSAGE(),"ATS",IP->ToString(),missionPlanPkt->getSize(),BitConverter::ToString(bytes_buffer3),"Init");

#endif // TRACE

		Messaggi ^pktAck = gcnew Messaggi();

		pktAck->set_pacchettoAcknowledgement();

		// Buffer for reading data
		array<Byte>^bytes_buffer4 = gcnew array<Byte>(pktAck->getSize());

		myStream->Read(bytes_buffer4, 0, pktAck->getSize());
		pktAck->deserialize(bytes_buffer4);

#ifdef TRACE

		Logger::Info(pktAck->getNID_MESSAGE(),IP->ToString(),"ATS",pktAck->getSize(),BitConverter::ToString(bytes_buffer4),"Init");

#endif // TRACE




		cout << "RESPONSE\n" << pktAck->get_pacchettoAcknowledgement()->getQ_MISSION_RESPONSE();


		cout << "DONE\n";
		myStream->Close();
		sock->Close();
	}
	catch ( SocketException^ e ) 
	{
		Console::WriteLine( "SocketException: {0}", e );
	}


}
*/


int main()
{
	/*proveSerializzazione serial;

	pacchettostatolineaatc pkt1;
	serial.provaSerializePacchettostatolineaatc(pkt1,0);

	byte *buffer2 = new byte[pkt1.getSize()];

	for(int i = 0; i < pkt1.getSize(); ++i)
	buffer2[i] = 0;

	pkt1.serialize(buffer2);

	array<Byte>^bytes_buffer4 = gcnew array<Byte>(pkt1.getSize());
	copiaByteInArray(buffer2, bytes_buffer4, pkt1.getSize());
	for each (Byte var in bytes_buffer4)
	{
	Console::WriteLine(var);
	}


	stampaBuffer(buffer2, 145);*/

	/*proveSerializzazione serial;

	pacchettopresentazione pkt1;

	serial.provaSerializePacchettoPresentazione(pkt1);

	byte *buffer2 = new byte[pkt1.getSize()];

	for(int i = 0; i < pkt1.getSize(); ++i)
	buffer2[i] = 0;

	pkt1.serialize(buffer2);

	array<Byte>^bytes_buffer4 = gcnew array<Byte>(pkt1.getSize());
	copiaByteInArray(buffer2, bytes_buffer4, pkt1.getSize());

	Console::WriteLine("Premi un Tasto x USCIRE");

	Console::Read();*/
	//	Trace::AutoFlush = true;
	// Trace::Indent();
	// Trace::WriteLine( "Entering Main" );
	// Trace::TraceInformation("Hello world");

	
/*	TabellaOrario ^tabella = gcnew TabellaOrario;

	tabella->leggiTabellaOrario("..\\FileConfigurazione\\TabellaOrario.xml");
	
	phisicalTrainList ^listaTreni = gcnew phisicalTrainList();

	



	ThreadPresentazione ^sd = gcnew ThreadPresentazione(listaTreni);


	Thread^ oThread2 = gcnew Thread( gcnew ThreadStart(sd, &ThreadPresentazione::TCP_Management_receive ) );

	oThread2->Start();
	


	//mapTrenoFisicoLogico ^maps = gcnew mapTrenoFisicoLogico("..\\FileConfigurazione\\MapTreni.xml");


	//Console::WriteLine(maps->ToString());

	Thread^ oThread1 = gcnew Thread( gcnew ThreadStart( &ThreadListenerATC::UDP_Management_receive ) );

	oThread1->Start();

	while(listaTreni->is_Empthy()){

		//Console::WriteLine("Nessun Treno Si è presentato");
	}

	TCP_Management(listaTreni->getPrimo(), tabella);



	Console::WriteLine("Premi un Tasto x USCIRE");

	Console::Read();

	oThread1->Abort("Thread ATC UDP Listener Chiuso");
	oThread2->Abort();*/

#ifdef TRACE
			 Logger::Info("main"," New Run Application");  
#endif // TRACE
	Prototipo::SchedulerForm ^form = gcnew Prototipo::SchedulerForm();

	System::Windows::Forms::Application::Run(form);

	return 0;
}