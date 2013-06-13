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
#include "manager\\ManagerStatoLineaATC.h"
#include "manager\\ManagerStatoLineaIXL.h"
#include "StateObject.h"

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
	ManagerStatoLineaATC ^managerATC;
	ManagerStatoLineaIXL ^managerIXL;
	wdogcontrol ^wdogs;
public:
	ThreadSchedule(List<EventQueue^> ^E , TabellaOrario ^tabo, tabellaItinerari ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w, ManagerStatoLineaATC ^manATC,ManagerStatoLineaIXL ^manIXL);

	void SimpleSchedule();
	void Init();
	StateObject ^SendTCPMsg(int trn,phisicalTrain ^Treno);
	bool SendBloccItinIXL(int NID_ITIN, int Q_CMDITIN);
	bool richestaItinerarioIXL(int iditinerario);
	static void ReceiveCallback(IAsyncResult^ asyncResult);
};

