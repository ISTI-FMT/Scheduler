#pragma once
#using <System.dll>
#include "..\\messaggi\\StateCDB.h"
#include "..\\phisicalTrain.h"


#include "..\\Event.h"
using namespace System;
using namespace System::Collections::Generic;

ref class ManagerMsgATO : public IObservable<Event^>
{
	Dictionary<int, phisicalTrain^> ^tabellaTrain;
	 List<IObserver<Event^>^> ^observers;
public:
	ManagerMsgATO(void);
	void addCheckAndSet(List<phisicalTrain^> ^listaCDB, String ^source);
	void addCheckAndSet(phisicalTrain ^oneCDB, String ^source);

	

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