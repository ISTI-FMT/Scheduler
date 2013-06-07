#pragma once
#using <System.dll>
#include "Itinerario.h"
using namespace System;
using namespace System::Collections::Generic;

ref class stazione
{
	String ^nomeStazione;
	int idStazione;
	//la chiave è prevcdb
	Dictionary<int,List<Itinerario^>^ > ^itinerari;
	//lachiave è id dell'itinerario
	Dictionary<int,Itinerario^ > ^itinerariid;

public:
	stazione(void);
	void setNomeStazione(String ^n){nomeStazione = n;}
	void set_SetIDStazione(int n){idStazione = n;}
	Dictionary<int,List<Itinerario^>^ > ^ getItinerari(){return itinerari;};
	Dictionary<int,Itinerario^ > ^ getItinerariid(){return itinerariid;};
	String ^get_NomeStazione(){return nomeStazione;};
	int get_idStazione(){return idStazione;};
	virtual System::String^ ToString() override;
	//fornendo id dell'itinerario restiuisce una lista di 2 valori interi che rappresentano rispettivamente
	//nid_lrgb e D_stop per quell'itinerario 
	List<int> ^get_infobalise(int id){
		List<int> ^ret = gcnew List<int>();
		if(itinerariid->ContainsKey(id)){
			ret->Add(itinerariid[id]->getLrgb());
			ret->Add(itinerariid[id]->getDStop());
			return ret;
		}
		return nullptr;

	}
};