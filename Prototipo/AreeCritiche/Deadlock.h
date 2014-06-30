#pragma once
#using <System.dll>

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

ref class Deadlock
{
public:
	Deadlock(void);
	Dictionary<int,int>^ Posizioni;
};

