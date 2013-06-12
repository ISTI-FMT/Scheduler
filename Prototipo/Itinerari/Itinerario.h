#pragma once
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;
ref class Itinerario
{
	int ^id;
	String ^name;
	String ^direzione;
	int lrgb;
	int dStop;
	bool porteBanchina;
	String ^latoBanchina;
	int prevCDB;
	int nextCDB;
	List<int> ^cdb;
	int nextstation;
public:
	Itinerario(void);
	void setId(int ^i){id = i;}
	int^ getId(){return id;}
	void set_nextstation(int i){nextstation = i;}
	int^ get_nextstation(){return nextstation;}
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
	void setPrevCDB(int p){prevCDB = p;}
	int getPrevCDB(){return prevCDB;}
	void setNextCDB(int p){nextCDB = p;}
	int getNextCDB(){return nextCDB;}
	
	List<int>^ getLCDB(){return cdb;}

		virtual System::String^ ToString() override;
};

