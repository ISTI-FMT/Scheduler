#pragma once
#using <System.dll>
#include "Event.h"
#include "EventQueue.h"
#include "tabellaOrario\\TabellaOrario.h"
#include "Itinerari\\tabellaItinerari.h"
#include "logger\\Logger.h"
#include "mapTrenoFisicoLogico.h"
#include "messaggi\\Messaggi.h"
#include "wdogcontrol.h"


using namespace System;

using namespace System::Collections::Concurrent;

ref class ThreadSchedule
{
	EventQueue ^EQueueIXL;
	EventQueue ^EQueueATO;
	EventQueue ^EQueueATC;
	TabellaOrario ^tabOrario;
	tabellaItinerari ^tabItinerari;
	mapTrenoFisicoLogico ^mapTrenoLogFisico;
	wdogcontrol ^wdogs;
public:
	ThreadSchedule(List<EventQueue^> ^E , TabellaOrario ^tabo, tabellaItinerari ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w);

	void SimpleSchedule();
	void Init();
	bool SendTCPMsg(int trn,phisicalTrain ^Treno);
	bool SendBloccItinIXL();
};

