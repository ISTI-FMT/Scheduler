#pragma once
#include "messaggi\\StateItinerario.h"
#include "messaggi\\StateCDB.h"
#include "Event.h"
/*questa classe rappresenta la struttura dati coda di eventi che lo schedulatore interroga per avere l'evento successivo*/
using namespace System;
using namespace System::Collections::Concurrent;
using namespace System::Diagnostics::CodeAnalysis;
//rappresenta una coda di eventi che implementa l'interfaccia observer 
//contiene i metodi per sottoscrivere l'oggetto osservabile ed è generica 



generic <typename T>
[ExcludeFromCodeCoverage]
public ref class EventQueue  : public IObserver<Event<T>^>
{
	IDisposable ^unsubscriber;
	ConcurrentQueue<Event<T>^> ^queueEvent;
public:
	EventQueue(void){
		queueEvent= gcnew ConcurrentQueue<Event<T>^>();
	};
	virtual void Subscribe(IObservable<Event<T>^> ^provider){
		if (provider != nullptr) 
			unsubscriber = provider->Subscribe(this);	
	};
	Event<T> ^getEvent(){
		Event<T> ^result ;
		if(!queueEvent->IsEmpty){

			queueEvent->TryDequeue(result);

		}
		return result;

	};
	virtual void OnCompleted(){
		Console::WriteLine("The Location Tracker has completed transmitting data to");
		Unsubscribe();

	};
	virtual void OnError(Exception ^e){
		Console::WriteLine("The Location Tracker has Error");
		Unsubscribe();
		
	};
	virtual void OnNext(Event<T> ^value){

#ifdef DEBUG_MSG
		Console::WriteLine("Evento: {0}",value->ToString());
#endif //DEBUG_MSG
		queueEvent->Enqueue(value);
	};
	virtual void Unsubscribe(){
		delete unsubscriber;
	};
};

