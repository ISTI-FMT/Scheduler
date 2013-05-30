#include "CDBIXL.h"

CDBIXL::CDBIXL(int idCdb)
{
	id = idCdb;
	statoCDB = cdbStatoIgnoto;
	statoDeviatoio = deviatoioStatoIgnoto;
}

CDBIXL::CDBIXL(void)
{
	id = 0;
	statoCDB = cdbStatoIgnoto;
	statoDeviatoio = deviatoioStatoIgnoto;
}

CDBIXL::CDBIXL(int idCdb, int statoCdb, int statoDeviatoio)
{
	id = idCdb;
	statoCDB = statoCdb;
	statoDeviatoio = statoDeviatoio;
}
