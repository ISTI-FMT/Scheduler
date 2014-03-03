#pragma once
#using <System.dll>
#include "lrbg.h"
using namespace System;
using namespace System::Collections::Generic;
/*utilizzo questa classe per rappresentare le informazioni delle stazioni parsate dal file xml ConfigurazioneFermate.xml*/
//questa classe rappresenta le informazioni delle stazioni che sono solo fermate || forse andrebbe chiamata stazionifermate?!!
public ref class binario
{
	String ^namebin;
	int bin;
	String ^direzione;
	lrbg ^info_lrgb;
	int d_stop;
	bool porteBanchina;
	int latoBanchina;
	int nextCDB;
	int prevCDB;
	int  CDB;
public:
	binario(void);
	void setNameBin(String ^i){namebin = i;};
	String^ getNameBin(){return namebin;};
	void setBin(int i){bin = i;};
	int getBin(){return bin;};
	void setDirezione(String ^d){direzione = d;};
	String^ getDirezione(){return direzione;};
	void set_info_lrgb(lrbg ^n){info_lrgb = n;};
	lrbg ^get_info_lrgb(){return info_lrgb;};
	void setD_stop(int d){d_stop = d;};
	int getD_stop(){return d_stop;};
	void setPorteBanchina(bool p){porteBanchina = p;};
	bool getPorteBanchina(){return porteBanchina;};
	void setLatoBanchina(int l){latoBanchina = l;};
	int getLatoBanchina(){return latoBanchina;};
	void setNextCDB(int n){nextCDB = n;};
	int getNextCDB(){return nextCDB;};
	void setPrevCDB(int p){prevCDB = p;};
	int getPrevCDB(){return prevCDB;};
	void setCDB(int c){CDB = c;};
	int getCDB(){return CDB;};
	
	virtual System::String^ ToString() override;

};

