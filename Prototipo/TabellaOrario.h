#pragma once
#include "TrenoFermate.h"
#include <iostream>
using namespace std;

/*
Questa classe è utilizzata per gestire la tabella orario dell'ATS attraverso una lista di oggetti di tipo TrenoFermate
*/
class TabellaOrario
{
	std::list<TrenoFermate> tabella;
	void aggiungiTreno(TrenoFermate &treno);
	// funzione che converte una System::String in un intero
	int convertiString2int(System::String ^StringValue);
	// funzione che converte una System::String in un std::string
	string convertiString2string(System::String ^StringValue);
public:
	TabellaOrario(void);
	// questa funzione legge il file di configurazione contenente la descrizione della tabella orario
	void leggiTabellaOrario(string nomeFile);
	~TabellaOrario();
};

