#include "ManagerItinerarioIXL.h"

ManagerItinerarioIXL::ManagerItinerarioIXL(void)
{
	tabella = gcnew Dictionary<int, ItinerarioIXL^>;
}

// questa funzione controlla se l'itinerario identificato da idItin esiste già 
// nella tabella: se non esiste, la funzione lo aggiunge e restituisce true,
// altrimenti restituisce false
bool ManagerItinerarioIXL::addItinerario(int idItin, int statoItin)
{
	if(tabella->ContainsKey(idItin))
		return false;
	ItinerarioIXL ^itinerario = gcnew ItinerarioIXL(idItin, statoItin);
	tabella->Add(idItin, itinerario);
	return true;
}

// questa funzione setta lo stato del'itinerario identificato da idItin a statoItin.
// Se lo stato dell'itinerario era già statoItin, la funzione restituisce false, altrimenti restituisce true
bool ManagerItinerarioIXL::checkAndSetItinerario(int idItin, int statoItin)
{
	if(tabella[idItin]->getStatoItinerario() == statoItin)
		return false;
	tabella[idItin]->setStatoItinerario(statoItin);
	return true;
}