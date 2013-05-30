#pragma once
#include "LineaIXL.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class ManagerLineaIXL
{
	Dictionary<int, LineaIXL^> ^tabella;
public:
	ManagerLineaIXL(void);
	// questa funzione controlla se il CDB identificato da idCdb esiste gi� 
	// nella tabella: se non esiste, la funzione lo aggiunge e restituisce true,
	// altrimenti restituisce false
	bool addCDB(int idCdb, int statoCDB, int statoDeviatoio);
	// questa funzione setta lo stato del CDB identificato da idCdb a statoCDB.
	// Se lo stato del CDB era gi� statoCDB, la funzione restituisce false, altrimenti restituisce true
	bool checkAndSetCDB(int idCdb, int statoCDB);
	// questa funzione setta lo stato del deviaotoio del CDB identificato da idCdb a statoDeviatoio.
	// Se lo stato del deviatoio era gi� statoDeviatoio, la funzione restituisce false, altrimenti restituisce true
	bool checkAndSetDeviatoio(int idCdb, int statoDeviatoio);
};

