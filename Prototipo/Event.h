#pragma once
#include "messaggi\\stateCDB.h"
#include "messaggi\\stateItinerario.h"
ref class Event
{	 
	stateCDB ^sCDB;
	stateItinerario ^sITI;
public:
	Event(void);
	Event(stateCDB ^v){sCDB=v;sITI=nullptr;}
	Event(stateItinerario ^vv){sITI=vv;sCDB=nullptr;};
	void setEvent(stateCDB ^v){sCDB=v;}
	void setEvent(stateItinerario ^vv){sITI=vv;};
	stateItinerario ^getEvent(stateItinerario ^vv){return sITI;};
	stateCDB ^getEvent(stateCDB ^vv){return sCDB;};
	

	

};

