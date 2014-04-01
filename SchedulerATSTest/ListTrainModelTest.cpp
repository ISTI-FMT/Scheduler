
#include "stdafx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace System::Collections::Generic;
namespace SchedulerATSTest {
	using namespace System;
	ref class ListTrainModelTest;


	/// <summary>
	///Classe di test per ListTrainModelTest.
	///Creata per contenere tutti gli unit test ListTrainModelTest
	///</summary>
	[TestClass]
	public ref class ListTrainModelTest
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
			///Test per Costruttore ListTrainModel
			///</summary>
	public: [TestMethod]
			void ListTrainModelConstructorTest()
			{
				ListTrainModel^  target = (gcnew ListTrainModel());
				TabellaStazioni^  T = gcnew TabellaStazioni();
				/*EventQueue<List<Fermata^>^> ^EQueueCambioOrario =gcnew EventQueue<List<Fermata^>^> ();
				Prototipo::ListTrainView^	view = gcnew Prototipo::ListTrainView(T,EQueueCambioOrario);
				target->Subscribe(view);
				view->AddModel(target);*/
				int p = 1; 
				int trn = 1151; 
				physicalTrain^  pt = gcnew physicalTrain(65316,"127.0.0.1",3610); 


				TabellaOrario ^tabo = (gcnew TabellaOrario(T)); 

				List<Fermata^ >^  listit =  tabo->getFermateFor(trn);


				double time = 0; 
				Train^  train1 = (gcnew Train(p, trn, pt, listit, time));
				int TRN = 1152; 
				List<Fermata^ >^  listit2 =  tabo->getFermateFor(TRN);


				Train^ train2 = (gcnew Train(2, TRN, pt, listit2));
				physicalTrain^  pt1 = gcnew physicalTrain(65315,"127.0.0.1",3610); 
				Train^ train3 = (gcnew Train(2, 1153, pt1, listit2));

				target->Add(train1);
				target->Add(train2);
				target->NextIt(train2);
				target->changePrior(train1,2);
				target->changeState(train1,StateTrain::USCITASTAZIONE);
				Assert::IsNotNull(target->getTrain("65316"));
				Assert::IsNull(target->getTrain("65315"));
				Assert::AreEqual(true,target->Contains(train1));
				Assert::AreEqual(false,target->Contains(train3));

				Assert::AreEqual(false,target->RemoveElement(train3));
				target->changeOrari(train2,tabo->getFermateFor(trn));
				Assert::AreEqual(true,target->RemoveElement(train1));

				CollectionAssert::AllItemsAreNotNull(target->getList());




			}
	};
}
namespace SchedulerATSTest {

}
