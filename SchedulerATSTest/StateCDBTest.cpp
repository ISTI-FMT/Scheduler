
#include "stdafx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
    using namespace System;
    ref class StateCDBTest;
    
    
    /// <summary>
///Classe di test per StateCDBTest.
///Creata per contenere tutti gli unit test StateCDBTest
///</summary>
	[TestClass]
	public ref class StateCDBTest
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
			///Test per Costruttore StateCDB
			///</summary>
	public: [TestMethod]
			void StateCDBConstructorTest()
			{
				int nid = 10; 
				QStateCDB state = QStateCDB::cdbLibero; 
				QStateDeviatoio dev = QStateDeviatoio::deviatoioStatoIgnoto; 
				int idltrain = 350;
				int idftrain = 3440; 
				StateCDB^  target = (gcnew StateCDB(nid, state, dev, idltrain, idftrain));
				StateCDB^  target2 = (gcnew StateCDB(nid, state, dev, idltrain));
				StateCDB^  target3 = (gcnew StateCDB(nid, state, dev));
				target3 = (gcnew StateCDB(nid, 0, 0));
				Assert::IsTrue(true, "Exception was properly thrown");
				Assert::IsNotNull(target->ToString());
			}
			/// <summary>
			///Test per Clone
			///</summary>
	public: [TestMethod]
			void CloneTest()
			{
				int nid = 10; 
				QStateCDB state = QStateCDB::cdbLibero; 
				QStateDeviatoio dev = QStateDeviatoio::deviatoioStatoIgnoto; 
				int idltrain = 350;
				int idftrain = 3440; 
				StateCDB^  target = (gcnew StateCDB(nid, state, dev, idltrain, idftrain));
				
				StateCDB^  actual= target->Clone();
				Assert::AreEqual(target, actual);
				Assert::AreNotSame(target, actual);
			}
			/// <summary>
			///Test per Update
			///</summary>
	public: [TestMethod]
			void UpdateTest()
			{
				StateCDB^  target = (gcnew StateCDB(10, QStateCDB::cdbLibero,QStateDeviatoio::deviatoioStatoIgnoto,55,11)); 
				int nid = 10; 
				QStateCDB state = QStateCDB::cdbImpegnato; 
				QStateDeviatoio dev = QStateDeviatoio::deviatoioNormale; 
				int idltrain = 350;
				int idftrain = 3440; 
				StateCDB^  newcdb = (gcnew StateCDB(nid, state, dev, idltrain, idftrain));
				
				bool actual = target->Update(newcdb);
				Assert::AreEqual(target, newcdb);
			}
			/// <summary>
			///Test per Equals
			///</summary>
	public: [TestMethod]
			void EqualsTest()
			{
				int nid = 10; 
				QStateCDB state = QStateCDB::cdbImpegnato; 
				QStateDeviatoio dev = QStateDeviatoio::deviatoioNormale; 
				int idltrain = 350;
				int idftrain = 3440; 
				StateCDB^  target = (gcnew StateCDB(nid, state, dev, idltrain, idftrain));
			
				StateCDB^  second = (gcnew StateCDB(nid, state, dev, idltrain, idftrain));
				
				
				bool actual = target->Equals(second);
				Assert::AreEqual(true, actual);

				StateCDB^  tre = (gcnew StateCDB());
				actual = target->Equals(tre);
				Assert::AreEqual(false, actual);

			}
	};
}
namespace SchedulerATSTest {
    
}
