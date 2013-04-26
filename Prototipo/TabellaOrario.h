#pragma once
#include "TrenoFermate.h"
#include "pacchettoMissionPlan.h"
#include <iostream>
using namespace std;

/*-----------------------------------------------------------------------------------------------
L'ATS legge il contenuto della tabella orario da un file di configurazione e memorizza queste informazioni
in apposite strutture dati.
-------------------------------------------------------------------------------------------------*/

// Questa classe è utilizzata per gestire la tabella orario dell'ATS attraverso una lista di oggetti di tipo TrenoFermate
class TabellaOrario
{
	std::list<TrenoFermate> tabella;
	void aggiungiTreno(TrenoFermate &treno);
	// funzione che converte una System::String in un intero
	int convertiString2int(System::String ^StringValue);
	// funzione che converte una System::String in un std::string
	string convertiString2string(System::String ^StringValue);
	friend ostream& operator<<(ostream &out, TabellaOrario &tabella);
public:
	TabellaOrario(void);
	// funzione che restituisce un qualsiasi TRN nella tabella orario (di fatto il primo)
	int getFirstTRN();
	// questa funzione legge il file di configurazione contenente la descrizione della tabella orario
	void leggiTabellaOrario(string nomeFile);
	// funzione che prende in ingresso un TRN ed un messaggio di tipo missionPlan, e riempie i campi del messaggio con i dati relativi
	// alla missione associata al TRN in questione
	void setMissionPlanMessage(int TRN, pacchettoMissionPlan *pkt);
	// funzione che restituisce un riferimento alla lista delle fermate relative al treno identificato dal TRN passato come parametro
	TrenoFermate& getTrenoFermate(int TRN, bool &error);
	~TabellaOrario();
};

