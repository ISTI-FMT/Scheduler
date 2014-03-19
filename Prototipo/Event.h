#pragma once
#include "IEvent.h"
#include "Train.h"
//rappresenta l'evento scambiato nell'implementazione del pattern observer
using namespace System::Diagnostics::CodeAnalysis;


generic <typename T>
[ExcludeFromCodeCoverage]
public ref class Event : public IEvent<T>{
	T source;
	Train ^attribute;
public:
	Event(Train ^tr,T s){attribute=tr;source=s;};
	Event(T s){source=s;};
	virtual void setEvent(T t){source=t;};
	virtual T getEvent(){return source;};
	void setEventAttribute(Train^ v){attribute=v;};
	Train^ getEventAttribute(){return attribute;};
	virtual System::String ^ToString() override{
		System::String ^out="";

		out += source->ToString();


		return out;

	};
};