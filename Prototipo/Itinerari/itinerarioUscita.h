#pragma once
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class itinerarioUscita
{
	String ^id;
	String ^direzione;
	bool porteBanchina;
	String ^latoBanchina;
	String ^nextCDB;
public:
	itinerarioUscita(void);
	void setId(String ^i){id = i;}
	String^ getId(){return id;}
	void setDirezione(String ^d){direzione = d;}
	String^ getDirezione(){return direzione;}
	void setPorteBanchina(bool p){porteBanchina = p;}
	bool getPorteBanchina(){return porteBanchina;}
	void setLatoBanchina(String ^l){latoBanchina = l;}
	String^ getLatoBanchina(){return latoBanchina;}
	void setNextCDB(String ^p){nextCDB = p;}
	String^ getNextCDB(){return nextCDB;}
};

