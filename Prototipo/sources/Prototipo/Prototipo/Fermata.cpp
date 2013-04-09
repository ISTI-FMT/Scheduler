#include "Fermata.h"


Fermata::Fermata(void)
{
	idStazione = 0;
	orarioArrivo.tm_hour = 0;
	orarioArrivo.tm_min = 0;
	orarioArrivo.tm_sec = 0;
	orarioPartenza.tm_hour = 0;
	orarioPartenza.tm_min = 0;
	orarioPartenza.tm_sec = 0;
	binarioProgrammato = 0;
	tempoAperturaPorte = 0;
	latoAperturaPorte = noApertura;
}

Fermata::~Fermata()
{
}

