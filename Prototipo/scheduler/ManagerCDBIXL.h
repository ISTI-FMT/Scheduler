#pragma once
#using <System.dll>
#include "..\\messaggi\\stateCDB.h"
using namespace System;
using namespace System::Collections::Generic;

ref class ManagerCDBIXL
{
	Dictionary<int, stateCDB^> ^tabella;
public:
	ManagerCDBIXL(void);
	void addCheckAndSetCDB(List<stateCDB^> ^listaCDB);
};

