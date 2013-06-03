#pragma once
#using <System.dll>
#include "..\\messaggi\\stateCDB.h"
#include "..\\Event.h"
using namespace System;
using namespace System::Collections::Generic;

ref class ManagerCDBIXL : public IObservable<Event^>
{
	Dictionary<int, stateCDB^> ^tabella;
	 List<IObserver<Event^>^> ^observers;
public:
	ManagerCDBIXL(void);
	void addCheckAndSetCDB(List<stateCDB^> ^listaCDB);
	void addCheckAndSetCDB(stateCDB ^oneCDB);

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