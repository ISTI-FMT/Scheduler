﻿
#include "stdafx.h"
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
    using namespace System;
    ref class TrainTest;
    
    
    /// <summary>
///Classe di test per TrainTest.
///Creata per contenere tutti gli unit test TrainTest
///</summary>
	[TestClass]
	public ref class TrainTest
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
			///Test per Costruttore Train
			///</summary>
	public: [TestMethod]
			void TrainConstructorTest()
			{
				int p = 1; 
				int trn = 1151; 
				physicalTrain^  pt = gcnew physicalTrain(1152,"127.0.0.1",3610); 

				TabellaStazioni^  T = gcnew TabellaStazioni();
				TabellaOrario ^tabo = (gcnew TabellaOrario(T)); 
				int TRN = 1151; 
				List<Fermata^ >^  listit =  tabo->getFermateFor(TRN);

				
				double time = 0; 
				Train^  target = (gcnew Train(p, trn, pt, listit, time));
				Train^  target2 = (gcnew Train(p, trn, pt, listit));

				Assert::IsNotNull(target->ToString());

				target->goNextItinerario();
				target->getStatoTreno();
				Assert::IsNotNull(target->getStazioneItinerario());
				target->goNextItinerario();
				target->getStatoTreno();
				Assert::IsNotNull(target->getStazioneItinerario());
				Assert::IsNotNull(target->getTimeNextEvent());

			}
	};
}
namespace SchedulerATSTest {
    
}
