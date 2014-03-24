#include "AreeCritiche.h"

using namespace System::Xml;
using namespace System::Xml::Schema;

AreeCritiche::AreeCritiche()
{
	areeCritiche = gcnew List<AreaCritica^>();
	missioni = gcnew Dictionary<int,MissioneAnnotata^>();
	XmlFilename = gcnew String("AreeCritiche.xml");
	XsdFilename = gcnew String("AreeCritiche.xsd");
	cdbAree = gcnew Dictionary<int, List<AreaCritica^>^>();
	leggiFileConfigurazioneAreeCritiche( System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream(XmlFilename));
}

AreeCritiche::AreeCritiche(String ^xmlAreecritiche)
{
	areeCritiche = gcnew List<AreaCritica^>();
	XmlFilename = xmlAreecritiche;
	XsdFilename = gcnew String("AreeCritiche.xsd");
	cdbAree = gcnew Dictionary<int, List<AreaCritica^>^>();
	try{
		System::IO::FileStream ^SourceStream = System::IO::File::Open(xmlAreecritiche, System::IO::FileMode::Open);
		leggiFileConfigurazioneAreeCritiche(SourceStream);
	}catch(System::Exception ^e){
		Console::WriteLine("File non esiste");
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
			}
			else
			{
				area = gcnew AreaCriticaCircolare(listaCdb, limite);
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
