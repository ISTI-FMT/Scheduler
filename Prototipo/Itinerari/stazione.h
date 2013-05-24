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
	Dictionary<String^,List<Itinerario^>^ > ^itinerari;

public:
	stazione(void);
	void setNomeStazione(String ^n){nomeStazione = n;}
	void set_SetIDStazione(int n){idStazione = n;}
	Dictionary<String^,List<Itinerario^>^ > ^ getItinerari(){return itinerari;};
	String ^get_NomeStazione(){return nomeStazione;};
	int get_idStazione(){return idStazione;};
	virtual System::String^ ToString() override;
};