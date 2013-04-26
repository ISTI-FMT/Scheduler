#include "TabellaOrario.h"
#using <System.dll>
#include "utility.h"
#include "pacchettoMissionPlan.h"
#include "pacchettoAcknowledgement.h"
#include "pacchettoCommandData1.h"
#include "pacchettoCommandData2.h"
#include "pacchettoCommandData3.h"
#include "pacchettopresentazione.h"
#include "phisicalTrainList.h"
#include "String2string.h"
#include "ThreadListenerATC.h"
#include <iostream>
#include "ThreadPresentazione.h"
#include "mapTrenoFisicoLogico.h"
#include "proveSerializzazione.h"

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

		pacchettoCommandData1 wakeUpPkt;

		wakeUpPkt.setNID_MESSAGE(0);
		wakeUpPkt.setNID_PACKET(0);
		wakeUpPkt.setQ_COMMAND_TYPE(WAKE_UP);
		wakeUpPkt.setT_TRAIN(tabella.getFirstTRN());

		byte *buffer1 = new byte[wakeUpPkt.getSize()];
		for(int i = 0; i < wakeUpPkt.getSize(); ++i)
			buffer1[i] = 0;
		
		wakeUpPkt.serializepacchettoCommandData(buffer1);
		stampaBuffer(buffer1, wakeUpPkt.getSize() * 8);

		// Buffer for reading data
		array<Byte>^bytes_buffer1 = gcnew array<Byte>(wakeUpPkt.getSize());

		copiaByteInArray(buffer1, bytes_buffer1, wakeUpPkt.getSize());


		pacchettoCommandData3 trainRunningNumberPkt;

		trainRunningNumberPkt.setNID_MESSAGE(1);
		trainRunningNumberPkt.setNID_PACKET(1);
		trainRunningNumberPkt.setQ_COMMAND_TYPE(TRN);
		trainRunningNumberPkt.setT_TRAIN(tabella.getFirstTRN());
		trainRunningNumberPkt.setNID_OPERATIONAL(tabella.getFirstTRN());

		byte *buffer2 = new byte[trainRunningNumberPkt.getSize()];
		for(int i = 0; i < trainRunningNumberPkt.getSize(); ++i)
			buffer2[i] = 0;
		
		trainRunningNumberPkt.serializepacchettoCommandData(buffer2);
		stampaBuffer(buffer2, trainRunningNumberPkt.getSize() * 8);

		// Buffer for reading data
		array<Byte>^bytes_buffer2 = gcnew array<Byte>(trainRunningNumberPkt.getSize());

		copiaByteInArray(buffer2, bytes_buffer2, trainRunningNumberPkt.getSize());

		pacchettoMissionPlan missionPlanPkt;

		int TRN = tabella.getFirstTRN();
		tabella.setMissionPlanMessage(TRN, missionPlanPkt);

		byte *buffer3 = new byte[missionPlanPkt.getSize()];
		for(int i = 0; i < missionPlanPkt.getSize(); ++i)
			buffer3[i] = 0;
		
		missionPlanPkt.serializeMissionPlanPkt(buffer3);
		stampaBuffer(buffer3, missionPlanPkt.getSize() * 8);

		// Buffer for reading data
		array<Byte>^bytes_buffer3 = gcnew array<Byte>(missionPlanPkt.getSize());

		copiaByteInArray(buffer3, bytes_buffer3, missionPlanPkt.getSize());

		// Creates the Socket to send data over a TCP connection.
		Socket ^sock = gcnew Socket( AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp );
		String ^IP = gcnew String(listaTreni.getFirstTrainIP().c_str());
		sock->Connect(IP, listaTreni.getFirstTrainPort());

		NetworkStream ^myStream = gcnew NetworkStream(sock);

		myStream->Write(bytes_buffer1, 0, wakeUpPkt.getSize());
		myStream->Write(bytes_buffer2, 0, trainRunningNumberPkt.getSize());
		myStream->Write(bytes_buffer3, 0, missionPlanPkt.getSize());

		pacchettoAcknowledgement pktAck;

		byte *buffer4 = new byte[pktAck.getSize()];
		for(int i = 0; i < pktAck.getSize(); ++i)
			buffer4[i] = 0;

		// Buffer for reading data
		array<Byte>^bytes_buffer4 = gcnew array<Byte>(pktAck.getSize());

		myStream->Read(bytes_buffer4, 0, pktAck.getSize());

		copiaArrayInByte(bytes_buffer4, buffer4, pktAck.getSize());

		pktAck.deserialize(buffer4);
		stampaBuffer(buffer4, pktAck.getSize());

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

	Thread^ oThread1 = gcnew Thread( gcnew ThreadStart( &ThreadListenerATC::TCP_Management_receive ) );

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