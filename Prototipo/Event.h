#pragma once
#include "messaggi\\StateCDB.h"
#include "messaggi\\StateItinerario.h"
#include "phisicalTrain.h"
/*utilizzo questa classe per implementare l'evento da scambiare tra lo schedulatore e gli observer che generano i messaggi:
manager ATO, ATC e IXL*/
using namespace System;
//rappresenta l'evento scambiato nell'implementazione del pattern observer
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

