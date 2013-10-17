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
	port = 4010;
	_shouldStop=false;
	end_byte_old = nullptr;
}

void ThreadListenerATC_IXL::ReceiveCallback(IAsyncResult^ asyncResult){
	//Thread::Sleep(1000);
	Console::ForegroundColor = ConsoleColor::Red;
	Console::WriteLine( "ATC/IXL Connected!" );
	Console::ForegroundColor = ConsoleColor::White;
	UdpClient^ recv_udpClient = (UdpClient^)(asyncResult->AsyncState);

	//Console::WriteLine("{0} ttl",recv_udpClient->Ttl);

	IPEndPoint^ ipEndPoint;

	array<Byte>^ receiveBytes = recv_udpClient->EndReceive(asyncResult, ipEndPoint);

	Messaggi ^pkt1 = gcnew Messaggi();

	int len =receiveBytes->Length;

	int index=0;
	bool scarta=false;
	if(len>50){
		array<Byte>^ end_byte = gcnew array<Byte>(1316); 
		for (int i = 8; i < len; i++)
		{
			end_byte[index]=receiveBytes[i];
			index++;
		}
		if(end_byte_old==nullptr){
			end_byte_old=end_byte;
		}else{
			int ind=0;
			for each (Byte ^Bytevar in end_byte_old)
			{
				String ^A =  Bytevar->ToString();
				String ^B = end_byte[ind].ToString();
				if(A->Equals(B)){
					scarta=true;
				}else{
					scarta=false; 
					end_byte_old=end_byte;
					break;
				}
				ind++;
			}

			isMessageReceived = true;
		}
	}else{
		array<Byte>^ end_byte = gcnew array<Byte>(39); 
		for (int i = 8; i < len; i++)
		{
			end_byte[index]=receiveBytes[i];
			index++;
		}
		if(end_byte_old_ATC==nullptr){
			end_byte_old_ATC=end_byte;
		}else{
			int ind=0;
			for each (Byte ^Bytevar in end_byte_old_ATC)
			{
				String ^A =  Bytevar->ToString();
				String ^B = end_byte[ind].ToString();
				if(A->Equals(B)){
					scarta=true;
				}else{
					scarta=false; 
					end_byte_old_ATC=end_byte;
					break;
				}
				ind++;
			}

			isMessageReceived = true;
		}


	}
	if(!scarta){
		pkt1->deserialize(receiveBytes);


#ifdef TRACE

		Logger::Info(pkt1->getNID_MESSAGE(),"ATC/IXL->ATS",ipEndPoint->Address->ToString(),pkt1->getSize(),BitConverter::ToString(receiveBytes),"ListenerATC/IXL");

#endif // TRACE


		Console::ForegroundColor = ConsoleColor::Red;
		Console::WriteLine("{0} ATC/IXL ti ha inviato un messaggio",ipEndPoint->Address->ToString());
		//Console::WriteLine(pkt1->ToString());
		Console::ResetColor();

		isMessageReceived = true;

		//aggiorniamo il manager  11 è stato linea ATC mentre 1 è stato linea IXL


		switch (pkt1->getNID_MESSAGE())
		{
		case MessATC::StatoLineaATC: {
			ManStatoLineaATC->addCheckAndSet(pkt1->get_pacchettoPositionDataATC()->getListCDB(),"ATC");
			break;

									 }
		case  MessIXL::StatoLineaIXL: {

			ManStatoLineaIXL->addCheckAndSet(pkt1->get_pacchettoStatoLineaIXL()->getCDB(),"IXL");
			//ManStatoLineaIXL->addCheckAndSet(pkt1->get_pacchettoStatoItinerario()->getItinerario(),"IXL");

			break;
									  }

		default:
			break;
		}


	}
}


void ThreadListenerATC_IXL::UDP_Management_receive(){
	try
	{
		Console::ForegroundColor = ConsoleColor::Red;
		Console::Write( "Thread Udp ATC Start... " );

		IPEndPoint^ ipEndPoint = gcnew IPEndPoint(IPAddress::Any,port );
		UdpClient^ udpClient = gcnew UdpClient(ipEndPoint);
		udpClient->Client->ReceiveBufferSize=2048;
		while ( !_shouldStop )
		{
			// Receive a message and write it to the console.




			IAsyncResult ^result = udpClient->BeginReceive(gcnew AsyncCallback(ThreadListenerATC_IXL::ReceiveCallback),udpClient);


			// Do some work while we wait for a message. For this example,
			// we'll just sleep
			while (!isMessageReceived & !_shouldStop)
			{
				Thread::Sleep(100);
				////isMessageReceived=true;
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

#ifdef TRACE
		Logger::Exception(abortException,"ThreadListenerATC_IXL");  
#endif // TRACE
		Console::WriteLine( dynamic_cast<String^>(abortException->ExceptionState) );
	}

}


void ThreadListenerATC_IXL::RequestStop()
{
	_shouldStop = true;
}
