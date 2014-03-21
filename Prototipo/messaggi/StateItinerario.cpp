#include "StateItinerario.h"


StateItinerario::StateItinerario(void)
{
	NID_ITIN = 0;
	Q_STATOITIN =(int) QStateItineraio::itinerarioStatoInAtto;
}

System::String ^ StateItinerario::ToString(){
	System::String ^out;
	out = out+"NID_ITIN: "+NID_ITIN+";";
	out = out+"Q_STATOITIN: "+Q_STATOITIN+";";

	return out;
};