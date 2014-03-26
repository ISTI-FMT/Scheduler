#include "ProfiloVelocita.h"


ProfiloVelocita::ProfiloVelocita(void)
{
	setD_MISSION(0);
	setV_MISSION(0);
}

System::String ^ ProfiloVelocita::ToString(){

	System::String ^out;
	out = out+"D_MISSION: "+getD_MISSION()+";";
	out = out+"V_MISSION: "+getV_MISSION()+";";

	return out;
};