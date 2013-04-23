#include "ThreadPresentazione.h"
#using <System.dll>
#include "pacchettopresentazione.h"
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


	 ThreadPresentazione::ThreadPresentazione()
		 :listaTreni(NULL)
	 {
		 
	 }

	 	 ThreadPresentazione::ThreadPresentazione(phisicalTrainList *lt)
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
			array<Byte>^bytes = gcnew array<Byte>(16);
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
				listaTreni->aggiungiTreno(treno);

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