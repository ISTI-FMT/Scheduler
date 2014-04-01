#pragma once
#include "wdogcontrol.h"
#include "manager\\ManagerStatoLineaATC.h"
#include "manager\\ManagerStatoLineaIXL.h"
#include "ConfVelocita\\ConfigurazioneVelocita.h"
#using <System.dll>
#include "EventQueue.h"
#include "tabellaOrario\\TabellaOrario.h"
#include "Itinerari\\TabellaStazioni.h"
#include "logger\\Logger.h"
#include "mapTrenoFisicoLogico.h"
#include "messaggi\\Messaggi.h"
#include "wdogcontrol.h"
#include "manager\\ManagerStatoLineaATC.h"
#include "manager\\ManagerStatoLineaIXL.h"
#include "AreeCritiche\\AreeCritiche.h"
#include "Train.h"
//#include "StateObject.h"
#include "ControllerListTrain.h"
#include "ListTrainView.h"
#include "ListTrainModel.h"


/*Utilizzo questa classe per definire il comportamento dello schedulatore con la lista pronti ordinata*/

using namespace System;
using namespace System::Net;
using namespace System::Collections::Generic;
using namespace System::Threading;

ref class ThreadSchedulerSortedList 
{
	EventQueue<StateCDB^> ^EQueueIXL;
	EventQueue<physicalTrain^> ^EQueueATO;
	EventQueue<StateCDB^> ^EQueueATC;
	EventQueue<List<Fermata^>^> ^EQueueCambioOrario;
	//EventQueue<int> ^EQueueCambioTrenoPrior;
	//EventQueue<StateTrain> ^EQueueCambioTrenoStato;
	TabellaOrario ^tabOrario;
	TabellaStazioni ^tabItinerari;
	AreeCritiche ^areeCritiche;
	mapTrenoFisicoLogico ^mapTrenoLogFisico;
	ManagerStatoLineaATC ^managerATC;
	ManagerStatoLineaIXL ^managerIXL;
	wdogcontrol ^wdogs;
	String ^ipixl;
	Dictionary<Train^,List<int>^> ^RaccoltaTrenoRequestCDB;
	ConfigurazioneVelocita ^confVelocita;
	List<physicalTrain^> ^listatrenipresentati;
	bool _shouldStop;
	bool _blockAreeCritiche;
	DateTime timeRicIXL;
	//System::Collections::Generic::SortedList<KeyListTrain^, Train^> ^ListSortedTrains;
	ControllerListTrain ^controlListtrain;
	static ManualResetEvent ^mre = gcnew ManualResetEvent(false);
	Prototipo::ListTrainView ^view;
public:
	ThreadSchedulerSortedList(void);


	ThreadSchedulerSortedList(EventQueue<StateCDB^> ^E0,EventQueue<StateCDB^>^E1,EventQueue<physicalTrain^>^E3, TabellaOrario ^tabo, TabellaStazioni ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w, ManagerStatoLineaATC ^manATC,ManagerStatoLineaIXL ^manIXL, ConfigurazioneVelocita ^cvel, AreeCritiche^ areeCritiche);

	property bool StopAreecritiche 
	{
		bool get()
		{
			return _blockAreeCritiche;
		}

		void set(bool a){

			_blockAreeCritiche=a;
		}

	}

	void Schedule();
	void Init();
	void ControllaMSG_ATO();
	void ControllaMSG_IXL();
	bool controllacdb(List<int>^lcdb);
	void ControllaEventiCambioOrario();
	void RequestStop();
	

	StateObject ^InizializzeATO(int trn,physicalTrain ^Treno);
	StateObject ^SendUpdateMissionATO(int trn,physicalTrain ^Treno,List<Fermata^> ^stops);
	/*void setMissionPlanMsg(int TRN, pacchettoMissionData ^pkt, List<ProfiloVelocita^>^pvel, List<Fermata^> ^stops);*/
	static void ReceiveCallback(IAsyncResult^ asyncResult);

	bool SendBloccItinIXL(int NID_ITIN, QCmdItinerari Q_CMDITIN);
	List<int> ^RequestItinerarioIXL(int idstazione ,int iditinerario);
	static void Connect(EndPoint ^remoteEP, Socket ^client);
	static void ConnectCallbackMethod(IAsyncResult ^ar);

	static void SendCallbackMethod(IAsyncResult ^ar);
	static void Send(Socket ^client, array<Byte> ^data);

};

