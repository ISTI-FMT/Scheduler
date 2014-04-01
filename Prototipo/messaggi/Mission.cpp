#include "Mission.h"

Mission::Mission(void)
{
	setT_START_TIME(0);
	setD_LRGB(0);
	setNID_LRGB(0);
	setD_STOP (0);
	setQ_DOORS ( FermataType::noApertura);
	setT_DOORS_TIME ( 0);
}

System::String ^ Mission::ToString(){


	System::String ^out;


	out = out+"T_START_TIME: "+getT_START_TIME()+";";
	out = out+"NID_LRGB: "+getNID_LRGB()+";";
	out = out+"D_LRGB: "+getD_LRGB()+";";
	out = out+"D_STOP: "+getD_STOP()+";";
	out = out+"Q_DOORS: "+getQ_DOORS()+";";
	out = out+"T_DOORS_TIME: "+getT_DOORS_TIME()+";";


	return out;
};