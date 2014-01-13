#pragma once
#include "..\\messaggi\\ProfiloVelocita.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

//questa classe viene usarta per leggere il file xml di configurazioni della velocità

ref class ConfigurazioneVelocita
{

	Dictionary<int,List<ProfiloVelocita^>^> ^mapidtrenologicopvel;
	String ^schemaxsd;
public:
	ConfigurazioneVelocita(void);
	

	void leggifileConfigurazioneVelocita();


	virtual System::String^ ToString() override;



	List<ProfiloVelocita^>^getProfiloVelocita(int id){
		if(mapidtrenologicopvel->ContainsKey(id)) return mapidtrenologicopvel[id];
		return nullptr;	
	};
};
