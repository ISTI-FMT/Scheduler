#include "Fault.h"

Fault::Fault(void)
{
	setNID_COMPONENT(0);
	setM_FAULT(0);
}

System::String ^Fault::ToString(){
	System::String ^out;

	out = out+"NID_COMPONENT: "+getNID_COMPONENT()+";";
	out = out+"M_FAULT: "+getM_FAULT()+";";

	return out;
}