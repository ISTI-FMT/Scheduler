#include "ThreadListenerATC_IXL.h"
#using <System.dll>
#include "..\\messaggi\\Messaggi.h"
#include "..\\logger\\Logger.h"

#define TRACE

using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;


/*ThreadListenerATC_IXL::ThreadListenerATC_IXL(){

}*/

ThreadListenerATC_IXL::ThreadListenerATC_IXL(ManagerStatoLineaIXL ^MC,ManagerStatoLineaATC ^MA ){
	ManStatoLineaIXL=MC;
	ManStatoLineaATC=MA;
	isMessageReceived=false;
}

void ThreadListenerATC_IXL::ReceiveCallback(IAsyncResult^ asyncResult){

	Console::ForegroundColor = ConsoleColor::Red;
	Console::WriteLine( "ATC/IXL Connected!" );
	UdpClient^ recv_udpClient = (UdpClient^)(asyncResult->AsyncState);


	IPEndPoint^ ipEndPoint;

	array<Byte>^ receiveBytes = recv_udpClient->EndReceive(asyncResult, ipEndPoint);

	Messaggi ^pkt1 = gcnew Messaggi();


	pkt1->deserialize(receiveBytes);

#ifdef TRACE

	Logger::Info(pkt1->getNID_MESSAGE(),ipEndPoint->Address->ToString(),"ATS",pkt1->getSize(),BitConverter::ToString(receiveBytes),"ListenerATC/IXL");

#endif // TRACE


	Console::ForegroundColor = ConsoleColor::Red;
	Console::WriteLine("{0} ATC/IXL ti ha inviato un messaggio",ipEndPoint->Address->ToString());
	Console::WriteLine(pkt1->ToString());
	Console::ResetColor();

	isMessageReceived = true;

	//aggiorniamo il manager  1 è stato linea ATC mentre 101 è stato linea IXL


	switch (pkt1->getNID_MESSAGE())
	{
	case 1: {
		ManStatoLineaATC->addCheckAndSet(pkt1->get_pacchettoStatoLineaATC()->getfirstCDB(),"ATC");
		ManStatoLineaATC->addCheckAndSet(pkt1->get_pacchettoStatoLineaATC()->getlastCDB(),"ATC");
		break;

			}
	case 101: {

		ManStatoLineaIXL->addCheckAndSet(pkt1->get_pacchettoStatoLineaIXL()->getfirstCDB(),"IXL");
		ManStatoLineaIXL->addCheckAndSet(pkt1->get_pacchettoStatoLineaIXL()->getlastCDB(),"IXL");
		ManStatoLineaIXL->addCheckAndSet(pkt1->get_pacchettoStatoItinerario()->getfirstItinerario(),"IXL");
		ManStatoLineaIXL->addCheckAndSet(pkt1->get_pacchettoStatoItinerario()->getlastItinerario(),"IXL");
		break;
			  }

	default:
		break;
	}



}


void ThreadListenerATC_IXL::UDP_Management_receive(){
	try
	{
		Console::ForegroundColor = ConsoleColor::Red;
		Console::Write( "Thread Udp ATC Start... " );
		int port = 23002;
		IPEndPoint^ ipEndPoint = gcnew IPEndPoint(IPAddress::Any,port );
		UdpClient^ udpClient = gcnew UdpClient(ipEndPoint);
		while ( true )
		{
			// Receive a message and write it to the console.




			IAsyncResult ^result = udpClient->BeginReceive(gcnew AsyncCallback(ThreadListenerATC_IXL::ReceiveCallback),udpClient);


			// Do some work while we wait for a message. For this example,
			// we'll just sleep
			while (!isMessageReceived)
			{
				Thread::Sleep(100);
				///isMessageReceived=true;
			}
			isMessageReceived=false;
			// Set the TcpListener on port 13000.


			//Creates a UdpClient for reading incoming data.
			//UdpClient^ receivingUdpClient = gcnew UdpClient( port );

			//IPEndPoint^ RemoteIpEndPoint = gcnew IPEndPoint( IPAddress::Any,0 );


			//array<Byte>^receiveBytes = receivingUdpClient->Receive(  RemoteIpEndPoint );


		}
	}
	catch ( SocketException^ e ) 
	{
#ifdef TRACE
		Logger::Exception(e,"ThreadListenerATC_IXL");  
#endif // TRACE
		Console::ForegroundColor = ConsoleColor::Red;
		Console::WriteLine( "SocketException: {0}", e );
		Console::ResetColor();
	}
	catch ( ThreadAbortException^ abortException ) 
	{

		Console::WriteLine( dynamic_cast<String^>(abortException->ExceptionState) );
	}

}



