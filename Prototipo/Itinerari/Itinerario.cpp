#include "Itinerario.h"
using namespace System;
using namespace System::Collections::Generic;

Itinerario::Itinerario(void)
{
	id = 0;
	name=gcnew String("");
	direzione = gcnew String("");
	lrgb = 0;
	dStop = 0;
	porteBanchina = false;
	latoBanchina = gcnew String ("");
	prevCDB = 0;
	nextCDB = 0;
	cdb=gcnew List<StateCDB^>();
	nextstation=0;
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
	out+=" nextstation: "+nextstation;
	out+=" CDB: ";
	for each (StateCDB ^var in cdb)
	{
		out+=var+"; ";
	}
	

	return out;
}