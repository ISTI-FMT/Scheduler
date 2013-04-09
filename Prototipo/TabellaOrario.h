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
public:
	TabellaOrario(void);
	void leggiTabellaOrario(string nomeFile);
	~TabellaOrario();
};

