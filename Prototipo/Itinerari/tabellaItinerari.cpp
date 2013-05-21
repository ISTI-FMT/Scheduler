#include "tabellaItinerari.h"

tabellaItinerari::tabellaItinerari(void)
{
	nomeStazione = gcnew String("");
	idStazione = 0;
	itinerariIngresso = gcnew Dictionary<itinerarioIngresso^, List<int>^>;
	itinerariUscita = gcnew Dictionary<itinerarioUscita^, List<int>^>;
}