#pragma once
#include "..\\messaggi\\stateItinerario.h"
#include "..\\Event.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class ManagerItinerarioIXL  : public IObservable<Event^>
{
	Dictionary<int, stateItinerario^> ^tabella;
	 List<IObserver<Event^>^> ^observers;
public:
	ManagerItinerarioIXL(void);
	void addCheckAndSetItinerario(List<stateItinerario^> ^listaItin);
	void addCheckAndSetItinerario(stateItinerario ^oneItinerario);
	virtual IDisposable ^Subscribe(IObserver<Event^> ^observer);
   

};

ref class Unsub : public  IDisposable
{
    List<IObserver<Event^>^> ^_observers;
    IObserver<Event^> ^_observer;

public:
	Unsub(List<IObserver<Event^>^> ^observers, IObserver<Event^> ^observer)
   {
      _observers = observers;
      _observer = observer;
   };
private:
	 ~Unsub(){
      if ((_observer != nullptr)){
		  _observers->Remove(_observer);
	  }
   };
};