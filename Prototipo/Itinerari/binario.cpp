#include "binario.h"

binario::binario(void)
{
	id= gcnew String("");
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
	out+=" Id Binario: "+id+"\n";
	out+=" Direzione: "+direzione+"\n";
	out+=" Id lrgb: "+nid_lrgb+"\n";
	out+=" D_stop: "+d_stop+"\n";
	out+=" Porte Banchina: "+porteBanchina+"\n";
	out+=" Lato Banchina: "+latoBanchina+"\n";
	out+=" prevCDB: "+prevCDB+"\n";
	out+=" nextCDB: "+nextCDB+"\n";
	out+=" CDB: "+CDB+"\n";
	return out;
}
