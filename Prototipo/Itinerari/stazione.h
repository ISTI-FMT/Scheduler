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
	Dictionary<String^,List<Itinerario^>^ > ^ getItinerari(){return itinerari;};

	virtual System::String^ ToString() override;
};