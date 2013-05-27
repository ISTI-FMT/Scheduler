#pragma once
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;
//da eliminare
ref class itinerarioIngresso
{

	int ^id;
	String ^name;
	String ^direzione;
	int lrgb;
	int dStop;
	bool porteBanchina;
	String ^latoBanchina;
	String ^prevCDB;
public:
	itinerarioIngresso(void);
	void setId(int ^i){id = i;}
	int^ getId(){return id;}
	void setName(String ^i){name = i;}
	String^ getName(){return name;}
	void setDirezione(String ^d){direzione = d;}
	String^ getDirezione(){return direzione;}
	void setLrgb(int l){lrgb = l;}
	int getLrgb(){return lrgb;}
	void setDStop(int d){dStop = d;}
	int getDStop(){return dStop;}
	void setPorteBanchina(bool p){porteBanchina = p;}
	bool getPorteBanchina(){return porteBanchina;}
	void setLatoBanchina(String ^l){latoBanchina = l;}
	String^ getLatoBanchina(){return latoBanchina;}
	void setPrevCDB(String ^p){prevCDB = p;}
	String^ getPrevCDB(){return prevCDB;}
};

