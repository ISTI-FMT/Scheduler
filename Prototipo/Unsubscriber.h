#pragma once
#using <System.dll>
#include "Event.h"
/*classe generica per disiscriversi nel pattern observer*/
using namespace System::Collections::Generic;
using namespace System::Diagnostics::CodeAnalysis;
using namespace System;
generic <typename T>

[ExcludeFromCodeCoverage]
public ref class Unsubscriber : public  IDisposable
{
	
    List<IObserver<T>^> ^_observers;
    IObserver<T> ^_observer;

public:
	/*Unsubscriber(void);*/
	Unsubscriber(List<IObserver<T>^> ^observers, IObserver<T> ^observer)
   {
      _observers = observers;
      _observer = observer;
   };
	void createUnsub(List<IObserver<T>^> ^observers, IObserver<T> ^observer){ _observers = observers;
      _observer = observer;};
private:
	 ~Unsubscriber(){
      if ((_observer != nullptr)){
		  _observers->Remove(_observer);
	  }
   };
};