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
void provaSerializePacchettoPresentazione(pacchettopresentazione &pkt)
{
	int NID_MESSAGE, L_MESSAGE, T_TRAIN, NID_PACKET, L_PACKET, N_PORT;
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
	cout << "Insert M_PORT" << endl;
	cin >> N_PORT;
	pkt.setM_PORT(N_PORT);
	
}

void provaSerializePacchettoack(pacchettoAcknowledgement &pkt)
{
	int NID_MESSAGE, L_MESSAGE, T_TRAIN, NID_PACKET, L_PACKET, Q_MISSION;
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
	cout << "InsertQMission" << endl;
	cin >> Q_MISSION;
	pkt.setQ_MISSION_RESPONSE(Q_MISSION);
	
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
		cout << "Premi un pulsante per continuare dopo che almeno un treno si è presentato all'ATS" << endl;
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

	ThreadPresentazione ^sd = gcnew ThreadPresentazione(&listaTreni);
	
	
	Thread^ oThread2 = gcnew Thread( gcnew ThreadStart(sd, &ThreadPresentazione::TCP_Management_receive ) );

	oThread2->Start();


	//Thread^ oThread = gcnew Thread( gcnew ThreadStart( &ThreadExample::TCP_Management_receive ) );

	//oThread->Start();

	


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