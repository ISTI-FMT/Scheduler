#include "LineaIXL.h"

LineaIXL::LineaIXL(int idCdb)
{
	id = idCdb;
	statoCDB = cdbStatoIgnoto;
	statoDeviatoio = deviatoioStatoIgnoto;
}

LineaIXL::LineaIXL(void)
{
	id = 0;
	statoCDB = cdbStatoIgnoto;
	statoDeviatoio = deviatoioStatoIgnoto;
}

LineaIXL::LineaIXL(int idCdb, int statoCdb, int statoDeviatoio)
{
	id = idCdb;
	statoCDB = statoCdb;
	statoDeviatoio = statoDeviatoio;
}
