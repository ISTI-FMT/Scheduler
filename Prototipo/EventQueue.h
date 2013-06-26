#pragma once
#include "Event.h"
#include "messaggi\\StateItinerario.h"
#include "messaggi\\StateCDB.h"
#include "Event.h"

using namespace System;
using namespace System::Collections::Concurrent;
//rappresenta una coda di eventi che implementa l'interfaccia observer 
//contiene i metodi per sottoscrivere l'oggetto osservabile
 ref class EventQueue  : public IObserver<Event^>
{
	IDisposable ^unsubscriber;
	ConcurrentQueue<Event^> ^queueEvent;
public:
	EventQueue(void);
	virtual void Subscribe(IObservable<Event^> ^provider);
	Event ^getEvent();
	virtual void OnCompleted();
	virtual void OnError(Exception ^e);
	virtual void OnNext(Event ^value);
	virtual void Unsubscribe();
};

