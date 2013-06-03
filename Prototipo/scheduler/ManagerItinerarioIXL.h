#pragma once
#include "..\\messaggi\\stateItinerario.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class ManagerItinerarioIXL
{
	Dictionary<int, stateItinerario^> ^tabella;
public:
	ManagerItinerarioIXL(void);
	void addItinerario(List<stateItinerario^> ^listaItin);
};