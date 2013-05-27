#pragma once
#using <System.dll>
#include "itinerarioIngresso.h"
#include "itinerarioUscita.h"
#include "Itinerario.h"
using namespace System;
using namespace System::Collections::Generic;

ref class stazione
{
	String ^nomeStazione;
	int idStazione;
	//la chiave è prevcdb
	Dictionary<String^,List<Itinerario^>^ > ^itinerari;
	//lachiave è id dell'itinerario
	Dictionary<int,Itinerario^ > ^itinerariid;

public:
	stazione(void);
	void setNomeStazione(String ^n){nomeStazione = n;}
	void set_SetIDStazione(int n){idStazione = n;}
	Dictionary<String^,List<Itinerario^>^ > ^ getItinerari(){return itinerari;};
	Dictionary<int,Itinerario^ > ^ getItinerariid(){return itinerariid;};
	String ^get_NomeStazione(){return nomeStazione;};
	int get_idStazione(){return idStazione;};
	virtual System::String^ ToString() override;
	List<int> ^get_infobalise(int id){
		List<int> ^ret = gcnew List<int>();
		if(itinerariid->ContainsKey(id)){
			ret->Add(itinerariid[id]->getLrgb());
			ret->Add(itinerariid[id]->getDStop());
		}
		return ret;

	}
};