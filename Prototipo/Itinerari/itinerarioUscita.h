#pragma once
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class itinerarioUscita
{
	int ^id;
	String ^name;
	String ^direzione;
	bool porteBanchina;
	String ^latoBanchina;
	String ^nextCDB;
	String ^prevCDB;
public:
	itinerarioUscita(void);
	void setId(int ^i){id = i;}
	int^ getId(){return id;}
	void setName(String ^i){name = i;}
	String^ getName(){return name;}
	void setDirezione(String ^d){direzione = d;}
	String^ getDirezione(){return direzione;}
	void setPorteBanchina(bool p){porteBanchina = p;}
	bool getPorteBanchina(){return porteBanchina;}
	void setLatoBanchina(String ^l){latoBanchina = l;}
	String^ getLatoBanchina(){return latoBanchina;}
	void setNextCDB(String ^p){nextCDB = p;}
	String^ getNextCDB(){return nextCDB;}
	void setPrevCDB(String ^p){prevCDB = p;}
	String^ getPrevCDB(){return prevCDB;}
};

