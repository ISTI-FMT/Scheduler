#pragma once
#using <System.dll>
#include "..\\messaggi\\StateCDB.h"
#include "..\\messaggi\\StateItinerario.h"

#include "..\\Event.h"
using namespace System;
using namespace System::Collections::Generic;

ref class ManagerStatoLineaIXL : public IObservable<Event^>
{
	Dictionary<int, StateCDB^> ^tabellaCDB;
	Dictionary<int, StateItinerario^> ^tabellaItin;
	 List<IObserver<Event^>^> ^observers;
public:
	ManagerStatoLineaIXL(void);
	void addCheckAndSet(List<StateCDB^> ^listaCDB, String ^source);
	void addCheckAndSet(StateCDB ^oneCDB, String ^source);

	void addCheckAndSet(List<StateItinerario^> ^listaItin, String ^source);
	void addCheckAndSet(StateItinerario ^oneItinerario, String ^source);

	StateItinerario ^getItinerario(int iditin);

	StateCDB^  StatoCDB(int idcdb);

	virtual IDisposable ^Subscribe(IObserver<Event^> ^observer);
   


};

ref class Unsubscriber : public  IDisposable
{
    List<IObserver<Event^>^> ^_observers;
    IObserver<Event^> ^_observer;

public:
	Unsubscriber(List<IObserver<Event^>^> ^observers, IObserver<Event^> ^observer)
   {
      _observers = observers;
      _observer = observer;
   };
private:
	 ~Unsubscriber(){
      if ((_observer != nullptr)){
		  _observers->Remove(_observer);
	  }
   };
};