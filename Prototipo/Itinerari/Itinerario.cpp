#include "Itinerario.h"
using namespace System;
using namespace System::Collections::Generic;

Itinerario::Itinerario(typeItini t)
{
	id = 0;
	tipoitin=t;
	name=gcnew String("");
	direzione = gcnew String("");
	infolrbg = gcnew lrbg();
	
	porteBanchina = false;
	latoBanchina = gcnew String ("");
	prevCDB = 0;
	nextCDB = 0;
	cdb=gcnew List<int>();
	nextstation=0;
}

System::String^ Itinerario::ToString(){
	String ^out="";
	out+=" Id Itinenario: "+id;
	out+=" Nome Itinenario: "+name;
	out+=" info lrgb: "+infolrbg->ToString();
	out+=" Porte Banchina: "+porteBanchina;
	out+=" Lato Banchina: "+latoBanchina;
	out+=" prevCDB: "+prevCDB;
	out+=" nextCDB: "+nextCDB;
	out+=" nextstation: "+nextstation;
	out+=" CDB: ";
	for each (int var in cdb)
	{
		out+=var+"; ";
	}
	

	return out;
}


List<int>^Itinerario::CloneListCDB(){
	List<int> ^newcdblist = gcnew List<int>();
	for each (int var in cdb)
	{
		newcdblist->Add(var);
	}
	return newcdblist;

}