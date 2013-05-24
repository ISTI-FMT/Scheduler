#include "Itinerario.h"
using namespace System;
using namespace System::Collections::Generic;

Itinerario::Itinerario(void)
{
	id = nullptr;
	name=gcnew String("");
	direzione = gcnew String("");
	lrgb = 0;
	dStop = 0;
	porteBanchina = false;
	latoBanchina = gcnew String ("");
	prevCDB = gcnew String ("");
	nextCDB = gcnew String ("");
	cdb=gcnew List<int>();
}

System::String^ Itinerario::ToString(){
	String ^out="";
	out+=" Id Itinenario: "+id;
	out+=" Nome Itinenario: "+name;
	out+=" Id lrgb: "+lrgb;
	out+=" D_stop: "+dStop;
	out+=" Porte Banchina: "+porteBanchina;
	out+=" Lato Banchina: "+latoBanchina;
	out+=" prevCDB: "+prevCDB;
	out+=" nextCDB: "+nextCDB;
	out+=" CDB: ";
	for each (int var in cdb)
	{
		out+=var+"; ";
	}
	

	return out;
}