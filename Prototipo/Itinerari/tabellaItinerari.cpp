#include "tabellaItinerari.h"
#using <System.Xml.dll>
#include "..\\String2string.h"
#include "..\\logger\\Logger.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Xml;
using namespace System::Xml::Schema;

#define TRACE
#define VALIDATEXML

tabellaItinerari::tabellaItinerari(void)
{
	mapidstazioneitinerari= gcnew Dictionary<int,stazione^ >() ;
	schemaxsd="..\\FileConfigurazione\\ConfigurazioneItinerari.xsd";
}


// questa funzione legge il file di configurazione contenente la descrizione degli itinerari
void tabellaItinerari::leggifileconfigurazioneItinerari(String ^nomeFile)
{

	try{

#ifdef VALIDATEXML
		// Create the XmlSchemaSet class.
		XmlSchemaSet^ sc = gcnew XmlSchemaSet;

		// Add the schema to the collection.
		sc->Add("urn:configurazioneitinerari-schema", schemaxsd );
		XmlReaderSettings^ settings = gcnew XmlReaderSettings;
		settings->ValidationType = System::Xml::ValidationType::Schema;
		settings->Schemas = sc;


		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(nomeFile, settings);

	/*	XmlDocument ^document = gcnew XmlDocument();
		document->Load(readers);  */
#endif // VALIDATEXML


		//System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(nomeFile);

		// per ogni stazione presente nel file di configurazione degli itinerari...
		while (reader->ReadToFollowing("stazione")){
			System::Xml::XmlReader ^inner = reader->ReadSubtree();
			// ...leggo l'id della stazione
			System::String ^StrIdstazione = reader->GetAttribute("id_offset");
			System::String ^nomestazione= reader->GetAttribute("name");
			// converto l'id della stazione da System::String a int
			int Idstazione = convertiString2int(StrIdstazione);

			if(!mapidstazioneitinerari->ContainsKey(Idstazione)){

				stazione ^newstazione = gcnew stazione();
				newstazione->setNomeStazione(nomestazione);
				newstazione->set_SetIDStazione(Idstazione);
				mapidstazioneitinerari->Add(Idstazione,newstazione );
				inner->ReadToFollowing("itinerariIngresso");
				System::Xml::XmlReader ^inner2 = inner->ReadSubtree();

				while (inner2->ReadToFollowing("ingresso")){



					Itinerario ^newitinerario = gcnew Itinerario();

					int Iditinerario = convertiString2int(inner2->GetAttribute("id"));
					newitinerario->setId(Iditinerario);



					newitinerario->setName( inner2->GetAttribute("name"));

					inner2->GetAttribute("direzione");

					System::String ^porte = inner2->GetAttribute("portebanchina");
					if(porte->Equals("true")){
						newitinerario->setPorteBanchina(true);
					}else{
						newitinerario->setPorteBanchina(false);
					}

					int nidlrgb = convertiString2int(inner2->GetAttribute("nid_lrgb"));
					newitinerario->setLrgb(nidlrgb);
					int dstop = convertiString2int(inner2->GetAttribute("d_stop"));
					newitinerario->setDStop(dstop);
					newitinerario->setLatoBanchina( inner2->GetAttribute("latobanchina"));

					newitinerario->setNextCDB( inner2->GetAttribute("nextcdb"));

					String ^prevcdb = 	inner2->GetAttribute("prevcdb");
					newitinerario->setPrevCDB( prevcdb);	

					System::Xml::XmlReader ^inner3 = inner2->ReadSubtree();
					while (inner3->ReadToFollowing("cdb")){



						int cdb = convertiString2int( inner3->ReadString());
						newitinerario->getLCDB()->Add(cdb);

					}


					newstazione->getItinerariid()->Add(Iditinerario,newitinerario);

					if(!newstazione->getItinerari()->ContainsKey(prevcdb)){
						List<Itinerario^>^listit = gcnew List<Itinerario^>();
						listit->Add(newitinerario);
						newstazione->getItinerari()->Add(prevcdb,listit);
					}else{
						List<Itinerario^>^listit = newstazione->getItinerari()[prevcdb];
						listit->Add(newitinerario);

					}

				}

				inner->ReadToFollowing("itinerariUscita");
				//if(sdsa)
				inner2 = inner->ReadSubtree();
				while (inner2->ReadToFollowing("partenza")){

					Itinerario ^newitinerario = gcnew Itinerario();
					int Iditinerario = convertiString2int(inner2->GetAttribute("id"));
					newitinerario->setId(Iditinerario);



					newitinerario->setName( inner2->GetAttribute("name"));

					inner2->GetAttribute("direzione");

					System::String ^porte = inner2->GetAttribute("portebanchina");
					if(porte->Equals("true")){
						newitinerario->setPorteBanchina(true);
					}else{
						newitinerario->setPorteBanchina(false);
					}


					newitinerario->setLatoBanchina( inner2->GetAttribute("latobanchina"));

					newitinerario->setNextCDB( inner2->GetAttribute("nextcdb"));

					String ^prevcdb = 	inner2->GetAttribute("prevcdb");
					newitinerario->setPrevCDB( prevcdb);	

					String ^nextstation = 	inner2->GetAttribute("nextstation");

					newitinerario->set_nextstation( convertiString2int(nextstation));	


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

				}




			}

		}	
	}catch(System::Xml::Schema::XmlSchemaValidationException ^e){

#ifdef TRACE
		Logger::Exception(e,"Tabella Itinerari");  
#endif // TRACE
		Console::WriteLine( L"Validation Error: {0}", e->Message );
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


