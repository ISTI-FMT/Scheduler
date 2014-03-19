
#include "stdafx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
#include "..//Prototipo//FermataType.h"
#include "stdafx.h"
namespace SchedulerATSTest {
    using namespace System;
    ref class FermataTest;
    
    
    /// <summary>
///Classe di test per FermataTest.
///Creata per contenere tutti gli unit test FermataTest
///</summary>
	[TestClass]
	public ref class FermataTest
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
				Fermata^  target = (gcnew Fermata(1)); 
			
				Fermata^  actual = target->Clone();
				Assert::AreEqual(target->ToString(),actual->ToString());
				Assert::IsTrue(target->Equals(actual));
				Assert::IsTrue(target->isPassante());
			}
			/// <summary>
			///Test per Costruttore Fermata
			///</summary>
	public: [TestMethod]
			void FermataConstructorTest()
			{
				int i = 0; 
				String^  n = System::String::Empty; 
				double oa = 0; 
				double op = 1;
				double tmpa = 0; 
				int bp = 0; 
				FermataType lap = FermataType::aperturaTrenoDx; 
				int idie = 0; 
				String^  nie = System::String::Empty; 
				int idiu = 0;
				String^  niu = System::String::Empty;
				Fermata^  target = (gcnew Fermata(i, n, oa, op, tmpa, bp, lap, idie, nie, idiu, niu));

				Assert::IsFalse(target->isPassante());
				Assert::IsTrue(target->ToString()->Length>20);	
			}
			/// <summary>
			///Test per setOrarioArrivo
			///</summary>
	public: [TestMethod]
			void setOrarioArrivoTest()
			{
				Fermata^  target = (gcnew Fermata()); 
				DateTime arr = DateTime::Now; // 
				target->setOrarioArrivo(arr);
			}
			/// <summary>
			///Test per setOrarioPartenza
			///</summary>
	public: [TestMethod]
			void setOrarioPartenzaTest()
			{
				Fermata^  target = (gcnew Fermata());
				DateTime orario =  DateTime::Now;
				target->setOrarioPartenza(orario);
			}
	};
}
namespace SchedulerATSTest {
    
}
