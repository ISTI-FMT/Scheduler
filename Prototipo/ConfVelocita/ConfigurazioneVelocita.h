#pragma once
#include "..\\messaggi\\ProfiloVelocita.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;


ref class ConfigurazioneVelocita
{

	Dictionary<int,List<ProfiloVelocita^>^> ^mapidtrenologicopvel;
	String ^schemaxsd;
public:
	ConfigurazioneVelocita(void);
	ConfigurazioneVelocita(String ^nomefile);

	void leggifileConfigurazioneVelocita(String ^nomefile);


	virtual System::String^ ToString() override;



	List<ProfiloVelocita^>^getProfiloVelocita(int id){
		if(mapidtrenologicopvel->ContainsKey(id)) return mapidtrenologicopvel[id];
		return nullptr;	
	};
};
