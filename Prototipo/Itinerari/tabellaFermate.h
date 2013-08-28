#pragma once
#include "binario.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

/*utilizzo questa classe per rappresentare le informazioni delle stazioni parsate dal file xml ConfigurazioneFermate.xml
queste vengono inserite in una mappa tra id delle fermata ed una lista di "binario"
contiene i metodi per leggere il file di configurazione verificarlo con lo scheda xsd..
*/


//questa classe contiene una mappa tra id delle fermata ed una lista di "binario"
ref class tabellaFermate
{
	// dizionario delle fermate. L'indice � l'id della fermata
	Dictionary<String ^, List<binario^> ^> ^tabella;
	String ^schemaxsd;
public:
	tabellaFermate(void);

	void addFermata(String ^nomeFermata, List<binario^> ^binari){tabella->Add(nomeFermata, binari);};

	Dictionary<String ^, List<binario^> ^> ^getTabFermate(){return tabella;};

	void leggifileconfigurazioneFermate(String ^nomeFile);

	virtual System::String^ ToString() override;

	//fornendo id della fermata il binario e banchina restiuisce una lista di 2 valori interi che rappresentano rispettivamente
	//nid_lrgb e D_stop per quella fermata 
	List<int> ^get_infobalise(String ^idfermata, int binp, int banchina){
		List<int> ^ret = gcnew List<int>();
		if(tabella->ContainsKey(idfermata)){
			List<binario^> ^listBin = tabella[idfermata];
			for each (binario ^bin in listBin)
			{
				if((bin->getBin()==binp) && (bin->getLatoBanchina()==banchina)){
					ret->Add(bin->getNid_lrgb());
					ret->Add(bin->getD_stop());
				}
			}
		}

		return ret;

	}


};

