
#include "stdafx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
    using namespace System;
    ref class TabellaStazioniTest;
    
    
    /// <summary>
///Classe di test per TabellaStazioniTest.
///Creata per contenere tutti gli unit test TabellaStazioniTest
///</summary>
	[TestClass]
	public ref class TabellaStazioniTest
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
			///Test per get_CdbPrecItinerario
			///</summary>
	public: [TestMethod]
			void get_CdbTest()
			{
				TabellaStazioni^  target = (gcnew TabellaStazioni()); // TODO: Eseguire l'inizializzazione a un valore appropriato
				int stazione = 13000; 
				int iditin = 901; 
				int expected = 13302; 
				int actual = target->get_CdbPrecItinerario(stazione, iditin);
				Assert::AreEqual(expected, actual);
				expected = 14020;
				actual = target->get_CdbSuccItinerario(stazione, iditin);
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(0,target->get_CdbSuccItinerario(110, 1));
				Assert::AreEqual(0,target->get_CdbPrecItinerario(110, 1));
				CollectionAssert::AllItemsAreNotNull(target->get_Cdb_Itinerario(stazione, iditin));
				Assert::IsNull(target->get_Cdb_Itinerario(1, 1));

				Assert::IsNotNull(target->get_CdbFermata(400,2));
				Assert::IsNotNull(target->get_Cdb_Itinerario(13000,901));

				

				Assert::IsNotNull(target->getMap());

				Assert::IsNotNull(target->ToString());
				Assert::IsNotNull(target->getMap()[13000]->getItinerariid()[901]->ShortDescName);
				Assert::IsNotNull(target->getMap()[15000]->getItinerariid()[906]->ShortDescName);
				Assert::IsNotNull(target->getMap()[400]->getBinari()[0]);
				target->getMap()[400]->getBinari()[0]->setLatoBanchina(3);
				
				Assert::IsNotNull(target->getMap()[400]->getBinari()[0]->ToString());

				Assert::AreEqual(0, target->get_CdbFermata(stazione,5));
				Assert::AreEqual(true,target->get_Direzione_itinerario(15000, 904));
				Assert::IsNull(target->get_infobalise(1, 1));
				Assert::AreEqual(false,target->get_Direzione_itinerario(1, 1));
				
				Assert::IsNull(target->get_infobalise_fromBinario(1, 1,true));


				Assert::IsNull(target->get_infobalise(13000, 1));
				Assert::AreEqual(false,target->get_Direzione_itinerario(13000, 1));
				
				Assert::IsNotNull(target->get_infobalise_fromBinario(400, 5,false));
				
			}
	};
}
namespace SchedulerATSTest {
    
}
