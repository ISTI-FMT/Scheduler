#include "TabellaOrario.h"
#using <System.Xml.dll>


#include "..\\logger\\Logger.h"
#include "..\\messaggi\\Mission.h"
using namespace System;
using namespace System::Globalization;
using namespace System::Xml;
using namespace System::Xml::Schema;
using namespace System::IO;

//Questa classe viene usata per leggere e gestire la tabella orario

#define TRACE
#define VALIDATEXML

TabellaOrario::TabellaOrario(void)
{
	tabella = gcnew Dictionary<int, List<Fermata^>^>;
	schemaxsd="TabellaOrario.xsd";
	leggiTabellaOrario();
	tabItinerari  = gcnew TabellaStazioni();
}

TabellaOrario::TabellaOrario(TabellaStazioni ^T)
{
	tabella = gcnew Dictionary<int, List<Fermata^>^>;
	schemaxsd="TabellaOrario.xsd";
	tabItinerari=T;
	leggiTabellaOrario();
}


/*
// funzione che converte una System::String in un std::string
string TabellaOrario::convertiString2string(System::String ^StringValue)
{
// converto da System::String a std::string
std::string stdString = String2string(StringValue);
return stdString;
}
*/
// funzione che restituisce un qualsiasi TRN nella tabella orario (di fatto il primo)
int TabellaOrario::getFirstTRN()
{
	if(tabella->Count > 0) {
		Dictionary<int, List<Fermata^> ^>::KeyCollection ^aux = tabella->Keys;
		for each (int x in aux)
		{
			return x;
		}
	}

	return 0;
}

// Display any validation errors.
/*sender*//*
		  void TabellaOrario::ValidationCallBack( Object^ , ValidationEventArgs^ e )
		  {
		  Console::WriteLine( L"Validation Error: {0}", e->Message );
		  }*/

// questa funzione legge il file di configurazione contenente la descrizione della tabella orario
void TabellaOrario::leggiTabellaOrario()
{
	try{
		// oggetti DateTime di supporto
		DateTime orarioSupporto1, orarioSupporto2, orarioSupporto3;
		double secs;
		TimeSpan sinceMidnight;

#ifdef VALIDATEXML
		System::IO::Stream^ readStreamschemaxsd = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream(schemaxsd);
		// Create the XmlSchemaSet class.
		XmlSchemaSet^ sc = gcnew XmlSchemaSet;

		// Add the schema to the collection.
		sc->Add( "urn:tabellaorario-schema",  gcnew XmlTextReader (readStreamschemaxsd) );
		XmlReaderSettings^ settings = gcnew XmlReaderSettings;
		settings->ValidationType = System::Xml::ValidationType::Schema;
		settings->Schemas = sc;
		/*ValidationEventHandler ^ed = gcnew ValidationEventHandler( ValidationCallBack );
		settings->ValidationEventHandler +=ed;*/
		System::IO::Stream^ readStreamXML = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("TabellaOrario.xml");
		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(readStreamXML, settings);
		String ^path = Directory::GetCurrentDirectory();
		String ^nomefile = "\\FileConfigurazione\\TabellaOrario.xml";
		
		if(File::Exists(path+nomefile)){
			reader = System::Xml::XmlReader::Create(path+nomefile, settings);
			Console::WriteLine("Caricato File Tabella Orario dal Disco");
		}

		//System::String^ nome = gcnew System::String(nomeFile.c_str());
		

		//	XmlDocument ^document = gcnew XmlDocument();
		//document->Load(readers);
		//document->Validate(ed);  
#endif // VALIDATEXML

		//System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(nomeFile);

		// per ogni treno presente nel file di configurazione della tabella orario...
		while (reader->ReadToFollowing("treno")){
			System::Xml::XmlReader ^inner = reader->ReadSubtree();
			// ...leggo l'id del treno
			System::String ^SystemStringIdTreno = reader->GetAttribute("id");
			// converto l'id del treno da System::String a int
			int idTreno = int::Parse(SystemStringIdTreno);
			// creo un nuovo treno
			List<Fermata^> ^treno = gcnew List<Fermata^>();

			// per ogni stazione in cui il treno in question deve fermarsi
			while (inner->ReadToFollowing("stazione")){
				// creo una nuova fermata
				Fermata ^stop = gcnew Fermata;
				// leggo l'id della stazione
				System::String ^SystemStringIdStazione = inner->GetAttribute("id");
				// configuro l'id della stazione
				stop->setIdStazione( int::Parse(SystemStringIdStazione));

				System::String ^SystemStringnameStazione = inner->GetAttribute("name");
				stop->setnameStazione(SystemStringnameStazione);

				System::Xml::XmlReader ^inner2 = inner->ReadSubtree();

				// leggo l'orario di arrivo
				inner2->ReadToFollowing("arrivo");
				System::String ^SystemStringOrarioArrivo = inner2->ReadString();
				// aggiungo alla data corrente l'ora, minuto e secondi letti
				orarioSupporto1 = DateTime::ParseExact(SystemStringOrarioArrivo, "HH:mm:ss", CultureInfo::InvariantCulture);
				//orarioSupporto2.Today.AddHours(orarioSupporto1.Hour);
				orarioSupporto3 = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);

				sinceMidnight = orarioSupporto1 - orarioSupporto3;
				// calcolo quanti secondi sono passati dalla mezzanotte
				secs = sinceMidnight.TotalSeconds;
				// configuro l'orario di arrivo della farmata in risoluzione di 30s
				stop->setOrarioArrivo(secs/30);

				// leggo l'orario di partenza
				inner2->ReadToFollowing("partenza");
				System::String ^SystemStringOrarioPartenza = inner2->ReadString();
				// aggiungo alla data corrente l'ora, minuto e secondi letti
				orarioSupporto2=DateTime::ParseExact(SystemStringOrarioPartenza, "HH:mm:ss", CultureInfo::InvariantCulture);
				//DateTime t = DateTime::ParseExact(SystemStringOrarioPartenza, "HH:mm:ss", CultureInfo::InvariantCulture);

				// calcolo la differenza fra la data preparata e la data "di oggi" (alla mezzanotte)
				sinceMidnight = orarioSupporto2- orarioSupporto3;
				// calcolo quanti secondi sono passati dalla mezzanotte
				secs = sinceMidnight.TotalSeconds;
				// configuro l'orario di arrivo della farmata in risoluzione di 30 s
				stop->setOrarioPartenza(secs/30);

				//TEMPO apertura porte
				inner2->ReadToFollowing("tempoaperturaporte");
				System::String ^SystemStringtemposperturaporte = inner2->ReadString();
				//stop->settempoMinimoAperturaPorte((stop->getOrarioPartenza()*30)- (stop->getOrarioArrivo()*30)-30);
				stop->settempoMinimoAperturaPorte( int::Parse(SystemStringtemposperturaporte));

				// leggo il binario programmato
				inner2->ReadToFollowing("binarioprogrammato");
				System::String ^SystemStringBinarioProgrammato = inner2->ReadString();
				// converto il binario programmato da System::String a int
				int binarioProgrammato =  int::Parse(SystemStringBinarioProgrammato);
				// configuro il binario programmato
				stop->setBinarioProgrammato(binarioProgrammato);

				// leggo il lato di apertura porte programmato
				inner2->ReadToFollowing("latoaperturaporteprogrammato");
				System::String ^SystemStringLatoProgrammato = inner2->ReadString();	
				// converto da System::String a std::string
				//string stringLatoAperturaPorte = convertiString2string(SystemStringLatoProgrammato);
				FermataType latoParturaPorte;
				if(SystemStringLatoProgrammato == "dx")
					latoParturaPorte = FermataType::aperturaTrenoDx;
				else if(SystemStringLatoProgrammato == "sx")
					latoParturaPorte = FermataType::aperturaTrenoSx;
				else if(SystemStringLatoProgrammato == "sd")
					latoParturaPorte = FermataType::aperturaTrenoDxSx;
				else
					latoParturaPorte = FermataType::noApertura;
				// configuro il lato apertura porte programmato programmato
				stop->setLatoAperturaPorte(latoParturaPorte);

				while (inner2->Read()) {
					switch (inner2->NodeType) {
					case System::Xml::XmlNodeType::Element:
						if(inner2->Name->Equals("itinerarioEntrata")){
							System::String ^idItEntrata = inner2->GetAttribute("id");
							inner2->Read();
							System::String ^nameEntrata = inner2->Value;

							stop->setIditinerarioEntrata( int::Parse(idItEntrata));
							stop->setnameitinerarioEntrata(nameEntrata);
						}
						if(inner2->Name->Equals("itinerarioUscita")){
							System::String ^idITUscita = inner2->GetAttribute("id");	
							inner2->Read();
							System::String ^nameUscita  = inner2->Value;
							stop->setIditinerarioUscita( int::Parse(idITUscita));
							stop->setnameitinerarioUscita(nameUscita);
						}
						break;
					}
				}


				// a questo punto posso aggiungere la fermata alla lista delle fermate del treno in questione
				treno->Add(stop);

				//System::Console::WriteLine(idTreno+idSTazione+orarioArrivo+orarioPartenza+binarioProgrammato+latoProgrammato);
				//System::Console::WriteLine();
			}
			// a questo punto aggiungo il treno alla tabella orario
			tabella->Add(idTreno, treno);
		}
		reader->Close();
	}catch(Exception ^e){

#ifdef TRACE
		Logger::Exception(e,"Tabella Orario");  
#endif // TRACE
		Console::WriteLine( L"Validation Error: {0}", e->Message );
	}	
}

// funzione che prende in ingresso un TRN ed un messaggio di tipo missionPlan, e riempie i campi del messaggio con i dati relativi
// alla missione associata al TRN in questione
void TabellaOrario::setMissionPlanMessage(int TRN, pacchettoMissionData ^pkt, List<ProfiloVelocita^>^pvel)
{
	// ottengo un riferimento alle fermate del treno TRN
	List<Fermata^> ^stops = tabella[TRN];
	createMissionPlanMsg(TRN,pkt,pvel,stops);
}

List<int>^ TabellaOrario::getCDBSignificativiFor(int trn)
{
	List<int>^ res = gcnew List<int>();
	List<Fermata^> ^listafermate = getFermateFor(trn);
	if(listafermate!=nullptr  & listafermate->Count>0 )
	{
		for each (Fermata^ fermata in listafermate)
		{
			int ie = fermata->getIditinerarioEntrata();
			int iu = fermata->getIditinerarioUscita();
			int prevfirstcdbu;
			if((iu>0)||(ie>0))
			{
				//Controllo prima gli itinerari di ingresso, poi quelli di uscita
				//visto che sono percorsi in questo ordine
				if (ie > 0)
				{
					prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(fermata->getIdStazione(),ie);

					//Inserisco il CDB precedente all'itinerario non � gi� presente
					if (res->Count == 0 || res[res->Count - 1] != prevfirstcdbu)
                    {
						res->Add(prevfirstcdbu);
                    }
					List<int>^ cdbs = tabItinerari->get_Cdb_Itinerario(fermata->getIdStazione(),ie);

					//Inserisco l'ultimo CDB dell'itinerario
					res->Add(cdbs[cdbs->Count -1]);
				}
				if (iu > 0)
				{
					prevfirstcdbu = tabItinerari->get_CdbPrecItinerario(fermata->getIdStazione(),iu);

					//Inserisco il CDB precedente all'itinerario non � gi� presente
					if (res->Count == 0 || res[res->Count - 1] != prevfirstcdbu)
                    {
						res->Add(prevfirstcdbu);
                    }
					List<int>^ cdbs = tabItinerari->get_Cdb_Itinerario(fermata->getIdStazione(),iu);

					//Inserisco l'ultimo CDB dell'itinerario
					res->Add(cdbs[cdbs->Count -1]);
				}
			}
			else //Caso in cui la stazione non ha itinerari ma solo fermate
			{
				int bin = fermata->getBinarioProgrammato();
				prevfirstcdbu = tabItinerari->get_CdbFermata(fermata->getIdStazione(),bin);
				res->Add(prevfirstcdbu);
			}
		}
	}
	return res;
}


void TabellaOrario::createMissionPlanMsg(int TRN, pacchettoMissionData ^pkt, List<ProfiloVelocita^>^pvel, List<Fermata^> ^stops){

	// se il teno esiste
	if(stops!=nullptr)
	{
		bool latolinea=false; //indica come si percorre la linea: se false da o per Monterosa/VicoloCorto true gli altri casi
		Fermata ^fakeVicoloCorto = gcnew Fermata(10000);
		Fermata ^fakeVialeMonterosa = gcnew Fermata(11000);
		if(!(stops->Contains(fakeVicoloCorto) | stops->Contains(fakeVialeMonterosa)  )){
			latolinea = true;
		}
		//indica la direzione in cui va il treno true dx da accademia -> vittoria, false viceversa
		bool direzione = tabItinerari->get_Direzione_itinerario(stops[0]->getIdStazione(),stops[0]->getIditinerarioUscita());
		if((stops[0]->getIditinerarioUscita()==0) &( stops->Count>2)){
			if(stops[2]->getIditinerarioUscita()>0){
				direzione = tabItinerari->get_Direzione_itinerario(stops[2]->getIdStazione(),stops[2]->getBinarioProgrammato());
			}
		}

		//Todo: V_mission D_mission tratte
		if(pvel!=nullptr){
			pkt->setPV(pvel);
			pkt->setN_ITER1(pvel->Count-1);
		}else{
			pkt->setPV(gcnew ProfiloVelocita(10700,70));
			pkt->setN_ITER1(0);
		}
		// -1 perch� la prima fermata non viene considerata negli N_ITER

		pkt->setN_ITER2((stops->Count) - 1);
		pkt->setQ_SCALE(QSCALEMissionData::M);
		int i=0;
		int prevprogkm = 0;
		for each (Fermata ^stop in stops)
		{

			Mission ^mission= gcnew Mission();
			mission->setQ_DOORS(stop->getLatoAperturaPorte());

			int orarioPartenza = (int)stop->getOrarioPartenza();

			mission->setT_START_TIME(orarioPartenza);
			mission->setT_DOORS_TIME( (int )stop->gettempoMinimoAperturaPorte());

			if(tabItinerari!=nullptr ){
				if(stop->getIditinerarioEntrata()!=0){
					lrbg ^infobalise = tabItinerari->get_infobalise(stop->getIdStazione(),stop->getIditinerarioEntrata());
					if(infobalise!=nullptr){

						mission->setNID_LRGB(infobalise->nid_lrgb);
						mission->setD_STOP(infobalise->d_stop);
						int pkmlrbg = 0;
						if(latolinea){
							pkmlrbg =	infobalise->get_progressivakm(13000);
						}else{
							pkmlrbg =	infobalise->get_progressivakm(10000);
						}
						int d_lrgb = Math::Abs(pkmlrbg - prevprogkm);
						if(direzione){
							prevprogkm = pkmlrbg +  infobalise->d_stop;
						}else{
							prevprogkm = pkmlrbg -  infobalise->d_stop;
						}
						mission->setD_LRGB(d_lrgb);
					}
				}
				if(i==0){
					lrbg ^infobalise = tabItinerari->get_infobalise(stop->getIdStazione(),stop->getIditinerarioUscita());
					if(infobalise!=nullptr){

						int nid_lrgb = infobalise->nid_lrgb;
						int dstop = infobalise->d_stop;
						mission->setD_STOP(dstop);
						mission->setNID_LRGB(nid_lrgb);
						//errore controlla dove t trovi leggi dal file di config
						int distPrimaBalise = 2;
						//parto da una stazione intermedia
						if(stop->getIdStazione()!=13000 ^ stop->getIdStazione()!=10000 ^ stop->getIdStazione()!=17000){
							distPrimaBalise=0;
							dstop+=15;
							//nid_lrgb=0;
							mission->setD_STOP(0);
							mission->setNID_LRGB(0);
						}
						
						
						mission->setD_LRGB(distPrimaBalise);
						
						int pkmlrbg = 0;
						if(latolinea){
							pkmlrbg = infobalise->get_progressivakm(13000) ;
						}else{
							pkmlrbg = infobalise->get_progressivakm(10000) ;
						}

						if(direzione){
							prevprogkm = pkmlrbg +  (dstop);
						}else{
							prevprogkm = pkmlrbg -  (dstop);
						}

					}
				}
				if((stop->getIditinerarioEntrata()==0) & (stop->getIditinerarioUscita()==0)){
					lrbg ^infobalise  = tabItinerari->get_infobalise_fromBinario(stop->getIdStazione(),stop->getBinarioProgrammato(),direzione);
					mission->setNID_LRGB(infobalise->nid_lrgb);
					mission->setD_STOP(infobalise->d_stop);
					int pkmlrbg = 0;
					if(latolinea){
						pkmlrbg =	infobalise->get_progressivakm(13000);
					}else{
						pkmlrbg =	infobalise->get_progressivakm(10000);
					}
					int d_lrgb = Math::Abs(pkmlrbg - prevprogkm);
					if(direzione){
						prevprogkm = pkmlrbg +  infobalise->d_stop;
					}else{
						prevprogkm = pkmlrbg -  infobalise->d_stop;
					}
					mission->setD_LRGB(d_lrgb);
				}

			}


			pkt->setMission(mission);
			i++;
		}
	}

}


System::String^ TabellaOrario::ToString(){
	String ^out;
	for each( KeyValuePair<int , List<Fermata^>^> kvp in tabella )
	{

		out+=" "+ kvp.Key+"\n\r";

		for each (Fermata ^dvar in kvp.Value)
		{
			out+= dvar->ToString();
		}
	}
	return out;
}

List<Fermata^> ^TabellaOrario::getFermateFor(int TRN){

	if(tabella->ContainsKey(TRN)){

		//return tabella[TRN];
		List<Fermata^> ^result = gcnew List<Fermata^>();
		for each (Fermata ^ferm in tabella[TRN])
		{
			if(ferm->getIdStazione()>0){
				result->Add(ferm);
			}
		}
		return result;
	}
	return nullptr;
}

List<Fermata^> ^TabellaOrario::getItinerariFor(int TRN){

	if(tabella->ContainsKey(TRN)){

		//return tabella[TRN];
		List<Fermata^> ^result = gcnew List<Fermata^>();
		for each (Fermata ^ferm in tabella[TRN])
		{
			if(ferm->getIdStazione()>1000){
				result->Add(ferm);
			}
		}
		return result;
	}
	return nullptr;
}


void TabellaOrario::ScriviTabellaOrario(System::IO::Stream ^stream){
	XmlWriterSettings ^settings = gcnew XmlWriterSettings();
	settings->Indent = true;
	XmlWriter ^writer = XmlWriter::Create(stream,settings);

	writer->WriteStartDocument();
	writer->WriteStartElement("orario");
	for each( KeyValuePair<int , List<Fermata^>^> kvp in tabella )
	{
		writer->WriteStartElement("treno");
		writer->WriteAttributeString("id",kvp.Key.ToString());



		for each (Fermata ^dvar in kvp.Value)
		{
			writer->WriteStartElement("stazione");
			writer->WriteAttributeString("id",dvar->getIdStazione().ToString());
			writer->WriteAttributeString("name",dvar->getnameStazione());

			writer->WriteElementString("arrivo", dvar->getOrarioArrivo().ToString());
			writer->WriteElementString("partenza", dvar->getOrarioPartenza().ToString());
			writer->WriteElementString("tempoaperturaporte", dvar->gettempoMinimoAperturaPorte().ToString());
			writer->WriteElementString("binarioprogrammato", dvar->getBinarioProgrammato().ToString());
			String ^latoParturaPorte ="";
			if(dvar->getLatoAperturaPorte() ==FermataType::aperturaTrenoDx )
				latoParturaPorte = "dx";
			else if(dvar->getLatoAperturaPorte() ==FermataType::aperturaTrenoSx)
				latoParturaPorte =  "sx";
			else if(dvar->getLatoAperturaPorte() ==FermataType::aperturaTrenoDxSx )
				latoParturaPorte ="sd" ;
			else
				latoParturaPorte = "";//FermataType::noApertura;

			

			writer->WriteElementString("latoaperturaporteprogrammato", latoParturaPorte);
			if(dvar->getIditinerarioEntrata()>0){
				writer->WriteStartElement("itinerarioEntrata");
				writer->WriteAttributeString("id", dvar->getIditinerarioEntrata().ToString());
				writer->WriteString(dvar->getnameitinerarioEntrata());
				writer->WriteEndElement();
			}
			if(dvar->getIditinerarioUscita()>0){
				writer->WriteStartElement("itinerarioUscita");
				writer->WriteAttributeString("id", dvar->getIditinerarioUscita().ToString());
				writer->WriteString(dvar->getnameitinerarioUscita());
				writer->WriteEndElement();
			}
			writer->WriteEndElement();

		}
		writer->WriteEndElement();
	}
	writer->WriteEndElement();
	writer->WriteEndDocument();
	writer->Close();
}