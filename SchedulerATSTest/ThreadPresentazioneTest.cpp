
#include "stdafx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
    using namespace System;
	using namespace System::Threading;
	using namespace System::Threading::Tasks;
	using namespace System::Net::Sockets;
	using namespace System::Net;
    ref class ThreadPresentazioneTest;
    
    
    /// <summary>
///Classe di test per ThreadPresentazioneTest.
///Creata per contenere tutti gli unit test ThreadPresentazioneTest
///</summary>
	[TestClass]
	public ref class ThreadPresentazioneTest
	{

	private:array<Byte>^fromString(String ^msg){
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
			///Test per Costruttore ThreadPresentazione
			///</summary>
	public: [TestMethod]
			void ThreadPresentazioneConstructorTest()
			{
				ManagerMsgATO^  MA = gcnew ManagerMsgATO();
				ThreadPresentazione^  ThreadP = (gcnew ThreadPresentazione(MA));
				Thread^ oThreadTCP_ATO = gcnew Thread( gcnew ThreadStart( ThreadP, &ThreadPresentazione::TCP_Management_receive ) );

				 oThreadTCP_ATO->Start();

				
				
				String ^msgPresentazione  ="D702200002B6602009E32035000E1C0000";
				array<Byte> ^sendBytes = fromString(msgPresentazione);

				Socket ^sock = gcnew Socket( System::Net::Sockets::AddressFamily::InterNetwork,System::Net::Sockets::SocketType::Stream,System::Net::Sockets::ProtocolType::Tcp );
				IPAddress ^broadcastip = IPAddress::Parse("127.0.0.1");
				IPEndPoint ^ep = gcnew IPEndPoint(broadcastip, 13000);
				sock->Connect(ep);
				sock->SendTo( sendBytes, ep);

				sock->Close();
				 Thread::Sleep(1000);
				 ThreadP->RequestStop();
				  Thread::Sleep(200);
			}
	};
}
namespace SchedulerATSTest {
    
}
