#include "ProfiloVelocita.h"


ProfiloVelocita::ProfiloVelocita(void)
{
	D_MISSION =0;
	V_MISSION=0;
}

System::String ^ ProfiloVelocita::ToString(){

	System::String ^out;
	out = out+"D_MISSION: "+D_MISSION+";";
	out = out+"V_MISSION: "+V_MISSION+";";


	return out;
};