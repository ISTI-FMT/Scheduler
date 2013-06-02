#include "Mission.h"


Mission::Mission(void)
{
	T_START_TIME = 0;
	NID_LRGB = 0;
	D_STOP = 0;
	Q_DOORS = 0;
	T_DOORS_TIME = 0;
}

System::String ^ Mission::ToString(){


	System::String ^out;


	out = out+"T_START_TIME: "+T_START_TIME+";";
	out = out+"NID_LRGB: "+NID_LRGB+";";
	out = out+"D_STOP: "+D_STOP+";";
	out = out+"Q_DOORS: "+Q_DOORS+";";
	out = out+"T_DOORS_TIME: "+T_DOORS_TIME+";";


	return out;
};