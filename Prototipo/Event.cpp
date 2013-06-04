#include "Event.h"


Event::Event(void)
{
	sCDB=nullptr;
	sITI=nullptr;
	lTrain=nullptr;
	source="";
}



System::String ^Event::ToString() {
	System::String ^out="";
	out += " Source: "+source+" ";
	if(sCDB){
		out += sCDB->ToString();
	}
	if(sITI){
		out+= sITI->ToString();
	}
	if(lTrain){
		out+= lTrain->ToString();
	}
	return out;
}