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
//#include "StateObject.h"
#include "ConfVelocita\\ConfigurazioneVelocita.h"
#include "threads\\ThreadSchedulerTrain.h"

/*Utilizzo questa classe per definire il comportamento dello schedulatore*/

using namespace System;

using namespace System::Collections::Concurrent;
//questo thread rappresenta lo scheduler dell'ATS

enum StateSimpleSchedule {StatoIgnoto = -1, PresentazioneTreno = 0, ControlloTreno = 1, RicItinerarioEntrata=3, RicItinerarioUscita=4};
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
	String ^ipixl;
	List<int> ^listIdCdbItinRic;
	ConfigurazioneVelocita ^confVelocita;
	bool _shouldStop;
	List<ThreadSchedulerTrain^> ^listThreadTrain;
public:
	ThreadSchedule(List<EventQueue^> ^E , TabellaOrario ^tabo, tabellaItinerari ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w, ManagerStatoLineaATC ^manATC,ManagerStatoLineaIXL ^manIXL, ConfigurazioneVelocita ^cvel);

	void SimpleSchedule();
	void Init();
	//StateObject ^SendTCPMsg(int trn,physicalTrain ^Treno);
	//bool SendBloccItinIXL(int NID_ITIN, int Q_CMDITIN);
	//void StampaStato(int stato);
	//bool richestaItinerarioIXL(int idstazione ,int iditinerario);
	bool controllacdb(List<int>^lcdb);
	//static void ReceiveCallback(IAsyncResult^ asyncResult);
	//static void SendCallback(IAsyncResult^ asyncResult);
	void RequestStop();
};

