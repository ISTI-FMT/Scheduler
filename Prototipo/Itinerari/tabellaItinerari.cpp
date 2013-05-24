#include "tabellaItinerari.h"
#using <System.Xml.dll>
#include "..\\String2string.h"

using namespace System;
using namespace System::Globalization;


tabellaItinerari::tabellaItinerari(void)
{
	mapidstazioneitinerari= gcnew Dictionary<int,stazione^ >() ;
}


// questa funzione legge il file di configurazione contenente la descrizione della tabella orario
void tabellaItinerari::leggifileconfigurazioneItinerari(String ^nomeFile)
{
	// oggetti DateTime di supporto


	System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(nomeFile);
	// per ogni treno presente nel file di configurazione della tabella orario...
	while (reader->ReadToFollowing("stazione")){
		System::Xml::XmlReader ^inner = reader->ReadSubtree();
		// ...leggo l'id della stazione
		System::String ^StrIdstazione = reader->GetAttribute("id_offset");
		System::String ^nomestazione= reader->GetAttribute("name");
		// converto l'id della stazione da System::String a int
		int Idstazione = convertiString2int(StrIdstazione);

		if(!mapidstazioneitinerari->ContainsKey(Idstazione)){

			stazione ^newstazione = gcnew stazione();
			mapidstazioneitinerari->Add(Idstazione,newstazione );
			inner->ReadToFollowing("itinerari");
			System::Xml::XmlReader ^inner2 = inner->ReadSubtree();
			System::Xml::XmlReader ^inner4 = inner->ReadSubtree();
			bool k = inner4->ReadToFollowing("ingresso");
			//bool kh = 	inner4->ReadToNextSibling("ingresso");
			//bool kh1 = 	inner4->ReadToNextSibling("ingresso");

			//bool kk = reader->ReadToFollowing("partenza");
			do{



				Itinerario ^newitinerario = gcnew Itinerario();

				int Iditinerario = convertiString2int(inner->GetAttribute("id"));
				newitinerario->setId(Iditinerario);



				newitinerario->setName( inner->GetAttribute("name"));

				inner->GetAttribute("direzione");

				System::String ^porte = inner->GetAttribute("portebanchina");
				if(porte->Equals("true")){
					newitinerario->setPorteBanchina(true);
				}else{
					newitinerario->setPorteBanchina(false);
				}

				int nidlrgb = convertiString2int(inner->GetAttribute("nid_lrgb"));
				newitinerario->setLrgb(nidlrgb);
				int dstop = convertiString2int(inner->GetAttribute("d_stop"));
				newitinerario->setDStop(dstop);
				newitinerario->setLatoBanchina( inner->GetAttribute("latobanchina"));

				newitinerario->setNextCDB( inner->GetAttribute("nextcdb"));

				String ^prevcdb = 	inner->GetAttribute("prevcdb");
				newitinerario->setPrevCDB( prevcdb);	

				System::Xml::XmlReader ^inner3 = inner->ReadSubtree();
				while (inner3->ReadToFollowing("cdb")){



					int cdb = convertiString2int( inner3->ReadString());
					newitinerario->getLCDB()->Add(cdb);

				}




				if(!newstazione->getItinerari()->ContainsKey(prevcdb)){
					List<Itinerario^>^listit = gcnew List<Itinerario^>();
					listit->Add(newitinerario);
					newstazione->getItinerari()->Add(prevcdb,listit);
				}else{
					List<Itinerario^>^listit = newstazione->getItinerari()[prevcdb];
					listit->Add(newitinerario);

				}

			}while (inner->ReadToNextSibling("ingresso"));

			reader->ReadToFollowing("partenza");
			do{

				Itinerario ^newitinerario = gcnew Itinerario();
				int Iditinerario = convertiString2int(reader->GetAttribute("id"));
				newitinerario->setId(Iditinerario);



				newitinerario->setName( reader->GetAttribute("name"));

				reader->GetAttribute("direzione");

				System::String ^porte = reader->GetAttribute("portebanchina");
				if(porte->Equals("true")){
					newitinerario->setPorteBanchina(true);
				}else{
					newitinerario->setPorteBanchina(false);
				}


				newitinerario->setLatoBanchina( reader->GetAttribute("latobanchina"));

				newitinerario->setNextCDB( reader->GetAttribute("nextcdb"));

				String ^prevcdb = 	reader->GetAttribute("prevcdb");
				newitinerario->setPrevCDB( prevcdb);	


				System::Xml::XmlReader ^inner3 = reader->ReadSubtree();
				while (inner3->ReadToFollowing("cdb")){



					int cdb = convertiString2int( inner3->ReadString());
					newitinerario->getLCDB()->Add(cdb);

				}



				if(!newstazione->getItinerari()->ContainsKey(prevcdb)){
					List<Itinerario^>^listit = gcnew List<Itinerario^>();
					listit->Add(newitinerario);
					newstazione->getItinerari()->Add(prevcdb,listit);
				}else{
					List<Itinerario^>^listit = newstazione->getItinerari()[prevcdb];
					listit->Add(newitinerario);

				}

			}while (reader->ReadToNextSibling("partenza"));




		}
		// a questo punto aggiungo il treno alla tabella orario
		//tabella->Add(idTreno, treno);
	}	
}


int tabellaItinerari::convertiString2int(System::String ^StringValue)
{
	// converto da System::String a std::string
	std::string stdString = String2string(StringValue);
	// converto da std::string a int
	int intValue = atoi(stdString.c_str());
	return intValue;
}

System::String^ tabellaItinerari::ToString() {
	String ^out="";
	for each( KeyValuePair<int  , stazione^> kvp in mapidstazioneitinerari )
	{

		out+=" "+ kvp.Key+"\n\r";

		out+=" "+kvp.Value->ToString()+"\n\r";


	}
	return out;
}


