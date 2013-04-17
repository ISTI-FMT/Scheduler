#include "TabellaOrario.h"
#using <System.dll>
#include "pacchettoMissionPlan.h"
#include "pacchettoCommandData1.h"
#include <iostream>
using namespace std;
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;

const int listenerPort = 13000;

void TCP_Management()
{
   try
   {

      // Set the TcpListener on port 13000.
      Int32 port = listenerPort;
      IPAddress^ localAddr = IPAddress::Parse( "127.0.0.1" );

      // TcpListener* server = new TcpListener(port);
      TcpListener^ server = gcnew TcpListener( localAddr,port );

      // Start listening for client requests.
      server->Start();

      // Buffer for reading data
      array<Byte>^bytes = gcnew array<Byte>(1024);
      String^ data = nullptr;

      // Enter the listening loop.
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
         Int32 i;

         // Loop to receive all the data sent by the client.
         while ( i = stream->Read( bytes, 0, bytes->Length ) )
         {

            // Translate data bytes to a ASCII String*.
            data = Text::Encoding::ASCII->GetString( bytes, 0, i );
            Console::WriteLine( "Received: {0}", data );

            // Process the data sent by the client.
            data = data->ToUpper();
            array<Byte>^msg = Text::Encoding::ASCII->GetBytes( data );

            // Send back a response.
            stream->Write( msg, 0, msg->Length );
            Console::WriteLine( "Sent: {0}", data );
         }

         // Shutdown and end connection
         client->Close();
      }
   }
   catch ( SocketException^ e ) 
   {
      Console::WriteLine( "SocketException: {0}", e );
   }

   Console::WriteLine( "\nHit enter to continue..." );
   Console::Read();
}

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
	byte buff[100];
	for(int i = 0; i < 100; ++i)
		buff[i] = 0;
	int len = 0;
	pkt.serializepacchettoCommandData(buff);
	stampaBuffer(buff, 80);
}

int main()
{
	TabellaOrario tabella;
	tabella.leggiTabellaOrario("..\\..\\FileConfigurazione\\TabellaOrario.xml");
	cout << tabella;

	byte buff[100];
	for(int i = 0; i < 100; ++i)
		buff[i] = 0;

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

	pacchettoCommandData1 pkt1;
	cout << sizeof(pkt1) << endl;
	provaSerializePacchettoCommandData1(pkt1);

	TCP_Management();

	system("Pause");

}