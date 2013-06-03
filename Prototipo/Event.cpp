#include "Event.h"


Event::Event(void)
{
	sCDB=nullptr;
	sITI=nullptr;
}



System::String ^Event::ToString() {
	if(sCDB){
		return sCDB->ToString();
	}
	if(sITI){
		return sITI->ToString();
	}

	return "";
}