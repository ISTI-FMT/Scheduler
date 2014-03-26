
#include "stdafx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
    using namespace System;
    ref class physicalTrainTest;
    
    
    /// <summary>
///Classe di test per physicalTrainTest.
///Creata per contenere tutti gli unit test physicalTrainTest
///</summary>
	[TestClass]
	public ref class physicalTrainTest
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
			///Test per Clone
			///</summary>
	public: [TestMethod]
			void CloneTest()
			{
				physicalTrain^  target = gcnew physicalTrain(1152,"127.0.0.1",3610); 
				
				physicalTrain^  actual = target->Clone();
				Assert::AreEqual(true, actual->Equals(target));
				Assert::AreNotSame(target,actual);
			}
			/// <summary>
			///Test per Update
			///</summary>
	public: [TestMethod]
			void UpdateTest()
			{
				physicalTrain^  target =  gcnew physicalTrain(1152,"127.0.0.1",3610); 
				target->setCDBLastPos(222);
				physicalTrain^  t =gcnew physicalTrain();
				Assert::IsFalse(t->Equals(target));
				t->setEngineNumber(1152);
				bool expected = true; 
				bool actual = t->Update(target);
				Assert::AreEqual(expected, actual);

				
				 expected = false; 
				 actual = t->Update(target);
				 Assert::AreEqual( t->ToString(), target->ToString());
				Assert::AreEqual(expected, actual);

			}
	};
}
namespace SchedulerATSTest {
    
}
