#pragma once
#include "messaggi\\StateCDB.h"
#include "messaggi\\StateItinerario.h"

using namespace System;

ref class Event
{	 
	StateCDB ^sCDB;
	StateItinerario ^sITI;
	String ^source;
public:
	Event(void);
	Event(StateCDB ^v,String ^s){sCDB=v;sITI=nullptr;source=s;}
	Event(StateItinerario ^vv,String ^s){sITI=vv;sCDB=nullptr;source=s;};
	void setEvent(StateCDB ^v){sCDB=v;}
	void setEvent(StateItinerario ^vv){sITI=vv;};
	StateItinerario ^getEvent(StateItinerario ^vv){return sITI;};
	StateCDB ^getEvent(StateCDB ^vv){return sCDB;};

	void setSource(String ^v){source=v;}
	String ^getSource(){return source;}
	

	virtual System::String ^ToString() override;

};

