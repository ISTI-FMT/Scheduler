
#include "stdafx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace System::Collections::Generic;
namespace SchedulerATSTest {
    using namespace System;
    ref class ConfigurazioneVelocitaTest;
    
    
    /// <summary>
///Classe di test per ConfigurazioneVelocitaTest.
///Creata per contenere tutti gli unit test ConfigurazioneVelocitaTest
///</summary>
	[TestClass]
	public ref class ConfigurazioneVelocitaTest
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
			///Test per Costruttore ConfigurazioneVelocita
			///</summary>
	public: [TestMethod]
			void ConfigurazioneVelocitaConstructorTest()
			{
				ConfigurazioneVelocita^  target = (gcnew ConfigurazioneVelocita());
				Assert::IsTrue(target->ToString()->Length>20);	
				ProfiloVelocita ^t = gcnew ProfiloVelocita();
				List<ProfiloVelocita^>^ resultnull =target->getProfiloVelocita(55);
				List<ProfiloVelocita^>^ result = target->getProfiloVelocita(1152);
				Assert::IsNull(resultnull);
				CollectionAssert::AllItemsAreNotNull(result);
			}

	};
}
namespace SchedulerATSTest {
    
}
