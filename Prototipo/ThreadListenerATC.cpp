#include "ThreadListenerATC.h"
#using <System.dll>
#include "utility.h"

using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;


ThreadListenerATC::ThreadListenerATC(){

}
void ThreadListenerATC::TCP_Management_receive(){
	try
	{
		// Set the TcpListener on port 13000.
		Int32 port = 23002;
		IPAddress^ localAddr = IPAddress::Any;

		// TcpListener* server = new TcpListener(port);
		TcpListener^ server = gcnew TcpListener( localAddr,port );

		// Start listening for client requests.
		server->Start();

		// Buffer for reading data

		//String^ data = nullptr;

		while ( true )
		{
			Console::ForegroundColor = ConsoleColor::Red;
			Console::Write( "Waiting for a connection of ATC... " );

			// Perform a blocking call to accept requests.
			// You could also user server.AcceptSocket() here.

			TcpClient^ client = server->AcceptTcpClient();
			Console::WriteLine( "ATC Connected!" );
			//data = nullptr;

			// Get a stream Object* for reading and writing
			NetworkStream^ stream = client->GetStream();

			pacchettostatolineaatc pkt1;
			int numberOfBytesRead = 0;

			array<Byte>^bytes = gcnew array<Byte>(pkt1.getSize());
			//do
			//{
				//numberOfBytesRead =stream->Read( bytes, 0, bytes->Length );

			//}
			//while ( stream->DataAvailable );

			stream->Read( bytes, 0, bytes->Length );



			byte *buffer2 = new byte[pkt1.getSize()];
			for(int i = 0; i < pkt1.getSize(); ++i)
				buffer2[i] = 0;


			copiaArrayInByte(bytes, buffer2, pkt1.getSize());

			//stampaBuffer(buffer2, pkt1.getSize()*8);

			pkt1.deserialize(buffer2);


			
			
			Console::WriteLine("{0} ATC ti ha inviato un messaggio",client->Client->RemoteEndPoint->ToString());
			Console::WriteLine(pkt1.toPrint());
			Console::ResetColor();

			// creo l'oggetto di tipo phisicalTrain

			// converto da System::String a std::string
			//string ip = String2string((( (IPEndPoint^)(client->Client->RemoteEndPoint) )->Address)->ToString());


			// aggiungo il treno alla lista dei treni fisici

			//data = System::Text::Encoding::ASCII->GetString( bytes, 0, 256 );

			//Console::WriteLine( String::Format( "Received: {0} ", data) );

			// Shutdown and end connection
			client->Close();
		}
	}
	catch ( SocketException^ e ) 
	{
		Console::ForegroundColor = ConsoleColor::DarkGreen;
		Console::WriteLine( "SocketException: {0}", e );
		Console::ResetColor();
	}

}

void ThreadListenerATC::stampaBuffer(byte *buff, int nBit)
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

