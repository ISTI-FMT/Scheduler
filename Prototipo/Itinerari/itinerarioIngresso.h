#pragma once
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class itinerarioIngresso
{
	String ^id;
	String ^direzione;
	int lrgb;
	int dStop;
	bool porteBanchina;
	String ^latoBanchina;
	String ^prevCDB;
public:
	itinerarioIngresso(void);
	void setId(String ^i){id = i;}
	String^ getId(){return id;}
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

