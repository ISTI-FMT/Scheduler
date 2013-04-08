#include "Fermata.h"


Fermata::Fermata(void)
{
	orarioPartenza = new tm;
	orarioArrivo = new tm;
}

Fermata::~Fermata()
{
	delete orarioPartenza;
	delete orarioArrivo;
}

