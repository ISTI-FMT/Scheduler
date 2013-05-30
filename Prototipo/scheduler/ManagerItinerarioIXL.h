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
	void addItinerario(List<ItinerarioIXL^> ^listaItin);
};