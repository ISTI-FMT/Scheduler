#pragma once
#using <System.dll>
#include "Event.h"
#include "EventQueue.h"
#include "tabellaOrario\\TabellaOrario.h"
#include "Itinerari\\tabellaItinerari.h"
#include "logger\\Logger.h"


using namespace System;


ref class ThreadSchedule
{
	EventQueue ^EQueue;
	TabellaOrario ^tabOrario;
	tabellaItinerari ^tabItinerari;
public:
	ThreadSchedule(EventQueue ^E, TabellaOrario ^tabo, tabellaItinerari ^tabi);

	void SimpleSchedule();
	void Init();
};

