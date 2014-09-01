#include "AreeCritiche.h"

using namespace System::Xml;
using namespace System::Xml::Schema;

AreeCritiche::AreeCritiche()
{
	areeCritiche = gcnew List<AreaCritica^>();
	limitiAree = gcnew array<int>(0);

	missioni = gcnew Dictionary<int,MissioneAnnotata^>();
	XmlFilename = gcnew String("AreeCritiche.xml");
	XsdFilename = gcnew String("AreeCritiche.xsd");

	//leggiFileConfigurazioneAreeCritiche( System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream(XmlFilename));
}

AreeCritiche::AreeCritiche(String ^xmlAreecritiche)
{
	areeCritiche = gcnew List<AreaCritica^>();
	limitiAree = gcnew array<int>(0);

	missioni = gcnew Dictionary<int,MissioneAnnotata^>();
	XmlFilename = xmlAreecritiche;
	XsdFilename = gcnew String("AreeCritiche.xsd");

	/*try{
	System::IO::FileStream ^SourceStream = System::IO::File::Open(xmlAreecritiche, System::IO::FileMode::Open);
	leggiFileConfigurazioneAreeCritiche(SourceStream);
	delete SourceStream;
	}catch(System::Exception ^e){
	Console::WriteLine("File non esiste");
	}*/
}

List<GestioneAreeCritiche::MissioneTreno^>^ AreeCritiche::get_missioniTreno()
{
	List<GestioneAreeCritiche::MissioneTreno^>^ res = gcnew List<GestioneAreeCritiche::MissioneTreno^>();
	for each(MissioneAnnotata^ missione in missioni->Values)
	{
		int trn = missione->Trn;
		List<int>^ listaCdb = missione->ListaCdb;

		GestioneAreeCritiche::MissioneTreno^ mt = gcnew GestioneAreeCritiche::MissioneTreno(Convert::ToString(trn), listaCdb);
		res->Add(mt);
	}
	return res;
}

int AreeCritiche::get_Direzione(List<int>^ area, List<int>^ missione, int cdbPosizione)
{
	//il CDB non fa parte dell'area o della missione. 
	//nessuna azione da fare
	if (!area->Contains(cdbPosizione) || !missione->Contains(cdbPosizione))
	{
		return NessunaAzione;
	}

	int idxMissione = missione->IndexOf(cdbPosizione);
	int idxArea = area->IndexOf(cdbPosizione);

	//il treno è alla fine dell'area
	//devo calcolare in che direzione sta andando
	if (idxArea == area->Count - 1)
	{
		//il treno è alla fine della missione
		if (idxMissione == missione->Count -1)
		{
			return EntraSinistra;
		}
		//il treno è all'inizio della missione
		else if (idxMissione == 0)
		{
			return EntraDestra;
		}
		//il treno è a metà della missione
		else
		{
			int cdbPrec = missione[idxMissione - 1];
			//se il cdb precedente è nell'area, sono entrato da sinistra
			if (idxArea > 0 && area[idxArea - 1] == cdbPrec)
			{
				return EntraSinistra;
			}
			else
			{
				return EntraDestra;
			}
		}
	}
	else if (idxArea == 0)
	{
		//il treno è alla fine della missione
		if (idxMissione == missione->Count -1)
		{
			return EntraDestra;
		}
		//il treno è all'inizio della missione
		else if (idxMissione == 0)
		{
			return EntraSinistra;
		}
		//il treno è a metà della missione
		else
		{
			int cdbSucc = missione[idxMissione + 1];
			//se il cdb successivo è nell'area, sono entrato da sinistra
			if (area[idxArea + 1] == cdbSucc)
			{
				return EntraSinistra;
			}
			else
			{
				return EntraDestra;
			}
		}
	}
	else
	{
		//il treno termina la missione in mezzo ad un'area
		if (idxMissione == missione->Count -1)
		{
			int cdbPrec = missione[idxMissione - 1];
			//se il cdb precedente è nell'area, sono entrato da sinistra
			if (idxArea > 0 && area[idxArea - 1] == cdbPrec)
			{
				return EntraSinistra;
			}
			else
			{
				return EntraDestra;
			}
		}
		//il treno inizia la missione in mezzo ad un'area
		else if (idxMissione == 0)
		{
			int cdbSucc = missione[idxMissione + 1];
			//se il cdb successivo è nell'area, sono entrato da sinistra
			if (area[idxArea + 1] == cdbSucc)
			{
				return EntraSinistra;
			}
			else
			{
				return EntraDestra;
			}
		}
		//il treno è a metà della missione ed in mezzo ad un area
		else
		{
			int cdbSucc = missione[idxMissione + 1];
			//se il cdb successivo è nell'area, sono entrato da sinistra
			if (area[idxArea + 1] == cdbSucc)
			{
				return EntraSinistra;
			}
			else
			{
				return EntraDestra;
			}
		}

	}
}

void AreeCritiche::Carica(GestioneAreeCritiche::Output::DatiAree^ dati, Dictionary<int,int>^ posizioniTreni)
{
	areeCritiche = gcnew List<AreaCritica^>();
	limitiAree = gcnew array<int>(dati->AreeCritiche->Count);
	missioni = gcnew Dictionary<int,MissioneAnnotata^>();

	int idArea = 0;
	Console::WriteLine("Loading Areas");

	//Carico aree
	for each (GestioneAreeCritiche::AreeCritiche::IAreaCritica^ area in dati->AreeCritiche)
	{
		if (area->TipoArea == GestioneAreeCritiche::AreeCritiche::TipoArea::Lineare)
		{
			GestioneAreeCritiche::AreeCritiche::AreaCriticaLineare^ lineare = (GestioneAreeCritiche::AreeCritiche::AreaCriticaLineare^) area;
			AreaCriticaLineare^ areanew = gcnew AreaCriticaLineare(lineare->ListaCdb);
			areanew->nome = Convert::ToString(idArea);

			limitiAree[idArea] = 0;
			areeCritiche->Add(areanew);
		}
		else
		{
			GestioneAreeCritiche::AreeCritiche::AreaCriticaCircolare^ circolare = (GestioneAreeCritiche::AreeCritiche::AreaCriticaCircolare^) area;
			AreaCriticaCircolare^ areanew = gcnew AreaCriticaCircolare(circolare->ListaCdb, circolare->Limite);
			areanew->nome = Convert::ToString(idArea);

			limitiAree[idArea] = circolare->Limite;
			areeCritiche->Add(areanew);
		}
		idArea++;
	}

	//Carico missioni annotate
	for each (GestioneAreeCritiche::Output::MissioneAnnotata^ missione in dati->MissioniAnnotate)
	{
		MissioneAnnotata^ missionenew = gcnew MissioneAnnotata();
		missionenew->Trn = Convert::ToInt32(missione->Trn);
		missionenew->AzioniCdb = missione->AzioniCdb;
		missionenew->ListaCdb = missione->ListaCdb;

		missioni->Add(missionenew->Trn, missionenew);
	}

	//Ricalcolo lo stato corrente delle aree basandomi sulle posizioni dei treni
	for each (int trn in posizioniTreni->Keys)
	{
		int cdb = posizioniTreni[trn];
		int idx;
		if (missioni->ContainsKey(trn))
		{
			MissioneAnnotata^ missione = missioni[trn];
			idx = missione->ListaCdb->IndexOf(cdb);

			for (int i = 0; i < areeCritiche->Count; i++)
			{
				AreaCritica^ area = areeCritiche[i];

				if (area->isInside(cdb))
				{
					//Circolare
					if (area->GetType() == AreaCriticaCircolare::typeid)
					{
						if (!area->entrataPermessa(trn, cdb, 1))
						{
							Console::WriteLine("ERRORE: Stato Aree non corretto! TRN:{0}", trn);
						}
						else
						{
							//determino se il treno è in procinto di uscire dall'area critica
							bool uscendo = false;
							if (idx < missione->ListaCdb->Count -1)
							{ 
								int nextcdb = missione->ListaCdb[idx+1];
								if (!area->isInside(nextcdb))
								{
									uscendo = true;
								}
							}

							if (!uscendo)
							{
								area->entrata(trn, cdb, EntrataCircolare);
							}
						}
					}
					//Lineare
					else
					{
						AreaCriticaLineare^ areaLineare = (AreaCriticaLineare^) area;

						if (idx < missione->ListaCdb->Count - 1)
						{
							//cdb successivo della missione
							int cdbsucc = missione->ListaCdb[idx + 1];

							int idxCdbArea = areaLineare->cdbs->IndexOf(cdb);
							if (idxCdbArea < areaLineare->cdbs->Count - 1)
							{
								//cdb successivo dell'area lineare
								int cdbAreaSucc = areaLineare->cdbs[idxCdbArea + 1];
								if (cdbsucc == cdbAreaSucc)
								{
									area->entrata(trn, cdb, EntraSinistra);
								}
							}							
						}

						


						if (cdb == areaLineare->cdbs[0])
						{
							area->entrata(trn, cdb, EntraSinistra);
						}
						else
						{
							

						}
						/*else if (cdb == areaLineare->cdbs[areaLineare->cdbs->Count -1 ])
						{
							area->entrata(trn, cdb, EntraDestra);
						}*/
					}
				}
			}
		}
	}


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
	}
	limitiAree = limitiAreeTmp->ToArray();
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

	return entrataValida;
}
