#pragma once
#using <System.dll>
#include "..\\messaggi\\StateCDB.h"
#include "lrbg.h"
using namespace System;
using namespace System::Collections::Generic;
/*utilizzo questa classe per rappresentare le informazioni degli itinerari parsate dal file xml ConfigurazioneItinerari.xml*/
enum typeItini  {Entrata =0, Uscita=1};
//questa classe rappresenta un itinerario
public ref class Itinerario
{
	int id;
	String ^name;
	String ^direzione;
	lrbg ^infolrbg;
	bool porteBanchina;
	String ^latoBanchina;
	int prevCDB;
	int nextCDB;
	List<int> ^cdb;
	int nextstation;
	typeItini tipoitin;
public:
	property String^ ShortName 
	{
		String^ get()
		{
			return name;
		}
	}
	
	property String^ ShortDescName 
	{
		String^ get()
		{
			String ^dir="";
			if(direzione=="sx"){
				dir="<--";
			}else{
				dir="-->";
			}
			return name+dir+id.ToString();
		}
	}
	Itinerario(typeItini t);
	void setId(int i){id = i;}
	int getId(){return id;}
	typeItini getTipoItinerario(){return tipoitin;}
	void set_nextstation(int i){nextstation = i;}
	int^ get_nextstation(){return nextstation;}
	void setName(String ^i){name = i;}
	String^ getName(){return name;}
	void setDirezione(String ^d){direzione = d;}
	String^ getDirezione(){return direzione;}
	void setLrgb(lrbg ^l){infolrbg = l;}
	lrbg^ getLrgb(){return infolrbg;}
	
	void setPorteBanchina(bool p){porteBanchina = p;}
	bool getPorteBanchina(){return porteBanchina;}
	void setLatoBanchina(String ^l){latoBanchina = l;}
	String^ getLatoBanchina(){return latoBanchina;}
	void setPrevCDB(int p){prevCDB = p;}
	int getPrevCDB(){return prevCDB;}
	void setNextCDB(int p){nextCDB = p;}
	int getNextCDB(){return nextCDB;}

	List<int>^ getLCDB(){return cdb;};
	List<int>^ CloneListCDB();
	virtual System::String^ ToString() override;
};

