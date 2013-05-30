#pragma once
#include "ItinerarioIXL.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class ManagerItinerarioIXL
{
	Dictionary<int, ItinerarioIXL^> ^tabella;
public:
	ManagerItinerarioIXL(void);
	// questa funzione controlla se l'itinerario identificato da idItin esiste già 
	// nella tabella: se non esiste, la funzione lo aggiunge e restituisce true,
	// altrimenti restituisce false
	bool addItinerario(int idItin, int statoItin);
	// questa funzione setta lo stato del'itinerario identificato da idItin a statoItin.
	// Se lo stato dell'itinerario era già statoItin, la funzione restituisce false, altrimenti restituisce true
	bool checkAndSetItinerario(int idItin, int statoItin);
};