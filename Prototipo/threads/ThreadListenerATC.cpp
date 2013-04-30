#include "ThreadListenerATC.h"
#using <System.dll>
#include "..\\utility.h"
#include "..\\messaggi\\Messaggi.h"

using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;


ThreadListenerATC::ThreadListenerATC(){

}
void ThreadListenerATC::UDP_Management_receive(){
	try
	{
		// Set the TcpListener on port 13000.
		Int32 port = 23002;
		
		//Creates a UdpClient for reading incoming data.
		UdpClient^ receivingUdpClient = gcnew UdpClient( port );

		//Creates an IPEndPoint to record the IP Address and port number of the sender.  
		// The IPEndPoint will allow you to read datagrams sent from any source.
		
		
		while ( true )
		{
			IPEndPoint^ RemoteIpEndPoint = gcnew IPEndPoint( IPAddress::Any,0 );
			Console::ForegroundColor = ConsoleColor::Red;
			Console::Write( "Waiting for a connection of ATC... " );

			array<Byte>^receiveBytes = receivingUdpClient->Receive(  RemoteIpEndPoint );

			Console::ForegroundColor = ConsoleColor::Red;
			Console::WriteLine( "ATC Connected!" );
			//data = nullptr;


			Messaggi ^pkt1 = gcnew Messaggi();
		
			//pkt1->set_pacchettoStatoLineaATC();
			
						

			pkt1->deserialize(receiveBytes);


			
			Console::ForegroundColor = ConsoleColor::Red;
			Console::WriteLine("{0} ATC ti ha inviato un messaggio",RemoteIpEndPoint->Address->ToString());
			Console::WriteLine(pkt1->get_pacchettoStatoLineaATC()->toPrint());
			Console::ResetColor();

			
		}
	}
	catch ( SocketException^ e ) 
	{
		Console::ForegroundColor = ConsoleColor::Red;
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

