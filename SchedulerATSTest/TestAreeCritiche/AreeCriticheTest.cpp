#include "stdafx.h"

using namespace System::Collections::Generic;
using namespace System::IO;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace SchedulerATSTest 
{
	using namespace System;
	ref class AreeCriticheTest;

	[TestClass]
	public ref class AreeCriticheTest
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

	public: [TestMethod]
			void TestAreeCritiche1152_1151stop()
			{
				AreeCritiche^ aree = gcnew AreeCritiche();
				aree->leggiFileConfigurazioneAreeCritiche();

				bool richiesta;
				richiesta = aree->richiestaCdb(13302,1152);
				Assert::AreEqual(richiesta, true);

				richiesta = aree->richiestaCdb(12303,1151);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(503,1151);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(15302,1151);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(502,1151);
				Assert::AreEqual(richiesta, false);

			}
	public: [TestMethod]
			void TestAreeCritiche1152_1151incrocio()
			{
				AreeCritiche^ aree = gcnew AreeCritiche();
				aree->leggiFileConfigurazioneAreeCritiche();

				//1152=13302,501,14302,502,15301,503,12301,400,428,16302,440,448,17302
				bool richiesta;
				richiesta = aree->richiestaCdb(13302,1152);
				Assert::AreEqual(richiesta, true);

				richiesta = aree->richiestaCdb(12303,1151);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(503,1151);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(15302,1151);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(502,1151);
				Assert::AreEqual(richiesta, false);

				richiesta = aree->richiestaCdb(501,1152);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(14302,1152);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(502,1152);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(15301,1152);
				Assert::AreEqual(richiesta, true);

				richiesta = aree->richiestaCdb(502,1151);
				Assert::AreEqual(richiesta, true);

			}

	};
}