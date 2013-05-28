#pragma once
#include "binario.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class tabellaFermate
{
	// tabella delle fermate. L'indice è l'id della fermata
	Dictionary<int, List<binario^> ^> ^tabella;
public:
	tabellaFermate(void);

	void addFermata(int idFermata, List<binario^> ^binari){tabella->Add(idFermata, binari);};

	void leggifileconfigurazioneFermate(String ^nomeFile);
	
	virtual System::String^ ToString() override;
	
	int convertiString2int(System::String ^StringValue);
};

