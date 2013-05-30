#include "ManagerItinerarioIXL.h"

ManagerItinerarioIXL::ManagerItinerarioIXL(void)
{
	tabella = gcnew Dictionary<int, ItinerarioIXL^>;
}

void ManagerItinerarioIXL::addItinerario(List<ItinerarioIXL^> ^listaItin)
{
	for each (ItinerarioIXL ^itin in listaItin)
	{
		if(!tabella->ContainsKey(itin->getId()))
		{
			tabella->Add(itin->getId(), itin);
			// segnala l'evento!!!
		}
		else 
		{
			if(tabella[itin->getId()]->getStatoItinerario() != itin->getStatoItinerario())
			{
				tabella[itin->getId()]->setStatoItinerario(itin->getStatoItinerario());
				// segnala evento!!!
			}
		}
	}
}