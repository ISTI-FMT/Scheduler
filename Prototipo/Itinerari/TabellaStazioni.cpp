#include "TabellaStazioni.h"
#using <System.Xml.dll>
#include "..\\logger\\Logger.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Xml;
using namespace System::Xml::Schema;


#define TRACE
#define VALIDATEXML

TabellaStazioni::TabellaStazioni(void)
{
	mapidstazioneitinerari= gcnew Dictionary<int,stazione^ >() ;
	leggifileconfigurazioneItinerari();
	leggifileconfigurazioneFermate();

}


// questa funzione legge il file di configurazione contenente la descrizione degli itinerari
void TabellaStazioni::leggifileconfigurazioneItinerari()
{

	try{

#ifdef VALIDATEXML
		System::IO::Stream^ readStreamschemaxsd = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("ConfigurazioneItinerari.xsd");

		// Create the XmlSchemaSet class.
		XmlSchemaSet^ sc = gcnew XmlSchemaSet;

		// Add the schema to the collection.
		sc->Add("urn:configurazioneitinerari-schema", gcnew XmlTextReader (readStreamschemaxsd) );
		XmlReaderSettings^ settings = gcnew XmlReaderSettings;
		settings->ValidationType = System::Xml::ValidationType::Schema;
		settings->Schemas = sc;

		System::IO::Stream^ readStreamXML = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("ConfigurazioneItinerari.xml");

		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(readStreamXML, settings);

		/*	XmlDocument ^document = gcnew XmlDocument();
		document->Load(readers);  */
#endif // VALIDATEXML

		//System::IO::Stream^ readStreamXML = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("ConfigurazioneItinerari.xml");
		//System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(readStreamXML);

		// per ogni stazione presente nel file di configurazione degli itinerari...
		
		while (reader->ReadToFollowing("stazione")){
			System::Xml::XmlReader ^inner = reader->ReadSubtree();
			// ...leggo l'id della stazione
			System::String ^StrIdstazione = reader->GetAttribute("id_offset");
			System::String ^nomestazione= reader->GetAttribute("name");
			// converto l'id della stazione da System::String a int
			int Idstazione = int::Parse(StrIdstazione);

			if(!mapidstazioneitinerari->ContainsKey(Idstazione)){

				stazione ^newstazione = gcnew stazione();
				newstazione->setNomeStazione(nomestazione);
				newstazione->set_SetIDStazione(Idstazione);
				mapidstazioneitinerari->Add(Idstazione,newstazione );
				inner->ReadToFollowing("itinerariIngresso");
				System::Xml::XmlReader ^inner2 = inner->ReadSubtree();

				while (inner2->ReadToFollowing("ingresso")){



					Itinerario ^newitinerario = gcnew Itinerario(typeItini::Entrata);

					int Iditinerario = int::Parse(inner2->GetAttribute("id"));
					newitinerario->setId(Iditinerario);



					newitinerario->ShortName =  inner2->GetAttribute("name");

					String^ direzione = inner2->GetAttribute("direzione");
					newitinerario->setDirezione(direzione);
					System::String ^porte = inner2->GetAttribute("portebanchina");
					if(porte->Equals("true")){
						newitinerario->setPorteBanchina(true);
					}else{
						newitinerario->setPorteBanchina(false);
					}

					//	int nidlrgb = int::Parse(inner2->GetAttribute("nid_lrgb"));
					//	newitinerario->setLrgb(nidlrgb);
					//	int dstop = int::Parse(inner2->GetAttribute("d_stop"));
					//	newitinerario->setDStop(dstop);
					newitinerario->setLatoBanchina( inner2->GetAttribute("latobanchina"));

					newitinerario->setNextCDB( int::Parse( inner2->GetAttribute("nextcdb")));

					int prevcdb = int::Parse(	inner2->GetAttribute("prevcdb"));
					newitinerario->setPrevCDB( prevcdb);	

					inner2->ReadToFollowing("ListCDB");

					System::Xml::XmlReader ^inner3 = inner2->ReadSubtree();
					

					while (inner3->ReadToFollowing("cdb")){



						int cdb = int::Parse( inner3->ReadString());
						newitinerario->getLCDB()->Add(cdb);

					}
					

					inner2->ReadToFollowing("lrgb");

					int nid_lrgb = int::Parse(inner2->GetAttribute("nid"));
					int d_stop = int::Parse(	inner2->GetAttribute("dstop"));

					lrbg ^infolrbg = gcnew lrbg(nid_lrgb,d_stop);
					
					inner3 = inner2->ReadSubtree();

					while (inner3->ReadToFollowing("pkm")){

						int rifkm = int::Parse(		inner3->GetAttribute("km"));
						int idpstation = int::Parse(	inner3->GetAttribute("idoffstaz"));

						infolrbg->add_progressivakm(rifkm,idpstation);


					}

					newitinerario->setLrgb(infolrbg);

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

					Itinerario ^newitinerario = gcnew Itinerario(typeItini::Uscita);
					int Iditinerario = int::Parse(inner2->GetAttribute("id"));
					newitinerario->setId(Iditinerario);



					newitinerario->ShortName = inner2->GetAttribute("name");

					String ^direzione = inner2->GetAttribute("direzione");
					newitinerario->setDirezione(direzione);
					System::String ^porte = inner2->GetAttribute("portebanchina");
					if(porte->Equals("true")){
						newitinerario->setPorteBanchina(true);
					}else{
						newitinerario->setPorteBanchina(false);
					}


					newitinerario->setLatoBanchina( inner2->GetAttribute("latobanchina"));

					newitinerario->setNextCDB(  int::Parse(inner2->GetAttribute("nextcdb")));

					int prevcdb = int::Parse(	inner2->GetAttribute("prevcdb"));
					newitinerario->setPrevCDB( prevcdb);	

					String ^nextstation = 	inner2->GetAttribute("nextstation");

					newitinerario->set_nextstation( int::Parse(nextstation));	

					inner2->ReadToFollowing("ListCDB");
					System::Xml::XmlReader ^inner3 = reader->ReadSubtree();
					while (inner3->ReadToFollowing("cdb")){



						int cdb = int::Parse( inner3->ReadString());
						newitinerario->getLCDB()->Add(cdb);

					}

					inner2->ReadToFollowing("lrgb");
					int nid_lrgb = int::Parse(inner2->GetAttribute("nid"));
					int d_stop = int::Parse(	inner2->GetAttribute("dstop"));

					lrbg ^infolrbg = gcnew lrbg(nid_lrgb,d_stop);

					inner3 = inner2->ReadSubtree();

					while (inner3->ReadToFollowing("pkm")){

						int rifkm = int::Parse(		inner3->GetAttribute("km"));
						int idpstation = int::Parse(	inner3->GetAttribute("idoffstaz"));

						infolrbg->add_progressivakm(rifkm,idpstation);


					}
					newitinerario->setLrgb(infolrbg);
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




			}

		}	
	}catch(System::Xml::Schema::XmlSchemaValidationException ^e){

#ifdef TRACE
		Logger::Exception(e,"Tabella Itinerari");  
#endif // TRACE
		Console::WriteLine( L"Validation Error: {0}", e->Message );
	}	
}



System::String^ TabellaStazioni::ToString() {
	String ^out="";
	for each( KeyValuePair<int  , stazione^> kvp in mapidstazioneitinerari )
	{

		out+=" "+ kvp.Key+"\n\r";

		out+=" "+kvp.Value->ToString()+"\n\r";


	}
	return out;
}

int TabellaStazioni::get_CdbPrecItinerario(int stazione, int iditin){
	int result=0;
	if(mapidstazioneitinerari->ContainsKey(stazione)){
		if(mapidstazioneitinerari[stazione]->getItinerariid()->ContainsKey(iditin)){
			return mapidstazioneitinerari[stazione]->getItinerariid()[iditin]->getPrevCDB();
		}

	}
	return result;
}

	int TabellaStazioni::get_CdbFermata(int stazione, int bin ){
		int result=0;
	if(mapidstazioneitinerari->ContainsKey(stazione)){
		
			for each (binario ^var in mapidstazioneitinerari[stazione]->getBinari())
			{
				if(var->getBin()==bin){
					return var->getCDB();
				}
			}
			
			
		

	}
	return result;

	}


int TabellaStazioni::get_CdbSuccItinerario(int stazione, int iditin){
	int result=0;
	if(mapidstazioneitinerari->ContainsKey(stazione)){
		if(mapidstazioneitinerari[stazione]->getItinerariid()->ContainsKey(iditin)){
			return mapidstazioneitinerari[stazione]->getItinerariid()[iditin]->getNextCDB();
		}

	}
	return result;
}

List<int> ^TabellaStazioni::get_Cdb_Itinerario(int stazione, int iditin){

	if(mapidstazioneitinerari->ContainsKey(stazione)){
		if(mapidstazioneitinerari[stazione]->getItinerariid()->ContainsKey(iditin)){
			return mapidstazioneitinerari[stazione]->getItinerariid()[iditin]->CloneListCDB();
		}

	}
	return nullptr;

}

void TabellaStazioni::leggifileconfigurazioneFermate()
{
	try{
#ifdef VALIDATEXML
		// Create the XmlSchemaSet class.
		System::IO::Stream^ readStreamschemaxsd = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("ConfigurazioneFermate.xsd");
		XmlSchemaSet^ sc = gcnew XmlSchemaSet;

		// Add the schema to the collection.
		sc->Add( "urn:conffermate-schema", gcnew XmlTextReader (readStreamschemaxsd) );
		XmlReaderSettings^ settings = gcnew XmlReaderSettings;
		settings->ValidationType = System::Xml::ValidationType::Schema;
		settings->Schemas = sc;	
		System::IO::Stream^ readStreamXML = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("ConfigurazioneFermate.xml");

		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(readStreamXML, settings);
#endif // VALIDATEXML

		// per ogni stazione presente nel file di configurazione degli itinerari...
		while (reader->ReadToFollowing("fermata"))
		{
			System::Xml::XmlReader ^inner = reader->ReadSubtree();
			// ...leggo l'id della stazione

			System::String ^StrIdstazione = reader->GetAttribute("id");
			System::String ^nomestazione= reader->GetAttribute("name");

			int Idstazione = int::Parse(StrIdstazione);

			if(!mapidstazioneitinerari->ContainsKey(Idstazione)){

				stazione ^newstazione = gcnew stazione();
				newstazione->setNomeStazione(nomestazione);
				newstazione->set_SetIDStazione(Idstazione);
				mapidstazioneitinerari->Add(Idstazione,newstazione );

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

					/*// ...leggo nid_lrgb del binario
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
					bin->setD_stop(d_stop);*/

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

					System::Xml::XmlReader ^inner2 = inner->ReadSubtree();

					inner->ReadToFollowing("cdb");
					System::String ^StrCDB = inner->ReadString();
					
					// converto CDB dellbinario da System::String a int
					//int CDB = int::Parse(StrCDB);
					bin->setCDB(int::Parse(StrCDB));
					

					inner2->ReadToFollowing("lrgb");
					int nid_lrgb = int::Parse(inner2->GetAttribute("nid"));
					int d_stop = int::Parse(	inner2->GetAttribute("dstop"));

					lrbg ^infolrbg = gcnew lrbg(nid_lrgb,d_stop);


					while (inner2->ReadToFollowing("pkm")){

						int rifkm = int::Parse(		inner2->GetAttribute("km"));
						int idpstation = int::Parse(	inner2->GetAttribute("idoffstaz"));

						infolrbg->add_progressivakm(rifkm,idpstation);


					}
					bin->set_info_lrgb(infolrbg);
					

					// inserisco il binario nella lista
					newstazione->addBinario(bin);
				}
			}

		}
	}catch(Exception ^e){

#ifdef TRACE
		Logger::Exception(e,"Tabella Fermate");  
#endif // TRACE
		Console::WriteLine( L"Validation Error: {0}", e->Message );
	}	
}



