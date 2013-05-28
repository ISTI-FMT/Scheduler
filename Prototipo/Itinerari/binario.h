#pragma once
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

ref class binario
{
	String ^id;
	String ^direzione;
	int nid_lrgb;
	int d_stop;
	bool porteBanchina;
	String ^latoBanchina;
	int nextCDB;
	int prevCDB;
	int CDB;
public:
	binario(void);
	void setId(String ^i){id = i;};
	String^ getId(){return id;};
	void setDirezione(String ^d){direzione = d;};
	String^ getDirezione(){return direzione;};
	void setNid_lrgb(int n){nid_lrgb = n;};
	int getNid_lrgb(){return nid_lrgb;};
	void setD_stop(int d){d_stop = d;};
	int getD_stop(){return d_stop;};
	void setPorteBanchina(bool p){porteBanchina = p;};
	bool getPorteBanchina(){return porteBanchina;};
	void setLatoBanchina(String ^l){latoBanchina = l;};
	String^ getLatoBanchina(){return latoBanchina;};
	void setNextCDB(int n){nextCDB = n;};
	int getNextCDB(){return nextCDB;};
	void setPrevCDB(int p){prevCDB = p;};
	int getPrevCDB(){return prevCDB;};
	void setCDB(int c){CDB = c;};
	int getCDB(){return CDB;};
	
	virtual System::String^ ToString() override;

};

