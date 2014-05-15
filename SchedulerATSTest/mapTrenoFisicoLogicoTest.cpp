
#include "stdafx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
    using namespace System;
    ref class mapTrenoFisicoLogicoTest;
    
    
    /// <summary>
///Classe di test per mapTrenoFisicoLogicoTest.
///Creata per contenere tutti gli unit test mapTrenoFisicoLogicoTest
///</summary>
	[TestClass]
	public ref class mapTrenoFisicoLogicoTest
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
			///Test per Costruttore mapTrenoFisicoLogico
			///</summary>
	public: [TestMethod]
			void mapTrenoFisicoLogicoConstructorTest()
			{
				mapTrenoFisicoLogico^  target = (gcnew mapTrenoFisicoLogico());
				Assert::IsNotNull(target->ToString());

				CollectionAssert::AllItemsAreNotNull(target->get_Map()[65282]->getIdTrenoListTreniLogici());
				String^ tmpFilename = System::IO::Path::GetTempFileName();
				
				System::IO::FileStream^ writeStream = gcnew System::IO::FileStream(tmpFilename, System::IO::FileMode::Create);
				target->saveXml(writeStream);
				
				writeStream->Close();

				Assert::AreNotEqual(0,target->get_Map()[65282]->getNextLogicTrain());
				Assert::AreNotEqual(0,target->get_Map()[65282]->getCurrentLogicTrain());

				Assert::AreNotEqual(-1,target->get_Map()[65282]->getIdTrenoLogico(0));
			}
	};
}
namespace SchedulerATSTest {
    
}
