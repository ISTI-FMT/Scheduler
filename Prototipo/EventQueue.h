#pragma once
#include "Event.h"
#include "messaggi\\stateItinerario.h"
#include "messaggi\\stateCDB.h"
#include "Event.h"

using namespace System;
using namespace System::Collections::Concurrent;

ref class EventQueue  : public IObserver<Event^>
{
	IDisposable ^unsubscriber;
	ConcurrentQueue<Event^> ^queueEvent;
public:
	EventQueue(void);
	virtual void Subscribe(IObservable<Event^> ^provider);
	virtual void OnCompleted();
	virtual void OnError(Exception ^e);
	virtual void OnNext(Event ^value);
	virtual void Unsubscribe();
};

