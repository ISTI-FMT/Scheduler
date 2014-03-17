#pragma once
#using <System.dll>
#include "..\\messaggi\\StateCDB.h"
#include "..\\physicalTrain.h"
#include "..\\Event.h"
#include "..\\Unsubscriber.h"

using namespace System;
using namespace System::Collections::Generic;

/*utilizzo questa classe per generare l'evento scaturito da un nuovo messaggio di presentazione dell'ATO*/

//rappresenta una struttura dati che implementa IObservable e contiene una mappa delle informazioni di presentazione dei ATO
public ref class ManagerMsgATO : public IObservable<Event<physicalTrain^>^>
{
	Dictionary<int, physicalTrain^> ^tabellaTrain;
	 List<IObserver<Event<physicalTrain^>^>^> ^observers;
public:
	ManagerMsgATO(void);
	void addCheckAndSet(List<physicalTrain^> ^listatrain, String ^source);
	void addCheckAndSet(physicalTrain ^onetrain, String ^source);

	

	virtual IDisposable ^Subscribe(IObserver<Event<physicalTrain^>^> ^observer);
   
	void Notify(physicalTrain ^onetrain);

};

