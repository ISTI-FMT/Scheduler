#include "ItinerarioIXL.h"


ItinerarioIXL::ItinerarioIXL(void)
{
	id = 0;
	statoItinerario = itinerarioStatoIgnoto;
}

ItinerarioIXL::ItinerarioIXL(int idItinerario)
{
	id = idItinerario;
	statoItinerario = itinerarioStatoIgnoto;
}

ItinerarioIXL::ItinerarioIXL(int idItinerario, int stato)
{
	id = idItinerario;
	statoItinerario = stato;
}