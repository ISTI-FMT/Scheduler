#include "ManagerLineaIXL.h"


ManagerLineaIXL::ManagerLineaIXL(void)
{
	tabella = gcnew Dictionary<int, LineaIXL^>;
}

// questa funzione controlla se il CDB identificato da idCdb esiste già 
// nella tabella: se non esiste, la funzione lo aggiunge e restituisce true,
// altrimenti restituisce false
bool ManagerLineaIXL::addCDB(int idCdb, int statoCDB, int statoDeviatoio)
{
	if(tabella->ContainsKey(idCdb))
		return false;
	LineaIXL ^linea = gcnew LineaIXL(idCdb, statoCDB, statoDeviatoio);
	tabella->Add(idCdb, linea);
	return true;
}

// questa funzione setta lo stato del CDB identificato da idCdb a statoCDB.
// Se lo stato del CDB era già statoCDB, la funzione restituisce false, altrimenti restituisce true
bool ManagerLineaIXL::checkAndSetCDB(int idCdb, int statoCDB)
{
	if(tabella[idCdb]->getStatoCdb() == statoCDB)
		return false;
	tabella[idCdb]->setStatoCdb(statoCDB);
	return true;
}

// questa funzione setta lo stato del deviaotoio del CDB identificato da idCdb a statoDeviatoio.
// Se lo stato del deviatoio era già statoDeviatoio, la funzione restituisce false, altrimenti restituisce true
bool ManagerLineaIXL::checkAndSetDeviatoio(int idCdb, int statoDeviatoio)
{
	if(tabella[idCdb]->getStatoDeviatoio() == statoDeviatoio)
		return false;
	tabella[idCdb]->setStatoCdb(statoDeviatoio);
	return true;
}
