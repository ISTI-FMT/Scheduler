#include "TabellaOrario.h"
#using <System.dll>
#include "utility.h"

#include "phisicalTrainList.h"
#include "String2string.h"
#include "ThreadListenerATC.h"
#include <iostream>
#include "ThreadPresentazione.h"
#include "mapTrenoFisicoLogico.h"
#include "proveSerializzazione.h"
#include "Messaggi.h"

using namespace std;
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;

phisicalTrainList listaTreni;
TabellaOrario tabella;

void stampaBuffer(byte *buff, int nBit)
{
	cout << nBit << endl;

	for(int j = 0; j < (nBit / 8); ++j)
	{
		for(int k = 7; k >= 0; --k)
		{
			byte mask = 1 << k;
			byte aux = buff[j] & mask;
			char supp = aux?'1':'0';
			cout << supp;
		}
		cout << endl;
	}
	for(int k = (nBit % 8) - 1; k >= 0; --k)
	{
		byte mask = 1 << k;
		byte aux = buff[(nBit / 8) + 1] & mask;
		char supp = aux?'1':'0';
		cout << supp;
	}
	cout << endl;
}


// porta su cui il treno è in ascolto
const int listenerPort = 5610;

/*------------------------------------------------------------------------------------
L'ATS gestisce delle connessioni TCP/IP con gli ATO dei treni sotto il suo controllo.
Attraverso queste connessioni l'ATS invia e riceve messaggi da e verso gli ATO.
------------------------------------------------------------------------------------*/

void TCP_Management()
{
	try
	{
		//Int32 port = listenerPort;
		//IPAddress^ localAddr = IPAddress::Parse( "146.48.84.52" );
		//IPAddress^ localAddr = IPAddress::Parse( "127.0.0.1" );

		int x;
		cout << "Premi un pulsante dopo che almeno un treno si e' presentato all'ATS" << endl;
		cin >> x;
		
		Messaggi ^wakeUpPkt = gcnew Messaggi();
		
		
		wakeUpPkt->setNID_MESSAGE(201);

		
		wakeUpPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		wakeUpPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(WAKE_UP);
		wakeUpPkt->setT_TRAIN(tabella.getFirstTRN());



		
		
		// Buffer for reading data
		array<Byte>^bytes_buffer1 = gcnew array<Byte>(wakeUpPkt->get_pacchettoCommandData()->getSize());

		wakeUpPkt->serialize(bytes_buffer1);


		Messaggi ^trainRunningNumberPkt = gcnew Messaggi();
		

		trainRunningNumberPkt->setNID_MESSAGE(201);
		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_PACKET(161);
		trainRunningNumberPkt->get_pacchettoCommandData()->setQ_COMMAND_TYPE(TRN);
		trainRunningNumberPkt->setT_TRAIN(tabella.getFirstTRN());
		trainRunningNumberPkt->get_pacchettoCommandData()->setNID_OPERATIONAL(tabella.getFirstTRN());

		
		// Buffer for reading data
		array<Byte>^bytes_buffer2 = gcnew array<Byte>(trainRunningNumberPkt->get_pacchettoCommandData()->getSize());

		trainRunningNumberPkt->serialize(bytes_buffer2);

		Messaggi ^missionPlanPkt = gcnew Messaggi();

		missionPlanPkt->setNID_MESSAGE(200);
		missionPlanPkt->get_pacchettoMissionPlan()->setNID_PACKET(160);
		int TRN = tabella.getFirstTRN();
		tabella.setMissionPlanMessage(TRN, missionPlanPkt->get_pacchettoMissionPlan());

	

		// Buffer for reading data
		array<Byte>^bytes_buffer3 = gcnew array<Byte>(missionPlanPkt->get_pacchettoMissionPlan()->getSize());
		
		missionPlanPkt->serialize(bytes_buffer3);
		
		// Creates the Socket to send data over a TCP connection.
		Socket ^sock = gcnew Socket( AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp );
		String ^IP = gcnew String(listaTreni.getFirstTrainIP().c_str());
		sock->Connect(IP, listaTreni.getFirstTrainPort());

		NetworkStream ^myStream = gcnew NetworkStream(sock);

		myStream->Write(bytes_buffer1, 0, wakeUpPkt->get_pacchettoCommandData()->getSize());
		myStream->Write(bytes_buffer2, 0, trainRunningNumberPkt->get_pacchettoCommandData()->getSize());
		myStream->Write(bytes_buffer3, 0, missionPlanPkt->get_pacchettoMissionPlan()->getSize());


		Messaggi ^pktAck = gcnew Messaggi();
		
		pktAck->set_pacchettoAcknowledgement();

		// Buffer for reading data
		array<Byte>^bytes_buffer4 = gcnew array<Byte>(pktAck->get_pacchettoAcknowledgement()->getSize());

		myStream->Read(bytes_buffer4, 0, pktAck->get_pacchettoAcknowledgement()->getSize());

		

		pktAck->deserialize(bytes_buffer4);

		cout << "RESPONSE\n" << pktAck->get_pacchettoAcknowledgement()->getQ_MISSION_RESPONSE();
		

		cout << "DONE\n";
	}
	catch ( SocketException^ e ) 
	{
		Console::WriteLine( "SocketException: {0}", e );
	}

	Console::WriteLine( "\nHit enter to continue..." );
	Console::Read();
}




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

	tabella.leggiTabellaOrario("..\\FileConfigurazione\\TabellaOrario.xml");
	//cout << tabella;


	

	

	ThreadPresentazione ^sd = gcnew ThreadPresentazione(&listaTreni);
	
	
	Thread^ oThread2 = gcnew Thread( gcnew ThreadStart(sd, &ThreadPresentazione::TCP_Management_receive ) );

	oThread2->Start();


	//mapTrenoFisicoLogico ^maps = gcnew mapTrenoFisicoLogico("..\\FileConfigurazione\\MapTreni.xml");

	
	//Console::WriteLine(maps->ToString());

	Thread^ oThread1 = gcnew Thread( gcnew ThreadStart( &ThreadListenerATC::UDP_Management_receive ) );

	oThread1->Start();

	TCP_Management();

	
	//pacchettoAcknowledgement ack;
	//byte *buffer3 = new byte[ack.getSize()];
	//provaSerializePacchettoack(ack);
	//ack.serialize(buffer3);
	//stampaBuffer(buffer3,ack.getSize() );

	Console::WriteLine("Premi un Tasto x USCIRE");

	Console::Read();

	//return 0;
}