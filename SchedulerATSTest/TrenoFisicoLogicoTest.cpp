﻿
#include "stdafx.h"
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
    using namespace System;
    ref class TrenoFisicoLogicoTest;
    
    
    /// <summary>
///Classe di test per TrenoFisicoLogicoTest.
///Creata per contenere tutti gli unit test TrenoFisicoLogicoTest
///</summary>
	[TestClass]
	public ref class TrenoFisicoLogicoTest
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
			///Test per Costruttore TrenoFisicoLogico
			///</summary>
	public: [TestMethod]
			void TrenoFisicoLogicoConstructorTest()
			{
				int idtrenoF = 36100; 
				List<int >^  idltrenoL = gcnew List<int >();
				int cdblpos = 13301; 
				TrenoFisicoLogico^  target = (gcnew TrenoFisicoLogico(idtrenoF, idltrenoL, cdblpos));
				TrenoFisicoLogico^  target3 = (gcnew TrenoFisicoLogico(idtrenoF, 1156, cdblpos));
				TrenoFisicoLogico^  target2 = (gcnew TrenoFisicoLogico());
				Assert::IsNotNull(target);
				Assert::IsNotNull(target2);
				Assert::IsNotNull(target3);
				Assert::AreEqual(-1,target2->getIdTrenoLogico(1));
				target2->setIdTrenoLogico(1156);
				Assert::AreEqual(1156,target2->getIdTrenoLogico(0));
			}
	};
}
namespace SchedulerATSTest {
    
}
