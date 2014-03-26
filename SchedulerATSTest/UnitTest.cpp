#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace SchedulerATSTest
{
	[TestClass]
	public ref class UnitTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Ottiene o imposta il contesto del test che fornisce
		///le informazioni e le funzionalità per l'esecuzione del test corrente.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		//È possibile utilizzare i seguenti attributi aggiuntivi per la scrittura dei test:
		//
		//Utilizzare ClassInitialize per eseguire il codice prima di eseguire il primo test della classe
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//Utilizzare ClassCleanup per eseguire il codice dopo l'esecuzione di tutti i test della classe
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Utilizzare TestInitialize per eseguire il codice prima di eseguire ciascun test
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//Utilizzare TestCleanup per eseguire il codice dopo l'esecuzione di ciascun test
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestMethod]
		void TestMethod1()
		{
			//
			// TODO: aggiungere qui la logica del test
			//
		};
	};
}
