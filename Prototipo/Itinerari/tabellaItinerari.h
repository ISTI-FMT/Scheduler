#pragma once
#include "stazione.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class tabellaItinerari
{

	Dictionary<int,stazione^ > ^mapidstazioneitinerari;
	String ^schemaxsd;
public:
	tabellaItinerari(void);

	void leggifileconfigurazioneItinerari(String ^nomefile);


	virtual System::String^ ToString() override;

	//fornendo id della stazione e dell'itinerario restiuisce una lista di 2 valori interi che rappresentano rispettivamente
	//nid_lrgb e D_stop per quell'itinerario 
	List<int> ^get_infobalise(int idstazione, int iditini){

		if(mapidstazioneitinerari->ContainsKey(idstazione)){
			return mapidstazioneitinerari[idstazione]->get_infobalise(iditini);
		}
		return nullptr;

	}

	int get_CdbPrecItinerario(int stazione, int iditin);
	
	int get_CdbSuccItinerario(int stazione, int iditin);

	Dictionary<int,stazione^ > ^getMap(){return mapidstazioneitinerari;};
};

