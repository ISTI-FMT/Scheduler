#pragma once
#include "stazione.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class tabellaItinerari
{
	List<stazione^> ^tabella;
public:
	tabellaItinerari(void);
};

