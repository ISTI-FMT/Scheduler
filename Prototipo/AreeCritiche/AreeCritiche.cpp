#include "AreeCritiche.h"

using namespace System::Xml;
using namespace System::Xml::Schema;

AreeCritiche::AreeCritiche()
{
	Init();
	leggiFileConfigurazioneAreeCritiche( System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream(XmlFilename));
}

AreeCritiche::AreeCritiche(String ^xmlAreecritiche)
{
	Init();
	XmlFilename = xmlAreecritiche;
	try{
		System::IO::FileStream ^SourceStream = System::IO::File::Open(xmlAreecritiche, System::IO::FileMode::Open);
		leggiFileConfigurazioneAreeCritiche(SourceStream);
		delete SourceStream;
	}catch(System::Exception ^e){
		Console::WriteLine("File non esiste");
	}
}

void AreeCritiche::Init()
{
	areeCritiche = gcnew List<AreaCritica^>();
	deadlockNoti = gcnew List<Deadlock^>();
	missioni = gcnew Dictionary<int,MissioneAnnotata^>();
	XmlFilename = gcnew String("AreeCritiche.xml");
	XsdFilename = gcnew String("AreeCritiche.xsd");
	cdbAree = gcnew Dictionary<int, List<AreaCritica^>^>();
	posizioniTreni = gcnew Dictionary<int,int>();
}

void AreeCritiche::leggiFileConfigurazioneAreeCritiche(System::IO::Stream^ readStreamXML)
{
	System::IO::Stream^ readStreamschemaxsd = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream(XsdFilename);
	// Create the XmlSchemaSet class.
	XmlSchemaSet^ sc = gcnew XmlSchemaSet;

	// Add the schema to the collection.
	sc->Add( "urn:AreeCritiche-schema",  gcnew XmlTextReader (readStreamschemaxsd) );
	XmlReaderSettings^ settings = gcnew XmlReaderSettings;
	settings->ValidationType = System::Xml::ValidationType::Schema;
	settings->Schemas = sc;
	settings->IgnoreWhitespace = true;
	settings->IgnoreComments = true;

	//System::String^ nome = gcnew System::String(nomeFile.c_str());
	System::Xml::XmlReader ^myReader = System::Xml::XmlReader::Create(readStreamXML, settings);

	MissioneAnnotata^ missioneCorrente = nullptr;
	SortedDictionary<int, int>^ limiti = gcnew SortedDictionary<int, int>();
	List<int>^ limitiAreeTmp = gcnew List<int>();
	while (myReader->Read())
	{
		if (myReader->NodeType != XmlNodeType::Element)
			continue;

		if (myReader->Name == "Area")
		{
			int id = Convert::ToInt32(myReader->GetAttribute("Id"));
			//NB:Nel caso di aree circolari, il limite deve essere coerente con i cdb dell'area
			int limite = Convert::ToInt32(myReader->GetAttribute("Limite"));
			limiti[id] = Convert::ToInt32(limite);

			List<int>^ listaCdb = gcnew List<int>();
			XmlReader^ cdbReader = myReader->ReadSubtree();
			while (cdbReader->Read())
			{
				if (cdbReader->NodeType == XmlNodeType::Element
					&& cdbReader->Name == "Cdb")
				{
					int cdbId = Convert::ToInt32(myReader->GetAttribute("Id"));
					listaCdb->Add(cdbId);
				}
			}

			AreaCritica^ area;
			if (limite == 0)
			{
				area = gcnew AreaCriticaLineare(listaCdb);
				limitiAreeTmp->Add(0);
			}
			else
			{
				area = gcnew AreaCriticaCircolare(listaCdb, limite);
				limitiAreeTmp->Add(limite);
			}
			area->nome = Convert::ToString(id);
			areeCritiche->Add(area);
		}
		else if (myReader->Name == "Missione")
		{
			missioneCorrente = gcnew MissioneAnnotata();
			int trn = Convert::ToInt32(myReader->GetAttribute("Trn"));
			missioneCorrente->Trn = trn;
			missioni[trn] = missioneCorrente;
		}
		else if (myReader->Name == "Cdb")
		{
			SortedDictionary<int, int>^ azioniCdbCorrente = gcnew SortedDictionary<int, int>();
			if (missioneCorrente != nullptr)
			{
				int cdbId = Convert::ToInt32(myReader->GetAttribute("Id"));
				missioneCorrente->ListaCdb->Add(cdbId);
			}

			XmlReader^ azioniReader = myReader->ReadSubtree();

			//leggo il contenuto di Cdb => una lista di elementi Azione
			while (!azioniReader->EOF)
			{
				if (azioniReader->NodeType == XmlNodeType::Element
					&& azioniReader->Name == "Azione")
				{
					String^ idAreaStr = azioniReader->GetAttribute("IdArea");
					//NOTA: Quando faccio read element content sto effettivamente muovendo il 
					//reader, quindi se faccio un secondo Read() mi salto un pezzo
					int azione = azioniReader->ReadElementContentAsInt();

					azioniCdbCorrente[Convert::ToInt32(idAreaStr)] = azione;
				}
				else
				{
					azioniReader->Read();
				}
			}

			if (missioneCorrente != nullptr)
			{
				SortedDictionary<int, int>::KeyCollection::Enumerator enumerator = limiti->Keys->GetEnumerator();
				//Creo, settate a zero (nessuna azione deve essere compiuta sulle aree corrispondenti), tutte le azioni che mancano
				while (enumerator.MoveNext())
				{
					int key = enumerator.Current;
					int value = limiti[key];

					if (!azioniCdbCorrente->ContainsKey(key))
					{
						azioniCdbCorrente[key] = 0;
					}
				}

				SortedDictionary<int, int>::ValueCollection^ values = azioniCdbCorrente->Values;
				array<int>^ valuesArray = gcnew array<int>(values->Count);
				values->CopyTo(valuesArray, 0);

				missioneCorrente->AzioniCdb->Add(valuesArray);
			}
		}
		if (myReader->Name == "Deadlock")
		{
			Deadlock^ dl = gcnew Deadlock();

			XmlReader^ posizioniReader = myReader->ReadSubtree();
			while (posizioniReader->Read())
			{
				if (posizioniReader->NodeType == XmlNodeType::Element
					&& posizioniReader->Name == "Posizione")
				{
					int trn = Convert::ToInt32(myReader->GetAttribute("TRN"));
					int cdb = Convert::ToInt32(myReader->GetAttribute("CDB"));

					dl->Posizioni->Add(trn, cdb);
				}
			}
			deadlockNoti->Add(dl);
		}
	}
	limitiAree = limitiAreeTmp->ToArray();
}

void AreeCritiche::MuoviTreno(int trn, int cdb)
{
	posizioniTreni[trn] = cdb;
}
void AreeCritiche::EliminaTreno(int trn)
{
	posizioniTreni->Remove(trn);
}

/*
Ritorna TRUE se un treno può entrare nel cdb, FALSE altrimenti.
Il treno può entrare nel cdb se tutte le aree critiche che lo contengono non hanno raggiunto il massimo numero di treni consentito
*/
bool AreeCritiche::richiestaCdb(int cdb, int trn)
{
	bool entrataValida = true;
	if (missioni->ContainsKey(trn))
	{
		MissioneAnnotata^ missione = missioni[trn];
		int idx = missione->ListaCdb->IndexOf(cdb);
		if (idx >= 0)
		{
			array<int>^ azioni = missione->AzioniCdb[idx];

			for (int i =0; i < areeCritiche->Count; i++)
			{
				AreaCritica^ area = areeCritiche[i];
				int azione = azioni[i];

				if (!area->entrataPermessa(trn, cdb, azione))
				{
					entrataValida = false;
					break;
				}
			}

			//Entro effettivamente nelle aree critiche solo se tutte hanno accettato l'ingresso
			if (entrataValida)
			{
				for (int i =0; i < areeCritiche->Count; i++)
				{
					AreaCritica^ area = areeCritiche[i];
					int azione = azioni[i];

					area->entrata(trn, cdb, azione);
				}
			}
		}
	}

	
	//Controllo ogni deadlock noto per determinare 
	//se le posizioni correnti dei treni corrispondono
	//ad un deadlock noto
	for each (Deadlock^ deadlock in this->deadlockNoti)
	{
		if (deadlock->Posizioni->Count == posizioniTreni->Count)
		{
			bool posizioniCorrispondono = true;
			for each (int key in deadlock->Posizioni->Keys)
			{
				//calcolo la posizione corrente del treno che può essere
				//una posizione nota oppure quella in cui il treno sta per andare
				int posizioneTreno = -1;
				if (posizioniTreni->ContainsKey(key))
				{
					posizioneTreno = posizioniTreni[key];
				}
				if (key == trn)
				{
					posizioneTreno = cdb;
				}

				//posizione del treno nel deadlock
				int posizioneDeadlock = deadlock->Posizioni[key];
				
				//Se il treno del deadlock non esiste, non posso essere in un deadlock
				if (posizioneTreno == -1)
				{
					posizioniCorrispondono = false;
					break;
				}
				if (posizioneTreno != deadlock->Posizioni[key])
				{
					posizioniCorrispondono = false;
					break;
				}
			}

			if (posizioniCorrispondono)
			{
				entrataValida = false;
				break;
			}
		}
	}

	return entrataValida;
}
