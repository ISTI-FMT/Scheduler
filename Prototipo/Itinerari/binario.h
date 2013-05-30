#pragma once
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class binario
{
	String ^namebin;
	int bin;
	String ^direzione;
	int nid_lrgb;
	int d_stop;
	bool porteBanchina;
	int latoBanchina;
	int nextCDB;
	int prevCDB;
	String  ^CDB;
public:
	binario(void);
	void setNameBin(String ^i){namebin = i;};
	String^ getNameBin(){return namebin;};
	void setBin(int i){bin = i;};
	int getBin(){return bin;};
	void setDirezione(String ^d){direzione = d;};
	String^ getDirezione(){return direzione;};
	void setNid_lrgb(int n){nid_lrgb = n;};
	int getNid_lrgb(){return nid_lrgb;};
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
	void setCDB(String ^c){CDB = c;};
	String ^getCDB(){return CDB;};
	
	virtual System::String^ ToString() override;

};

