#pragma once
#include "messaggi\\StateCDB.h"
#include "messaggi\\StateItinerario.h"
#include "phisicalTrain.h"

using namespace System;

ref class Event
{	 
	StateCDB ^sCDB;
	StateItinerario ^sITI;
	phisicalTrain ^lTrain;
	String ^source;
public:
	Event(void);
	Event(StateCDB ^v,String ^s){sCDB=v;sITI=nullptr;source=s;lTrain=nullptr;};
	Event(StateItinerario ^vv,String ^s){sITI=vv;sCDB=nullptr;source=s;lTrain=nullptr;};
	Event(phisicalTrain ^vv,String ^s){sITI=nullptr;sCDB=nullptr;source=s;lTrain=vv;};
	void setEvent(StateCDB ^v){sCDB=v;}
	void setEvent(StateItinerario ^vv){sITI=vv;};
	void setEvent(phisicalTrain ^vv){lTrain=vv;};

	StateItinerario ^getEventStateItinerario();
	StateCDB ^getEventStateCDB();
	phisicalTrain ^getEventPresentTrain();

	void setSource(String ^v){source=v;}
	String ^getSource(){return source;}


	virtual System::String ^ToString() override;

};

