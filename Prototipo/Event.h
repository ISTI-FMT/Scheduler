#pragma once
#include "messaggi\\StateCDB.h"
#include "messaggi\\StateItinerario.h"
ref class Event
{	 
	StateCDB ^sCDB;
	StateItinerario ^sITI;
public:
	Event(void);
	Event(StateCDB ^v){sCDB=v;sITI=nullptr;}
	Event(StateItinerario ^vv){sITI=vv;sCDB=nullptr;};
	void setEvent(StateCDB ^v){sCDB=v;}
	void setEvent(StateItinerario ^vv){sITI=vv;};
	StateItinerario ^getEvent(StateItinerario ^vv){return sITI;};
	StateCDB ^getEvent(StateCDB ^vv){return sCDB;};
	

	virtual System::String ^ToString() override;

};

