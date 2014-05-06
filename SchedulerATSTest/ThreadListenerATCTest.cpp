
#include "stdafx.h"
#include "stdafx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
	using namespace System;
	using namespace System::Threading;
	using namespace System::Threading::Tasks;
	using namespace System::Net::Sockets;
	using namespace System::Net;
	ref class ThreadListenerUdp2Test;


	/// <summary>
	///Classe di test per ThreadListenerUdpTest.
	///Creata per contenere tutti gli unit test ThreadListenerUdpTest
	///</summary>
	[TestClass]
	public ref class ThreadListenerUdp2Test
	{

	private: array<Byte>^fromString(String ^msg){
				 int len = ( msg->Length / 2)+(msg->Length%2);//+1;
				 array<Byte>^sendBytes = gcnew array<Byte>(len);
				 for (int i = 0; i < sendBytes->Length; i++)
				 {
					 String ^str = msg->Substring(i *2, 2);
					 int h =str->Length;
					 if(h>1){
						 sendBytes[i] = Byte::Parse(str,System::Globalization::NumberStyles::HexNumber);
					 }
				 }
				 return sendBytes;
			 };

			 Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  testContextInstance;
			 /// <summary>
			 ///Ottiene o imposta il contesto dei test, che fornisce
			 ///funzionalità e informazioni sull'esecuzione dei test corrente.
			 ///</summary>
	public: property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  TestContext
			{
				Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  get()
				{
					return testContextInstance;
				}
				System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  value)
				{
					testContextInstance = value;
				}
			}

#pragma region Attributi di test aggiuntivi
			// 
			//Durante la scrittura dei test è possibile utilizzare i seguenti attributi aggiuntivi:
			//
			//Utilizzare ClassInitialize per eseguire il codice prima di eseguire il primo test della classe
			//public: [ClassInitialize]
			//static System::Void MyClassInitialize(TestContext^  testContext)
			//{
			//}
			//
			//Utilizzare ClassCleanup per eseguire il codice dopo l'esecuzione di tutti i test di una classe
			//public: [ClassCleanup]
			//static System::Void MyClassCleanup()
			//{
			//}
			//
			//Utilizzare TestInitialize per eseguire il codice prima di eseguire ciascun test
			//
			//public: [TestInitialize]
			//System::Void MyTestInitialize()
			//{
			//}
			//Utilizzare TestCleanup per eseguire il codice dopo l'esecuzione di ciascun test
			//public: [TestCleanup]
			//System::Void MyTestCleanup()
			//{
			//}
			//
#pragma endregion
			/// <summary>
			///Test per Costruttore ThreadListenerUdp
			///</summary>
	public: [TestMethod]
			void ThreadListenerUdpConstructorTest()
			{
				ManagerStatoLineaIXL^  MC = gcnew ManagerStatoLineaIXL();
				ManagerStatoLineaATC^  MA = gcnew ManagerStatoLineaATC();
				ThreadListenerUdp^  target = (gcnew ThreadListenerUdp(MC, MA));
				Thread^ oThreadUDP = gcnew Thread( gcnew ThreadStart( target, &ThreadListenerUdp::UDP_Management_receive ) );

				oThreadUDP->Start();

				 EventQueue<StateCDB^>  ^EventQATC = gcnew EventQueue<StateCDB^> ();
				 EventQATC->Subscribe(MA);


				String ^msgATC   ="0B022000000411A00B0000FF0000000480000032D200050001004F00000495000043970000FF2300000481000033F50000FF24000004820000283D0000FF020000047F0000300F0001000F0000048E00003FAD0000000000000000000000000000000000000000000000000000";
				String ^msgATC2  ="0B022000000411A00B0000FF0000000480000036C500050001004F00000495000043970000FF2300000481000033F50000FF24000004820000283D0000FF020000047F0000300F0001000F0000048E00003FAD0000000000000000000000000000000000000000000000000000";
				String ^msgATC3  ="0B022000000411A00B0000FF0000000480000036C600050001004F00000495000043970000FF2300000481000033F50000FF24000004820000283D0000FF020000047F0000300F0001000F0000048E00003FAD0000000000000000000000000000000000000000000000000000";
				String ^msgATC4  ="0B022000000411A00B0000FF0000000480000037DE00050001004F00000495000043970000FF2300000481000033F50000FF24000004820000283D0000FF020000047F0000300F0001000F0000048E00003FAD0000000000000000000000000000000000000000000000000000";
				array<Byte> ^sendBytes = fromString(msgATC);
				array<Byte> ^sendBytes2 = fromString(msgATC2);
				array<Byte> ^sendBytes3 = fromString(msgATC3);
				array<Byte> ^sendBytes4 = fromString(msgATC4);

				Socket ^s = gcnew Socket(System::Net::Sockets::AddressFamily::InterNetwork, System::Net::Sockets::SocketType::Dgram,
					System::Net::Sockets::ProtocolType::Udp);

				IPAddress ^broadcast = IPAddress::Parse("127.0.0.1");
				IPEndPoint ^ep = gcnew IPEndPoint(broadcast, 4010);

				s->SendTo( sendBytes, ep);
				s->Close();

				s = gcnew Socket(System::Net::Sockets::AddressFamily::InterNetwork, System::Net::Sockets::SocketType::Dgram,
					System::Net::Sockets::ProtocolType::Udp);
				s->SendTo( sendBytes, ep);
				s->Close();

				s = gcnew Socket(System::Net::Sockets::AddressFamily::InterNetwork, System::Net::Sockets::SocketType::Dgram,
					System::Net::Sockets::ProtocolType::Udp);
				s->SendTo( sendBytes2, ep);
				s->Close();
				Thread::Sleep(10000);
				s = gcnew Socket(System::Net::Sockets::AddressFamily::InterNetwork, System::Net::Sockets::SocketType::Dgram,
					System::Net::Sockets::ProtocolType::Udp);
				s->SendTo( sendBytes3, ep);
				s->Close();
				s = gcnew Socket(System::Net::Sockets::AddressFamily::InterNetwork, System::Net::Sockets::SocketType::Dgram,
					System::Net::Sockets::ProtocolType::Udp);
				s->SendTo( sendBytes4, ep);


				
				 Thread::Sleep(10000);
				 Assert::IsNotNull(MA->getCDB(13301));
				  Assert::IsNotNull(MA->getCDB(302));
				 target->RequestStop();
				  Thread::Sleep(200);
			}
		
	};
}
namespace SchedulerATSTest {

}
