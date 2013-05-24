#include "itinerarioUscita.h"

itinerarioUscita::itinerarioUscita(void)
{
	id = 0;
	name=gcnew String("");
	direzione = gcnew String("");
	porteBanchina = false;
	latoBanchina = gcnew String ("");
	nextCDB = gcnew String ("");
	prevCDB = gcnew String ("");
}
