#include "TabellaOrario.h"
#using <System.Xml.dll>
#include <iostream>
#include "..\\String2string.h"
#include <iostream>
using namespace std;
using namespace System;
using namespace System::Globalization;
TabellaOrario::TabellaOrario(void)
{
	tabella = gcnew List<TrenoFermate^>;
}

// funzione che converte una System::String in un intero
int TabellaOrario::convertiString2int(System::String ^StringValue)
{
	// converto da System::String a std::string
	std::string stdString = String2string(StringValue);
	// converto da std::string a int
	int intValue = atoi(stdString.c_str());
	return intValue;
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
	if(tabella->Count > 0)
		return tabella[0]->getIdTreno();
	else
		return 0;
}

// questa funzione legge il file di configurazione contenente la descrizione della tabella orario
void TabellaOrario::leggiTabellaOrario(string nomeFile)
{
	// oggetti DateTime di supporto
	DateTime orarioSupporto1, orarioSupporto2, orarioSupporto3;
	double secs;
	TimeSpan sinceMidnight;

	System::String^ nome = gcnew System::String(nomeFile.c_str());
	System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(nome);
	// per ogni treno presente nel file di configurazione della tabella orario...
	while (reader->ReadToFollowing("treno")){
		System::Xml::XmlReader ^inner = reader->ReadSubtree();
		// ...leggo l'id del treno
		System::String ^SystemStringIdTreno = reader->GetAttribute("id");
		// converto l'id del treno da System::String a int
		int idTreno = convertiString2int(SystemStringIdTreno);
		// creo un nuovo treno
		TrenoFermate ^treno = gcnew TrenoFermate(idTreno);

		// per ogni stazione in cui il treno in question deve fermarsi
		while (inner->ReadToFollowing("stazione")){
			// creo una nuova fermata
			Fermata ^stop = gcnew Fermata;
			// leggo l'id della stazione
			System::String ^SystemStringIdStazione = inner->GetAttribute("id");
			// configuro l'id della stazione
			stop->setIdStazione(SystemStringIdStazione);

			// leggo l'orario di arrivo
			inner->ReadToFollowing("arrivo");
			System::String ^SystemStringOrarioArrivo = inner->ReadString();
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
			inner->ReadToFollowing("partenza");
			System::String ^SystemStringOrarioPartenza = inner->ReadString();
			// aggiungo alla data corrente l'ora, minuto e secondi letti
			orarioSupporto2=DateTime::ParseExact(SystemStringOrarioPartenza, "HH:mm:ss", CultureInfo::InvariantCulture);
			//DateTime t = DateTime::ParseExact(SystemStringOrarioPartenza, "HH:mm:ss", CultureInfo::InvariantCulture);
			
			// calcolo la differenza fra la data preparata e la data "di oggi" (alla mezzanotte)
			sinceMidnight = orarioSupporto2- orarioSupporto3;
			// calcolo quanti secondi sono passati dalla mezzanotte
			secs = sinceMidnight.TotalSeconds;
			// configuro l'orario di arrivo della farmata in risoluzione di 30 s
			stop->setOrarioPartenza(secs/30);

			// leggo il binario programmato
			inner->ReadToFollowing("binarioprogrammato");
			System::String ^SystemStringBinarioProgrammato = inner->ReadString();
			// converto il binario programmato da System::String a int
			int binarioProgrammato = convertiString2int(SystemStringBinarioProgrammato);
			// configuro il binario programmato
			stop->setBinarioProgrammato(binarioProgrammato);

			// leggo il lato di apertura porte programmato
			inner->ReadToFollowing("latoaperturaporteprogrammato");
			System::String ^SystemStringLatoProgrammato = inner->ReadString();	
			// converto da System::String a std::string
			//string stringLatoAperturaPorte = convertiString2string(SystemStringLatoProgrammato);
			int latoParturaPorte;
			if(SystemStringLatoProgrammato == "dx")
				latoParturaPorte = aperturaTrenoDx;
			else if(SystemStringLatoProgrammato == "sx")
				latoParturaPorte = aperturaTrenoSx;
			else if(SystemStringLatoProgrammato == "sd")
				latoParturaPorte = aperturaTrenoDxSx;
			else
				latoParturaPorte = noApertura;
			// configuro il lato apertura porte programmato programmato
			stop->setLatoAperturaPorte(latoParturaPorte);

			// a questo punto posso aggiungere la fermata alla lista delle fermate del treno in questione
			treno->aggiungiFermata(stop);

			//System::Console::WriteLine(idTreno+idSTazione+orarioArrivo+orarioPartenza+binarioProgrammato+latoProgrammato);
			System::Console::WriteLine();
		}
		// a questo punto aggiungo il treno alla tabella orario
		aggiungiTreno(treno);
	}	
}

// funzione che prende in ingresso un TRN ed un messaggio di tipo missionPlan, e riempie i campi del messaggio con i dati relativi
// alla missione associata al TRN in questione
void TabellaOrario::setMissionPlanMessage(int TRN, pacchettoMissionPlan *pkt)
{
	
	// ottengo un riferimento alle fermate del treno TRN
	TrenoFermate ^treno = getTrenoFermate(TRN);
	// se il teno esiste
	if(treno!=nullptr)
	{
		// ottengo un riferimento alla lista delle feremate del treno
		List<Fermata^> ^stops = treno->getListaFermate();
		//Todo: V_mission D_mission ancora da trattare
		pkt->setN_ITER1(0);
		// -1 perchè la prima fermata non viene considerata negli N_ITER
		pkt->setN_ITER2((stops->Count) - 1);
		int i = 0;
		for each (Fermata ^stop in stops)
		{
			pkt->setQ_DOORS(i, stop->getLatoAperturaPorte());
			int Costanteaperturaporte = 30;
			int orarioPartenza = (int)stop->getOrarioPartenza();
			int orarioArrivo =  (int)stop->getOrarioArrivo();
			pkt->setT_START_TIME(i,orarioPartenza);
			pkt->setT_DOORS_TIME(i, ((orarioPartenza-Costanteaperturaporte) - orarioArrivo));
			++i;
		}
	}
}

// funzione che restituisce un riferimento alla lista delle fermate relative al treno identificato dal TRN passato come parametro
TrenoFermate^ TabellaOrario::getTrenoFermate(int TRN)
{
	for each(TrenoFermate ^treno in tabella)
	{
		if(treno->getIdTreno() == TRN)
		{
			return treno;
		}
	}

	
	return nullptr;
}

void TabellaOrario::aggiungiTreno(TrenoFermate ^treno)
{
	tabella->Add(treno);
}

/*
ostream& operator<<(ostream &out, TabellaOrario &tabella)
{
	for (std::list<TrenoFermate>::iterator it=tabella.tabella.begin(); it != tabella.tabella.end(); ++it)
		out << (*it) << endl;
	return out;
}
*/
