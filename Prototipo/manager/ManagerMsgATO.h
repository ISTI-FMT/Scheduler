#pragma once
#using <System.dll>
#include "..\\messaggi\\StateCDB.h"
#include "..\\physicalTrain.h"
#include "..\\Event.h"


using namespace System;
using namespace System::Collections::Generic;

/*utilizzo questa classe per generare l'evento scaturito da un nuovo messaggio di presentazione dell'ATO*/

//rappresenta una struttura dati che implementa IObservable e contiene una mappa delle informazioni di presentazione dei ATO
ref class ManagerMsgATO : public IObservable<Event^>
{
	Dictionary<int, physicalTrain^> ^tabellaTrain;
	 List<IObserver<Event^>^> ^observers;
public:
	ManagerMsgATO(void);
	void addCheckAndSet(List<physicalTrain^> ^listatrain, String ^source);
	void addCheckAndSet(physicalTrain ^onetrain, String ^source);

	

	virtual IDisposable ^Subscribe(IObserver<Event^> ^observer);
   


};

ref class Unsubus : public  IDisposable
{
    List<IObserver<Event^>^> ^_observers;
    IObserver<Event^> ^_observer;

public:
	Unsubus(List<IObserver<Event^>^> ^observers, IObserver<Event^> ^observer)
   {
      _observers = observers;
      _observer = observer;
   };
private:
	 ~Unsubus(){
      if ((_observer != nullptr)){
		  _observers->Remove(_observer);
	  }
   };
};