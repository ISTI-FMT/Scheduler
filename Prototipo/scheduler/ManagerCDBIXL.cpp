#include "ManagerCDBIXL.h"

ManagerCDBIXL::ManagerCDBIXL(void)
{
	tabella = gcnew Dictionary<int, CDBIXL^>;
}

void ManagerCDBIXL::addCheckAndSetCDB(List<CDBIXL^> ^listaCDB)
{
	for each (CDBIXL ^cdb in listaCDB)
	{
		if(!tabella->ContainsKey(cdb->getId()))
		{
			tabella->Add(cdb->getId(), cdb);
			// segnala l'evento!!!
		}
		else 
		{
			if(tabella[cdb->getId()]->getStatoCdb() != cdb->getStatoCdb())
			{
				tabella[cdb->getId()]->setStatoCdb(cdb->getStatoCdb());
				// segnala evento!!!
			}
			if(tabella[cdb->getId()]->getStatoDeviatoio() != cdb->getStatoDeviatoio())
			{
				tabella[cdb->getId()]->setStatoDeviatoio(cdb->getStatoDeviatoio());
				// segnala evento!!!
			}
		}
	}
}