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
			void TestAreeCritiche()
			{
				AreeCritiche^ aree = gcnew AreeCritiche();
				System::IO::Stream^ readStreamschemaxsd = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("missioni.xml");
				System::IO::StreamReader^ reader = gcnew StreamReader(readStreamschemaxsd);
				String^ data = reader->ReadToEnd();

				aree->leggiConfigurazioneAreeCritiche(data);
				bool richiesta;
				richiesta = aree->richiestaCdb(1,0);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(6,0);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(7,0);
				Assert::AreEqual(richiesta, true);

				richiesta = aree->richiestaCdb(2,1);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(6,1);
				Assert::AreEqual(richiesta, true);
				richiesta = aree->richiestaCdb(7,1);
				Assert::AreEqual(richiesta, true);

				richiesta = aree->richiestaCdb(8,3);
				Assert::AreEqual(richiesta, false);
				

				

				delete reader;

			}

	};
}