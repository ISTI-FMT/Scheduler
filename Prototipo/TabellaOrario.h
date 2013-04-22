#pragma once
#include "TrenoFermate.h"
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
	~TabellaOrario();
};

