#pragma once
#include "stazione.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class tabellaItinerari
{

	Dictionary<int,stazione^ > ^mapidstazioneitinerari;
	String ^schemaxsd;
public:
	tabellaItinerari(void);

	void leggifileconfigurazioneItinerari(String ^nomefile);
	
	
	virtual System::String^ ToString() override;
	

	
	

	Dictionary<int,stazione^ > ^getMap(){return mapidstazioneitinerari;};
};

