#include "ThreadPresentazione.h"
#using <System.dll>
#include "Messaggi.h"
#include "utility.h"
#include "phisicalTrainList.h"
#include "String2string.h"

using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Runtime::InteropServices;


	 ThreadPresentazione::ThreadPresentazione()
	 {
		 
	 }

	 	 ThreadPresentazione::ThreadPresentazione(phisicalTrainList ^lt)
		 :listaTreni(lt)
	 {
		 
	 }

	void  ThreadPresentazione::TCP_Management_receive(){
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
				Console::ForegroundColor = ConsoleColor::DarkGreen;
				Console::Write( "Waiting for a connection... " );

				// Perform a blocking call to accept requests.
				// You could also user server.AcceptSocket() here.

				TcpClient^ client = server->AcceptTcpClient();
				Console::ForegroundColor = ConsoleColor::DarkGreen;
				Console::WriteLine( "Connected!" );
				data = nullptr;

				// Get a stream Object* for reading and writing
				NetworkStream^ stream = client->GetStream();
				
				stream->Read( bytes, 0, bytes->Length );

				Messaggi ^pkt1 = gcnew Messaggi();

				
				pkt1->deserialize(bytes);
				//Console::WriteLine(pkt1.getNID_MESSAGE());
				//Console::WriteLine(pkt1.getL_MESSAGE());
				//Console::WriteLine(pkt1.getM_PORT());

				//Console::WriteLine("{0} ti ha inviato un messaggio",client->Client->RemoteEndPoint->ToString());

				// creo l'oggetto di tipo phisicalTrain
				phisicalTrain ^treno = gcnew phisicalTrain();
				treno->setEngineNumber(pkt1->getNID_ENGINE());
				treno->setTcpPort(pkt1->get_pacchettoPresentazione()->getM_PORT());
				
				treno->setIpAddress((((IPEndPoint^)(client->Client->RemoteEndPoint) )->Address)->ToString());
				// aggiungo il treno alla lista dei treni fisici
				listaTreni->setMapTreni(treno);

				
				String ^stringip = gcnew String(treno->getIpAddress());
				Console::ForegroundColor = ConsoleColor::DarkGreen;
				Console::WriteLine("Aggiunto il treno {0} operativo su {1}:{2} ", treno->getEngineNumber() ,stringip, treno->getTcpPort());

				//data = System::Text::Encoding::ASCII->GetString( bytes, 0, 256 );

				//Console::WriteLine( String::Format( "Received: {0} ", data) );

				// Shutdown and end connection
				client->Close();
				Console::ResetColor();
			}
		}
		catch ( SocketException^ e ) 
		{
			Console::ForegroundColor = ConsoleColor::DarkGreen;
			Console::WriteLine( "SocketException: {0}", e );
			Console::ResetColor();
		}

	}


	void  ThreadPresentazione::stampaBuffer(byte *buff, int nBit)
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