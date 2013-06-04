#include "Event.h"


Event::Event(void)
{
	sCDB=nullptr;
	sITI=nullptr;
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

	return out;
}