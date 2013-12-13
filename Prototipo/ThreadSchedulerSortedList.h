#pragma once
#include "wdogcontrol.h"
#include "manager\\ManagerStatoLineaATC.h"
#include "manager\\ManagerStatoLineaIXL.h"
#include "ConfVelocita\\ConfigurazioneVelocita.h"
#using <System.dll>
#include "Event.h"
#include "EventQueue.h"
#include "tabellaOrario\\TabellaOrario.h"
#include "Itinerari\\TabellaStazioni.h"
#include "logger\\Logger.h"
#include "mapTrenoFisicoLogico.h"
#include "messaggi\\Messaggi.h"
#include "wdogcontrol.h"
#include "manager\\ManagerStatoLineaATC.h"
#include "manager\\ManagerStatoLineaIXL.h"
#include "Train.h"
#include "StateObject.h"
#include "ControllerListTrain.h"
#include "ListTrainView.h"
#include "ListTrainModel.h"


/*Utilizzo questa classe per definire il comportamento dello schedulatore*/

using namespace System;

using namespace System::Collections::Generic;


ref class ThreadSchedulerSortedList 
{
	EventQueue ^EQueueIXL;
	EventQueue ^EQueueATO;
	EventQueue ^EQueueATC;
	EventQueue ^EQueueCambioOrario;
	TabellaOrario ^tabOrario;
	TabellaStazioni ^tabItinerari;
	mapTrenoFisicoLogico ^mapTrenoLogFisico;
	ManagerStatoLineaATC ^managerATC;
	ManagerStatoLineaIXL ^managerIXL;
	wdogcontrol ^wdogs;
	String ^ipixl;
	Dictionary<Train^,List<int>^> ^RaccoltaTrenoRequestCDB;
	ConfigurazioneVelocita ^confVelocita;
	bool _shouldStop;
	DateTime timeRicIXL;
	//System::Collections::Generic::SortedList<KeyListTrain^, Train^> ^ListSortedTrains;
	ControllerListTrain ^controlListtrain;
public:
	ThreadSchedulerSortedList(void);


	ThreadSchedulerSortedList(List<EventQueue^> ^E , TabellaOrario ^tabo, TabellaStazioni ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w, ManagerStatoLineaATC ^manATC,ManagerStatoLineaIXL ^manIXL, ConfigurazioneVelocita ^cvel);

	void Schedule();
	void Init();
	void ControllaMSG_ATO();
	void ControllaMSG_IXL();
	bool controllacdb(List<int>^lcdb);
	void ControllaEventiCambioOrario();
	void RequestStop();

	StateObject ^InizializzeATO(int trn,physicalTrain ^Treno);
	StateObject ^SendUpdateMissionATO(int trn,physicalTrain ^Treno,List<Fermata^> ^stops);
	void setMissionPlanMsg(int TRN, pacchettoMissionData ^pkt, List<ProfiloVelocita^>^pvel, List<Fermata^> ^stops);
	static void ReceiveCallback(IAsyncResult^ asyncResult);

	bool SendBloccItinIXL(int NID_ITIN, int Q_CMDITIN);
	List<int> ^RequestItinerarioIXL(int idstazione ,int iditinerario);

};

