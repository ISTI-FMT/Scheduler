#include "ThreadListenerUdp.h"
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


ThreadListenerUdp::ThreadListenerUdp(ManagerStatoLineaIXL ^MC,ManagerStatoLineaATC ^MA )
{
	ManStatoLineaIXL=MC;
	ManStatoLineaATC=MA;
	isMessageReceived=false;
	try
	{
		if(!Int32::TryParse(System::Configuration::ConfigurationSettings::AppSettings["port_UDP_receive"],port))
		{
			port=4010;
		}
	} 
	catch(System::Configuration::ConfigurationException  ^error)
	{
		String ^eerr = error->Message;
		Console::WriteLine("Errore configurazione port_UDP_receive: {0}",eerr);
		port=4010;
	}

	Console::WriteLine("PORT UDP Receive: {0}",port);
	_shouldStop=false;
	end_byte_old_IXL = nullptr;
	end_byte_old_ATC = nullptr;
}

bool ThreadListenerUdp::ConfrontaArrayByte(array<Byte>^A,array<Byte>^B)
{
	bool scarta = false;
	if(B==nullptr){

		return scarta;
	}else{
		if(B->Length!=A->Length){

			return scarta;
		}
	}
	// header messaggio nid_msg 8 + l_msg 11 + T_Time 32 51/8=6.38
	for (int ind=7;ind<B->Length;ind++)
	{
		//String ^A_string = B[ind].ToString();
		//String ^B_string = A[ind].ToString();
		Byte ^A_s = A[ind];
		Byte ^B_s = B[ind];
		if(A_s->Equals(B_s)){
			scarta=true;
		}else{
			scarta=false; 

			break;
		}
	}
	return scarta;
}

void ThreadListenerUdp::ReceiveCallback(IAsyncResult^ asyncResult)
{
	UdpClient^ recv_udpClient = (UdpClient^)(asyncResult->AsyncState);
	IPEndPoint^ ipEndPoint= gcnew IPEndPoint(IPAddress::Any,port );
	array<Byte>^ receiveBytes = recv_udpClient->EndReceive(asyncResult, ipEndPoint);

	Messaggi ^pkt1 = gcnew Messaggi();
	isMessageReceived = true;

	//se il messaggio ricevuto non contiene una modifica dello stato
	//rispetto al messaggio precedente, viene scartato (scarta = true)
	bool scarta=false;

	int NID_MESSAGE= utility::pop(receiveBytes, 8, 0);

	if(NID_MESSAGE==(int)MessageID::StatoLineaIXL)
	{
		scarta = ConfrontaArrayByte(receiveBytes,end_byte_old_IXL);
		if(!scarta){
			end_byte_old_IXL=receiveBytes;
		}
	}
	else
	{
		scarta = ConfrontaArrayByte(receiveBytes,end_byte_old_ATC);
		if(!scarta){
			end_byte_old_ATC=receiveBytes;
		}
	}

	if(!scarta){
		String ^mittente = gcnew String("Sconosciuto");
		if(NID_MESSAGE==(int)MessageID::StatoLineaATC)
			mittente="ATC";
		if(NID_MESSAGE==(int)MessageID::StatoLineaIXL)
			mittente="IXL";
		Console::WriteLine( "{0} Connected! Messaggio Accettato",mittente );
		pkt1->deserialize(receiveBytes);


#ifdef TRACE

		Logger::Info(pkt1->getNID_MESSAGE(),mittente+"->ATS",ipEndPoint->Address->ToString(),pkt1->getSize(),BitConverter::ToString(receiveBytes),"ListenerATC/IXL");

#endif // TRACE


		Console::ForegroundColor = ConsoleColor::Red;
		Console::WriteLine("{0} ATC/IXL ti ha inviato un messaggio",ipEndPoint->Address->ToString());
		Console::ResetColor();

		//aggiorniamo il manager
		//11 è stato linea ATC mentre 1 è stato linea IXL
		switch (pkt1->getNID_MESSAGE())
		{
		case MessageID::StatoLineaATC: 
			{
				ManStatoLineaATC->addCheckAndSet(pkt1->get_pacchettoPositionDataATC()->getListCDB(),"ATC");
				Console::ForegroundColor = ConsoleColor::White;
				Console::WriteLine("ricevuto messaggio da ATC");
				break;
			}
		case  MessageID::StatoLineaIXL: 
			{
				ManStatoLineaIXL->addCheckAndSet(pkt1->get_pacchettoStatoLineaIXL()->getCDB(),"IXL");
				Console::ForegroundColor = ConsoleColor::White;
				Console::WriteLine("ricevuto messaggio da IXL");
				break;
			}

		default:
			break;
		}
	}
}


void ThreadListenerUdp::UDP_Management_receive()
{
	try
	{
		Console::ForegroundColor = ConsoleColor::Red;
		Console::WriteLine( "Thread Udp ATC Start... " );

		IPEndPoint^ ipEndPoint = gcnew IPEndPoint(IPAddress::Any,port );
		UdpClient^ udpClient = gcnew UdpClient(ipEndPoint);
		udpClient->Client->ReceiveBufferSize=14048;
		while ( !_shouldStop )
		{
			IAsyncResult ^result = udpClient->BeginReceive(gcnew AsyncCallback(ThreadListenerUdp::ReceiveCallback),udpClient);

			while (!isMessageReceived & !_shouldStop)
			{
				Thread::Sleep(100);
			}
			isMessageReceived=false;
		}
	}
	catch ( SocketException^ e ) 
	{
#ifdef TRACE
		Logger::Exception(e,"ThreadListenerUdp");  
#endif // TRACE
		Console::ForegroundColor = ConsoleColor::Red;
		Console::WriteLine( "SocketException: {0}", e );
		Console::ResetColor();
	}
	catch ( ThreadAbortException^ abortException ) 
	{

#ifdef TRACE
		Logger::Exception(abortException,"ThreadListenerUdp");  
#endif // TRACE
		Console::WriteLine( dynamic_cast<String^>(abortException->ExceptionState) );
	}
}

void ThreadListenerUdp::RequestStop()
{
	_shouldStop = true;
}

