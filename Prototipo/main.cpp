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
#include <iostream>

using namespace std;
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;

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

void provaSerializePacchettoCommandData1(pacchettoCommandData1 &pkt)
{
	int NID_MESSAGE, L_MESSAGE, T_TRAIN, NID_PACKET, L_PACKET, Q_COMMAND_TYPE;
	cout << "Insert NID_MESSAGE" << endl;
	cin >> NID_MESSAGE;
	pkt.setNID_MESSAGE(NID_MESSAGE);
	cout << "Insert L_MESSAGE" << endl;
	cin >> L_MESSAGE;
	pkt.setL_MESSAGE(L_MESSAGE);
	cout << "Insert T_TRAIN" << endl;
	cin >> T_TRAIN;
	pkt.setT_TRAIN(T_TRAIN);
	cout << "Insert NID_PACKET" << endl;
	cin >> NID_PACKET;
	pkt.setNID_PACKET(NID_PACKET);
	cout << "Insert L_PACKET" << endl;
	cin >> L_PACKET;
	pkt.setL_PACKET(L_PACKET);
	cout << "Insert Q_COMMAND_TYPE" << endl;
	cin >> Q_COMMAND_TYPE;
	pkt.setQ_COMMAND_TYPE(Q_COMMAND_TYPE);
	//byte buff[100];
	//for(int i = 0; i < 100; ++i)
	//	buff[i] = 0;
	//int len = 0;
	//pkt.serializepacchettoCommandData(buff);
	//stampaBuffer(buff, 80);
}


// porta su cui il treno � in ascolto
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


		pacchettoCommandData1 wakeUpPkt;
		pacchettoCommandData2 trainRunningNumberPkt;
		pacchettoMissionPlan missionPlanPkt;
		//provaSerializePacchettoCommandData1(pkt1);

		wakeUpPkt.setNID_MESSAGE(0);
		wakeUpPkt.setNID_PACKET(0);
		wakeUpPkt.setQ_COMMAND_TYPE(TRN);
		wakeUpPkt.setT_TRAIN(5);

		byte *buffer1 = new byte[wakeUpPkt.getSize()];
		for(int i = 0; i < wakeUpPkt.getSize(); ++i)
			buffer1[i] = 0;
		
		wakeUpPkt.serializepacchettoCommandData(buffer1);
		stampaBuffer(buffer1, wakeUpPkt.getSize() * 8);

		// Buffer for reading data
		array<Byte>^bytes_buffer = gcnew array<Byte>(pkt1.getSize());

		copiaByteInArray(buffer, bytes_buffer, pkt1.getSize());

		// Creates the Socket to send data over a TCP connection.
		Socket ^sock = gcnew Socket( AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp );
		sock->Connect(localAddr, listenerPort);

		NetworkStream ^myStream = gcnew NetworkStream(sock);

		myStream->Write(bytes_buffer, 0, pkt1.getSize());

		byte *buffer2 = new byte[trainRunningNumberPkt.getSize()];
		for(int i = 0; i < trainRunningNumberPkt.getSize(); ++i)
			buffer2[i] = 0;

		byte *buffer3 = new byte[missionPlanPkt.getSize()];
		for(int i = 0; i < missionPlanPkt.getSize(); ++i)
			buffer3[i] = 0;

		pacchettoAcknowledgement pktAck;

		byte *buffer2 = new byte[pktAck.getSize()];
		for(int i = 0; i < pktAck.getSize(); ++i)
			buffer2[i] = 0;

		// Buffer for reading data
		array<Byte>^bytes_buffer2 = gcnew array<Byte>(pktAck.getSize());

		myStream->Read(bytes_buffer2, 0, pktAck.getSize());

		copiaArrayInByte(bytes_buffer2, buffer2, pktAck.getSize());

		pktAck.deserialize(buffer2);
		stampaBuffer(buffer2, 136);

		cout << "DONE\n";
	}
	catch ( SocketException^ e ) 
	{
		Console::WriteLine( "SocketException: {0}", e );
	}

	Console::WriteLine( "\nHit enter to continue..." );
	Console::Read();
}

phisicalTrainList listaTreni;

public ref class ThreadExample
{
public:
	static void TCP_Management_receive(){
		try
		{
			// Set the TcpListener on port 13000.
			Int32 port = 13000;
			IPAddress^ localAddr = IPAddress::Any;//IPAddress::Parse( "127.0.0.1" );

			// TcpListener* server = new TcpListener(port);
			TcpListener^ server = gcnew TcpListener( localAddr,port );

			// Start listening for client requests.
			server->Start();

			// Buffer for reading data
			array<Byte>^bytes = gcnew array<Byte>(256);
			String^ data = nullptr;

			while ( true )
			{
				Console::Write( "Waiting for a connection... " );

				// Perform a blocking call to accept requests.
				// You could also user server.AcceptSocket() here.

				TcpClient^ client = server->AcceptTcpClient();
				Console::WriteLine( "Connected!" );
				data = nullptr;

				// Get a stream Object* for reading and writing
				NetworkStream^ stream = client->GetStream();
				
				stream->Read( bytes, 0, bytes->Length );

				pacchettopresentazione pkt1;

				byte *buffer2 = new byte[pkt1.getSize()];
				for(int i = 0; i < pkt1.getSize(); ++i)
					buffer2[i] = 0;

				copiaArrayInByte(bytes, buffer2, pkt1.getSize());

				stampaBuffer(buffer2, 136);
				pkt1.deserialize(buffer2);
				//Console::WriteLine(pkt1.getNID_MESSAGE());
				//Console::WriteLine(pkt1.getL_MESSAGE());
				//Console::WriteLine(pkt1.getM_PORT());

				//Console::WriteLine("{0} ti ha inviato un messaggio",client->Client->RemoteEndPoint->ToString());

				// creo l'oggetto di tipo phisicalTrain
				phisicalTrain treno;
				treno.setEngineNumber(pkt1.getNID_ENGINE());
				treno.setTcpPort(pkt1.getM_PORT());
				// converto da System::String a std::string
				string ip = String2string((( (IPEndPoint^)(client->Client->RemoteEndPoint) )->Address)->ToString());
				
				treno.setIpAddress(ip);
				// aggiungo il treno alla lista dei treni fisici
				listaTreni.aggiungiTreno(treno);

				cout << "Aggiunto il treno " << treno.getEngineNumber() << " operativo su " << treno.getIpAddress().c_str() << ":" << treno.getTcpPort() << endl;

				//data = System::Text::Encoding::ASCII->GetString( bytes, 0, 256 );

				//Console::WriteLine( String::Format( "Received: {0} ", data) );

				// Shutdown and end connection
				client->Close();
			}
		}
		catch ( SocketException^ e ) 
		{
			Console::WriteLine( "SocketException: {0}", e );
		}

	}
};



int main()
{
	TabellaOrario tabella;
	tabella.leggiTabellaOrario("..\\FileConfigurazione\\TabellaOrario.xml");
	cout << tabella;

	//byte buff[100];
	//for(int i = 0; i < 100; ++i)
	//	buff[i] = 0;

	/*
	// Prova di serializzazione di pacchetto missione plan
	pacchettoMissionPlan p;
	int x;
	cin >> x;
	p.setNID_MESSAGE(x);
	cin >> x;
	p.setL_MESSAGE(x);
	cin >> x;
	p.setT_TRAIN(x);

	int i = 0;
	p.serializeStructuredHeader(buff, i);

	stampaBuffer(buff,i);
	*/

	//pacchettoCommandData1 pkt1;
	//cout << sizeof(pkt1) << endl;
	//provaSerializePacchettoCommandData1(pkt1);


	Thread^ oThread = gcnew Thread( gcnew ThreadStart( &ThreadExample::TCP_Management_receive ) );

	oThread->Start();

	TCP_Management();


	Console::WriteLine("Premi un Tasto x USCIRE");

	Console::Read();

	//return 0;
}