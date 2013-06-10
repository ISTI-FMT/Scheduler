#pragma once
#using <System.dll>
#include "..\\messaggi\\StateCDB.h"


#include "..\\Event.h"
using namespace System;
using namespace System::Collections::Generic;

ref class ManagerStatoLineaATC : public IObservable<Event^>
{
	Dictionary<int, StateCDB^> ^tabellaCDB;
	 List<IObserver<Event^>^> ^observers;
public:
	ManagerStatoLineaATC(void);
	void addCheckAndSet(List<StateCDB^> ^listaCDB, String ^source);
	void addCheckAndSet(StateCDB ^oneCDB, String ^source);

	StateCDB^ getCDB(int idcdb);

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