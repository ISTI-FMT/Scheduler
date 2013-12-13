#pragma once
#using <System.dll>
#include "Event.h"
using namespace System::Collections::Generic;
using namespace System;

public ref class Unsubscriber : public  IDisposable
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