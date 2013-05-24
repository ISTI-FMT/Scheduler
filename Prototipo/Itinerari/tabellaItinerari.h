#pragma once
#include "stazione.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class tabellaItinerari
{

	Dictionary<int,stazione^ > ^mapidstazioneitinerari;
public:
	tabellaItinerari(void);

	void leggifileconfigurazioneItinerari(String ^nomefile);
	
	
	virtual System::String^ ToString() override;
	
	
	int convertiString2int(System::String ^StringValue);

	Dictionary<int,stazione^ > ^getMap(){return mapidstazioneitinerari;};
};

