#include "Fault.h"


Fault::Fault(void)
{
	NID_COMPONENT=0;
	M_FAULT=0;
}

System::String ^Fault::ToString(){
		System::String ^out;

	
	out = out+"NID_COMPONENT: "+NID_COMPONENT+";";
	out = out+"M_FAULT: "+M_FAULT+";";

	 return out;
}