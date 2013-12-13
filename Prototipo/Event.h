#pragma once
#include "messaggi\\StateCDB.h"
#include "messaggi\\StateItinerario.h"
#include "physicalTrain.h"
#include "Train.h"
/*utilizzo questa classe per implementare l'evento da scambiare tra lo schedulatore e gli observer che generano i messaggi:
manager ATO, ATC e IXL*/
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Globalization;
//rappresenta l'evento scambiato nell'implementazione del pattern observer
public ref class Event
{	 
	StateCDB ^sCDB;
	StateItinerario ^sITI;
	physicalTrain ^lTrain;
	List<Fermata^> ^nuoviorari;
	Train ^train;// = gcnew Dictionary<int,KeyValuePair<DateTime, DateTime>>();
	String ^source;
public:
	Event(void);
	Event(StateCDB ^v,String ^s){sCDB=v;sITI=nullptr;source=s;lTrain=nullptr;nuoviorari=nullptr;};
	Event(StateItinerario ^vv,String ^s){sITI=vv;sCDB=nullptr;source=s;lTrain=nullptr;nuoviorari=nullptr;};
	Event(physicalTrain ^vv,String ^s){sITI=nullptr;sCDB=nullptr;source=s;lTrain=vv;nuoviorari=nullptr;};
	Event(Train ^t,List<Fermata^> ^nuovio,String ^s){train=t;nuoviorari=nuovio;sCDB=nullptr;sITI=nullptr;source=s;lTrain=nullptr;};
	void setEvent(StateCDB ^v){sCDB=v;}
	void setEvent(StateItinerario ^vv){sITI=vv;};
	void setEvent(physicalTrain ^vv){lTrain=vv;};

	StateItinerario ^getEventStateItinerario();
	StateCDB ^getEventStateCDB();
	physicalTrain ^getEventPresentTrain();
	List<Fermata^> ^getEventOrari(){return nuoviorari;};
	Train ^getTrain(){return train;};
	void setSource(String ^v){source=v;}
	String ^getSource(){return source;}


	virtual System::String ^ToString() override;

};

