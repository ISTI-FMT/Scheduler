#include "binario.h"

binario::binario(void)
{
	id = 0;
	direzione = gcnew String("");
	nid_lrgb = 0;
	d_stop = 0;
	porteBanchina = false;
	latoBanchina = gcnew String("");
	nextCDB = 0;
	prevCDB = 0;
	CDB = 0;
}

System::String^ binario::ToString(){
	String ^out="";
	out+=" Id Binario: "+id;
	out+=" Direzione: "+direzione;
	out+=" Id lrgb: "+nid_lrgb;
	out+=" D_stop: "+d_stop;
	out+=" Porte Banchina: "+porteBanchina;
	out+=" Lato Banchina: "+latoBanchina;
	out+=" prevCDB: "+prevCDB;
	out+=" nextCDB: "+nextCDB;
	out+=" CDB: "+CDB;
	return out;
}
