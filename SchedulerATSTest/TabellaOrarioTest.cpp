
#include "stdafx.h"
#include "stdafx.h"
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
    using namespace System;
    ref class TabellaOrarioTest;
    
    
    /// <summary>
///Classe di test per TabellaOrarioTest.
///Creata per contenere tutti gli unit test TabellaOrarioTest
///</summary>
	[TestClass]
	public ref class TabellaOrarioTest
	{

	private: Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  testContextInstance;
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
			///Test per Costruttore TabellaOrario
			///</summary>
	public: [TestMethod]
			void TabellaOrarioConstructorTest()
			{
				TabellaStazioni^  T = gcnew TabellaStazioni(); 
				TabellaOrario^  target = (gcnew TabellaOrario(T));

				String^ tmpFilename = System::IO::Path::GetTempFileName();
				System::IO::FileStream^ writeStream = gcnew System::IO::FileStream(tmpFilename, System::IO::FileMode::Create);
				target->ScriviTabellaOrario(writeStream);
				
				writeStream->Close();

				Assert::IsNotNull(target->ToString());
				Assert::IsNotNull(target->getFirstTRN());
				CollectionAssert::AllItemsAreNotNull(target->get_TabellaOrario());
				//target->ScriviTabellaOrario();
				/*System::Xml::Serialization::XmlSerializer ^serializer = gcnew System::Xml::Serialization::XmlSerializer(TabellaOrario::typeid);
				System::IO::StreamWriter ^stream = gcnew System::IO::StreamWriter("C:\\test.xml");
			     serializer->Serialize(stream, target);*/
			}
			/// <summary>
			///Test per getItinerariFor
			///</summary>
	public: [TestMethod]
			void getItinerariForTest()
			{
				TabellaOrario^  target = (gcnew TabellaOrario()); 
				int TRN = 1155; // 
				List<Fermata^ >^  actual =  target->getItinerariFor(TRN);
				Assert::IsNull(actual);
				TabellaStazioni^  T = gcnew TabellaStazioni(); 
				target = (gcnew TabellaOrario(T)); 
				TRN = 1151; 
				actual =  target->getItinerariFor(TRN);

				CollectionAssert::AllItemsAreNotNull(actual);
			}
			/// <summary>
			///Test per getFermateFor
			///</summary>
	public: [TestMethod]
			void getFermateForTest()
			{
				TabellaOrario^  target = (gcnew TabellaOrario()); 
				int TRN = 1155; // 
				List<Fermata^ >^  actual =  target->getFermateFor(TRN);
				Assert::IsNull(actual);
				TabellaStazioni^  T = gcnew TabellaStazioni(); 
				target = (gcnew TabellaOrario(T)); 
				TRN = 1151; 
				actual =  target->getFermateFor(TRN);
				CollectionAssert::AllItemsAreNotNull(actual);
			}
			/// <summary>
			///Test per setMissionPlanMessage
			///</summary>
	public: [TestMethod]
			void setMissionPlanMessageTest()
			{
				TabellaStazioni^  T = gcnew TabellaStazioni(); 
				TabellaOrario^  target = (gcnew TabellaOrario(T)); 
				int TRN = 1166; 
				pacchettoMissionData^  pkt = gcnew pacchettoMissionData(); 
				List<ProfiloVelocita^ >^  pvel = nullptr; 
				target->setMissionPlanMessage(TRN, pkt, pvel);
				CollectionAssert::AllItemsAreNotNull(pkt->getlistMission());
			}
	};
}
namespace SchedulerATSTest {
    
}
