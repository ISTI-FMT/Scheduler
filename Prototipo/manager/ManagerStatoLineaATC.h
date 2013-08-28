#pragma once
#using <System.dll>
#include "..\\messaggi\\StateCDB.h"
#include "..\\Event.h"
using namespace System;
using namespace System::Collections::Generic;

/*utilizzo questa classe per generare l'evento scaturito da un nuovo messaggio di stato della linea proveniente dall'ATC
filtra i messaggi inviando allo scheduler solo quelli che hanno subito una modifica*/

//rappresenta una struttura dati che implementa IObservable e contiene una mappa delle informazioni sullo stato della linea fornite da ATC
ref class ManagerStatoLineaATC : public IObservable<Event^>
{
	//id della mappa è id del CDB
	Dictionary<int, StateCDB^> ^tabellaCDB;
	//id della mappa è il numero del treno
	Dictionary<int,List<StateCDB^>^> ^tabellaTRenoListCDB;
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