#include "AreeCritiche.h"

using namespace System::Xml;


AreeCritiche::AreeCritiche()
{
	areeCritiche = gcnew List<AreaCritica^>();
	XmlFilename = gcnew String("AreeCritiche.xml");
	cdbAree = gcnew Dictionary<int, List<AreaCritica^>^>();
}

void AreeCritiche::leggiFileConfigurazioneAreeCritiche()
{
	XmlReaderSettings^ settings = gcnew XmlReaderSettings();
	settings->IgnoreWhitespace = true;
	settings->IgnoreComments = true;
	XmlReader^ myReader = XmlReader::Create(XmlFilename, settings);
	while (myReader->Read())
            {
                if (myReader->NodeType != XmlNodeType::Element)
                    continue;

                if (myReader->Name == "Area")
                {
                    int id = Convert::ToInt32(myReader->GetAttribute("Id"));
                    //NB:Nel caso di aree circolari, il limite deve essere coerente con i cdb dell'area
                    int limite = Convert::ToInt32(myReader->GetAttribute("Limite"));

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
                //else if (myReader->Name == "Missione")
                //{
                //    missioneCorrente = new MissioneAnnotata();
                //    missioneCorrente.Trn = myReader.GetAttribute("Trn");
                //    res.MissioniAnnotate.Add(missioneCorrente);
                //}
                //else if (myReader->Name == "Cdb")
                //{
                //    SortedDictionary<int, int> azioniCdbCorrente = new SortedDictionary<int, int>();
                //    if (missioneCorrente != null)
                //    {
                //        int cdbId = Convert::ToInt32(myReader.GetAttribute("Id"));
                //        missioneCorrente.ListaCdb.Add(cdbId);
                //    }

                //    XmlReader^ azioniReader = myReader->ReadSubtree();

                //    //leggo il contenuto di Cdb => una lista di elementi Azione
                //    while (!azioniReader.EOF)
                //    {
                //        if (azioniReader.NodeType == XmlNodeType::Element
                //            && azioniReader.Name == "Azione")
                //        {
                //            String^ idAreaStr = azioniReader->GetAttribute("IdArea");
                //            //NOTA: Quando faccio read element content sto effettivamente muovendo il 
                //            //reader, quindi se faccio un secondo Read() mi salto un pezzo
                //            int azione = azioniReader.ReadElementContentAsInt();

                //            azioniCdbCorrente[Convert::ToInt32(idAreaStr)] = azione;
                //        }
                //        else
                //        {
                //            azioniReader.Read();
                //        }
                //    }

                //    if (missioneCorrente != null)
                //    {
                //        //Creo, settate a zero (nessuna azione deve essere compiuta sulle aree corrispondenti), tutte le azioni che mancano
                //        foreach (KeyValuePair<int, int> keyValuePair in limiti)
                //        {
                //            if (!azioniCdbCorrente.ContainsKey(keyValuePair.Key))
                //            {
                //                azioniCdbCorrente[keyValuePair.Key] = 0;
                //            }
                //        }

                //        missioneCorrente.AzioniCdb.Add(azioniCdbCorrente.Values.ToArray());
                //    }
                //}
            }
}

/*
 Ritorna TRUE se un treno può entrare nel cdb, FALSE altrimenti.
 Il treno può entrare nel cdb se tutte le aree critiche che lo contengono non hanno raggiunto il massimo numero di treni consentito
*/
bool AreeCritiche::richiestaCdb(int cdb)
{
	return false;
}

void AreeCritiche::entrataCdb(int cdb)
{
	
}

void AreeCritiche::uscitaCdb(int cdb)
{
	
}
