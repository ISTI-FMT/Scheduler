#include "itinerarioIngresso.h"

itinerarioIngresso::itinerarioIngresso(void)
{
	id = 0;
	name=gcnew String("");
	direzione = gcnew String("");
	lrgb = 0;
	dStop = 0;
	porteBanchina = false;
	latoBanchina = gcnew String ("");
	prevCDB = gcnew String ("");
}
