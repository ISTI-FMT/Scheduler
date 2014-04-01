
#include "stdafx.h"
#include "stdafx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace SchedulerATSTest {
    using namespace System;
    ref class LoggerTest;
    
    
    /// <summary>
///Classe di test per LoggerTest.
///Creata per contenere tutti gli unit test LoggerTest
///</summary>
	[TestClass]
	public ref class LoggerTest
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
			///Test per Info
			///</summary>
	public: [TestMethod]
			void InfoTest()
			{
				String^  message = System::String::Empty; 
				String^  module = System::String::Empty; 
				Logger::Info(message, module);
			}
			/// <summary>
			///Test per Warning
			///</summary>
	public: [TestMethod]
			void WarningTest()
			{
				String^  message = System::String::Empty; 
				String^  module = System::String::Empty; 
				Logger::Warning(message, module);
			}
			/// <summary>
			///Test per Error
			///</summary>
	public: [TestMethod]
			void ErrorTest()
			{
				String^  message = System::String::Empty; 
				String^  module = System::String::Empty; 
				Logger::Error(message, module);
			}
			/// <summary>
			///Test per Info
			///</summary>
	public: [TestMethod]
			void InfoTest1()
			{
				int NID_MSG = 0; 
				String^  io = System::String::Empty; 
				String^  desc = System::String::Empty; 
				int dim = 0; 
				String^  message = System::String::Empty; 
				String^  module = System::String::Empty; 
				Logger::Info(NID_MSG, io, desc, dim, message, module);
			}
			/// <summary>
			///Test per Costruttore Logger
			///</summary>
	public: [TestMethod]
			void LoggerConstructorTest()
			{
				Logger^  target = (gcnew Logger());
				Assert::IsNotNull(target);
			}
	};
}
namespace SchedulerATSTest {
    
}
