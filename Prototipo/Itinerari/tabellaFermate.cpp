#include "tabellaFermate.h"
#using <System.Xml.dll>
#include "..\\String2string.h"
#include "..\\logger\\Logger.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Xml;
using namespace System::Xml::Schema;

tabellaFermate::tabellaFermate(void)
{
	tabella = gcnew Dictionary<int, List<binario^> ^>;
}

int tabellaFermate::convertiString2int(System::String ^StringValue)
{
	// converto da System::String a std::string
	std::string stdString = String2string(StringValue);
	// converto da std::string a int
	int intValue = atoi(stdString.c_str());
	return intValue;
}

System::String^ tabellaFermate::ToString() {
	String ^out="";
	for each( KeyValuePair<int  , List<binario^>^> kvp in tabella )
	{
		out+=" Id stazione " + kvp.Key+"\n\r";

		for each(binario ^bin in kvp.Value)
		{
			out+=" "+bin->ToString()+"\n\r";
		}
	}
	return out;
}

void tabellaFermate::leggifileconfigurazioneFermate(String ^nomeFile)
{
	XmlReaderSettings^ settings = gcnew XmlReaderSettings;
	System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(nomeFile, settings);

	// per ogni stazione presente nel file di configurazione degli itinerari...
	while (reader->ReadToFollowing("fermata"))
	{
		System::Xml::XmlReader ^inner = reader->ReadSubtree();
		// ...leggo l'id della stazione
		System::String ^StrIdFermata = reader->GetAttribute("id");
		// converto l'id della stazione da System::String a int
		int idFermata = convertiString2int(StrIdFermata);

		Console::Write(StrIdFermata);

		// creo la lista vuota che poi inserirò nella tabella
		List<binario^> ^listaBinari = gcnew List<binario^>;

		while (inner->ReadToFollowing("binario"))
		{
			// creo il binario che devo inserire
			binario ^bin = gcnew binario;

			//System::Xml::XmlReader ^inner = reader->ReadSubtree();

			// ...leggo id del binario
			System::String ^StrIdBinario = inner->GetAttribute("id");
			// setto id del binario
			bin->setId(StrIdBinario);

			// ...leggo direzione del binario
			System::String ^direzione = inner->GetAttribute("direzione");
			// setto direzione del binario
			bin->setDirezione(direzione);

			// ...leggo nid_lrgb del binario
			System::String ^Strnid_lrgb = inner->GetAttribute("nid_lrgb");
			// converto nid_lrgb dellbinario da System::String a int
			int nid_lrgb = convertiString2int(Strnid_lrgb);
			// setto nid_lrgb del binario
			bin->setNid_lrgb(nid_lrgb);

			// ...leggo d_stop del binario
			System::String ^Strd_stop = inner->GetAttribute("d_stop");
			// converto d_stop dellbinario da System::String a int
			int d_stop = convertiString2int(Strd_stop);
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
			bin->setLatoBanchina(latobanchina);

			// ...leggo nextCDB del binario
			System::String ^StrnextCDB = inner->GetAttribute("nextCDB");
			// converto nextCDB dellbinario da System::String a int
			int nextCDB = convertiString2int(StrnextCDB);
			// setto nextCDB del binario
			bin->setNextCDB(nextCDB);

			// ...leggo prevCDB del binario
			System::String ^StrprevCDB = inner->GetAttribute("prevCDB");
			// converto prevCDB dellbinario da System::String a int
			int prevCDB = convertiString2int(StrprevCDB);
			// setto prevCDB del binario
			bin->setPrevCDB(prevCDB);

			reader->ReadToFollowing("cdb");
			System::String ^StrCDB = inner->ReadString();
			// converto CDB dellbinario da System::String a int
			int CDB = convertiString2int(StrCDB);
			bin->setCDB(CDB);

			// inserisco il binario nella lista
			listaBinari->Add(bin);
		}
		// inserisco la coppia idFermata e listaBinari nella tabella delle fermate
		addFermata(idFermata, listaBinari);
	}
}

