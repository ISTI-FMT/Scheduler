#pragma once
#include "stazione.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;


/*utilizzo questa classe per rappresentare le informazioni delle stazioni parsate dal file xml ConfigurazioneItinerari.xml
queste vengono inserite in una mappa tra id della stazione e le informazioni della stazione serializzate nella classe stazione.h
*/

//questa classe rappresenta una mappa tra id della stazione e la stazione 
public ref class TabellaStazioni
{

	Dictionary<int,stazione^ > ^mapidstazioneitinerari;
	String ^schemaxsd;
public:
	TabellaStazioni(void);

	void leggifileconfigurazioneItinerari();
	void leggifileconfigurazioneFermate();

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

	List<int> ^get_Cdb_Itinerario(int stazione, int iditin);

	Dictionary<int,stazione^ > ^getMap(){return mapidstazioneitinerari;};
};

