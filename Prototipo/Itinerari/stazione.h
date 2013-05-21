#pragma once
#using <System.dll>
#include "itinerarioIngresso.h"
#include "itinerarioUscita.h"
using namespace System;
using namespace System::Collections::Generic;

ref class stazione
{
	String ^nomeStazione;
	int idStazione;
	Dictionary<itinerarioIngresso^, List<int>^> ^itinerariIngresso;
	Dictionary<itinerarioUscita^, List<int>^> ^itinerariUscita;
public:
	stazione(void);
	void setNomeStazione(String ^n){nomeStazione = n;}
};