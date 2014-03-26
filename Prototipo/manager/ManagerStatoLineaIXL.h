#pragma once
#using <System.dll>
#include "..\\messaggi\\StateCDB.h"
#include "..\\messaggi\\StateItinerario.h"
#include "..\\Unsubscriber.h"
#include "..\\Event.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Diagnostics::CodeAnalysis;

/*utilizzo questa classe per generare gli eventi scaturiti da un nuovi messaggi di stato della linea o stato degli itinerari provenienti dall'IXL
filtra i messaggi inviando allo scheduler solo quelli che hanno subito una modifica*/

//rappresenta una struttura dati che implementa IObservable e contiene una mappa delle informazioni sullo stato della linea fornite da IXL
public ref class ManagerStatoLineaIXL : public IObservable<Event<StateCDB^>^>
{
	Dictionary<int, StateCDB^> ^tabellaCDB;
	Dictionary<int, StateItinerario^> ^tabellaItin;
	 List<IObserver<Event<StateCDB^>^>^> ^observers;
public:
	ManagerStatoLineaIXL(void);
	void addCheckAndSet(List<StateCDB^> ^listaCDB, String ^source);
	void addCheckAndSet(StateCDB ^oneCDB, String ^source);
	
	[ExcludeFromCodeCoverage]
	void addCheckAndSet(List<StateItinerario^> ^listaItin, String ^source);
	
	[ExcludeFromCodeCoverage]
	void addCheckAndSet(StateItinerario ^oneItinerario, String ^source);
	
	[ExcludeFromCodeCoverage]
	StateItinerario ^getItinerario(int iditin);

	StateCDB^  StatoCDB(int idcdb);

	virtual IDisposable ^Subscribe(IObserver<Event<StateCDB^>^> ^observer);
   


};

