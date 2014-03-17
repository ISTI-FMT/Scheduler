#pragma once
#using <System.dll>
#include "..\\messaggi\\StateCDB.h"
#include "..\\Event.h"
#include "..\\Unsubscriber.h"
using namespace System;
using namespace System::Collections::Generic;

/*utilizzo questa classe per generare l'evento scaturito da un nuovo messaggio di stato della linea proveniente dall'ATC
filtra i messaggi inviando allo scheduler solo quelli che hanno subito una modifica*/

//rappresenta una struttura dati che implementa IObservable e contiene una mappa delle informazioni sullo stato della linea fornite da ATC
public ref class ManagerStatoLineaATC : public IObservable<Event<StateCDB^>^>
{
	//id della mappa è id del CDB
	Dictionary<int, StateCDB^> ^tabellaCDB;
	//id della mappa è il numero del treno
	Dictionary<int,List<StateCDB^>^> ^tabellaTRenoListCDB;
	List<IObserver<Event<StateCDB^>^>^> ^observers;
public:
	ManagerStatoLineaATC(void);
	void addCheckAndSet(List<StateCDB^> ^listaCDB, String ^source);
	void addCheckAndSet(StateCDB ^oneCDB, String ^source);
	//void Notify(StateCDB ^oneCDB, String ^source);
	StateCDB^ getCDB(int idcdb);

	virtual IDisposable ^Subscribe(IObserver<Event<StateCDB^>^> ^observer);
   


};


