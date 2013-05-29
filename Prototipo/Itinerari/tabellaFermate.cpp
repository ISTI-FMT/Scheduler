#include "tabellaFermate.h"
#using <System.Xml.dll>

#include "..\\logger\\Logger.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Xml;
using namespace System::Xml::Schema;

#define TRACE


tabellaFermate::tabellaFermate(void)
{
	tabella = gcnew Dictionary<String ^, List<binario^> ^>;
	schemaxsd  ="..\\FileConfigurazione\\ConfigurazioneFermate.xsd";
}



System::String^ tabellaFermate::ToString() {
	String ^out="";
	for each( KeyValuePair<String^  , List<binario^>^> kvp in tabella )
	{
		out+=" Nome Fermata " + kvp.Key+"\n\r";

		for each(binario ^bin in kvp.Value)
		{
			out+=" "+bin->ToString()+"\n\r";
		}
	}
	return out;
}

void tabellaFermate::leggifileconfigurazioneFermate(String ^nomeFile)
{
	try{
		// Create the XmlSchemaSet class.
		XmlSchemaSet^ sc = gcnew XmlSchemaSet;

		// Add the schema to the collection.
		sc->Add( "urn:conffermate-schema", schemaxsd );
		XmlReaderSettings^ settings = gcnew XmlReaderSettings;
		settings->ValidationType = System::Xml::ValidationType::Schema;
		settings->Schemas = sc;
		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(nomeFile, settings);

		// per ogni stazione presente nel file di configurazione degli itinerari...
		while (reader->ReadToFollowing("fermata"))
		{
			System::Xml::XmlReader ^inner = reader->ReadSubtree();
			// ...leggo l'id della stazione
			System::String ^StrIdFermata = reader->GetAttribute("id");


			// creo la lista vuota che poi inserirò nella tabella
			List<binario^> ^listaBinari = gcnew List<binario^>;
			// inserisco la coppia idFermata e listaBinari nella tabella delle fermate
			addFermata(StrIdFermata, listaBinari);

			while (inner->ReadToFollowing("binario"))
			{
				// creo il binario che devo inserire
				binario ^bin = gcnew binario;

				//System::Xml::XmlReader ^inner = reader->ReadSubtree();

				// ...leggo name del binario
				System::String ^StrnameBinario = inner->GetAttribute("namebin");
				// setto name del binario
				bin->setNameBin(StrnameBinario);

				// ...leggo il bin del binario
				System::String ^StrBinario = inner->GetAttribute("bin");
				// setto il bin del binario
				bin->setBin(int::Parse(StrBinario));

				// ...leggo direzione del binario
				System::String ^direzione = inner->GetAttribute("direzione");
				// setto direzione del binario
				bin->setDirezione(direzione);

				// ...leggo nid_lrgb del binario
				System::String ^Strnid_lrgb = inner->GetAttribute("nid_lrgb");
				// converto nid_lrgb dellbinario da System::String a int
				int nid_lrgb = int::Parse(Strnid_lrgb);
				// setto nid_lrgb del binario
				bin->setNid_lrgb(nid_lrgb);

				// ...leggo d_stop del binario
				System::String ^Strd_stop = inner->GetAttribute("d_stop");
				// converto d_stop dellbinario da System::String a int
				int d_stop = int::Parse(Strd_stop);
				// setto d_stop del binario
				bin->setD_stop(d_stop);

				// ...leggo portebanchina del binario
				System::String ^Strportebanchina = inner->GetAttribute("portebanchina");
				// converto in bool
				bool porte = (Strportebanchina == "true")?true:false;
				// setto d_stop del binario
				bin->setPorteBanchina(porte);

				// ...leggo latobanchina del binario
				System::String ^latobanchina = inner->GetAttribute("latobanchina");
				// setto latobanchina del binario

				int strlatobanchina;
				if(latobanchina == "dx")
					strlatobanchina = 1;
				else if(latobanchina == "sx")
					strlatobanchina = 2;
				else if(latobanchina == "sd")
					strlatobanchina = 3;
				else
					strlatobanchina = 0;
				bin->setLatoBanchina(strlatobanchina);

				// ...leggo nextCDB del binario
				System::String ^StrnextCDB = inner->GetAttribute("nextCDB");
				// converto nextCDB dellbinario da System::String a int
				int nextCDB = int::Parse(StrnextCDB);
				// setto nextCDB del binario
				bin->setNextCDB(nextCDB);

				// ...leggo prevCDB del binario
				System::String ^StrprevCDB = inner->GetAttribute("prevCDB");
				// converto prevCDB dellbinario da System::String a int
				int prevCDB = int::Parse(StrprevCDB);
				// setto prevCDB del binario
				bin->setPrevCDB(prevCDB);

				reader->ReadToFollowing("cdb");
				System::String ^StrCDB = inner->ReadString();
				// converto CDB dellbinario da System::String a int
				//int CDB = int::Parse(StrCDB);
				bin->setCDB(StrCDB);

				// inserisco il binario nella lista
				listaBinari->Add(bin);
			}

		}
	}catch(Exception ^e){

#ifdef TRACE
		Logger::Exception(e,"Tabella Fermate");  
#endif // TRACE
		Console::WriteLine( L"Validation Error: {0}", e->Message );
	}	
}

