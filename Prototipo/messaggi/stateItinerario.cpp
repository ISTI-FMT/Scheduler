#include "stateItinerario.h"


stateItinerario::stateItinerario(void)
{
	NID_ITIN = 0;
	Q_STATOITIN = 0;
}

System::String ^ stateItinerario::ToString(){
	System::String ^out;
	out = out+"NID_ITIN: "+NID_ITIN+";";
	out = out+"Q_STATOITIN: "+Q_STATOITIN+";";

	return out;
};