#pragma once
#include "binario.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class tabellaFermate
{
	// tabella delle fermate. L'indice è l'id della fermata
	Dictionary<String ^, List<binario^> ^> ^tabella;
public:
	tabellaFermate(void);

	void addFermata(String ^nomeFermata, List<binario^> ^binari){tabella->Add(nomeFermata, binari);};

	void leggifileconfigurazioneFermate(String ^nomeFile);
	
	virtual System::String^ ToString() override;
	
	
};

