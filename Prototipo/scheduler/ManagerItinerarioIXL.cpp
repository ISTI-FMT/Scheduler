#include "ManagerItinerarioIXL.h"

ManagerItinerarioIXL::ManagerItinerarioIXL(void)
{
	tabella = gcnew Dictionary<int, stateItinerario^>;
}

void ManagerItinerarioIXL::addItinerario(List<stateItinerario^> ^listaItin)
{
	for each (stateItinerario ^itin in listaItin)
	{
		if(!tabella->ContainsKey(itin->getNID_ITIN()))
		{
			tabella->Add(itin->getNID_ITIN(), itin);
			// segnala l'evento!!!
		}
		else 
		{
			bool mod = tabella[itin->getNID_ITIN()]->Update(itin);
			if(mod)
			{

				// segnala evento!!!
			}
			
		}
	}
}