#include "ManagerCDBIXL.h"

ManagerCDBIXL::ManagerCDBIXL(void)
{
	tabella = gcnew Dictionary<int, stateCDB^>;
}

void ManagerCDBIXL::addCheckAndSetCDB(List<stateCDB^> ^listaCDB)
{
	for each (stateCDB ^cdb in listaCDB)
	{
		if(!tabella->ContainsKey(cdb->getNID_CDB()))
		{
			tabella->Add(cdb->getNID_CDB(), cdb);
			// segnala l'evento!!!
		}
		else 
		{
			bool mod = tabella[cdb->getNID_CDB()]->Update(cdb);
			if(mod)
			{

				// segnala evento!!!
			}

		}
	}
}