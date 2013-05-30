#pragma once
#include "CDBIXL.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class ManagerCDBIXL
{
	Dictionary<int, CDBIXL^> ^tabella;
public:
	ManagerCDBIXL(void);
	void addCheckAndSetCDB(List<CDBIXL^> ^listaCDB);
};

