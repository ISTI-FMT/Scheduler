#include "Itinerario.h"
using namespace System;
using namespace System::Collections::Generic;

Itinerario::Itinerario(typeItini t)
{
	id = 0;
	tipoitin=t;
	ShortName=gcnew String("");
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
	out+=" Id Itinenario: "+getId();
	out+=" Nome Itinenario: "+ShortName;
	out+=" info lrgb: "+infolrbg->ToString();
	out+=" Porte Banchina: "+getPorteBanchina();
	out+=" Lato Banchina: "+getLatoBanchina();
	out+=" prevCDB: "+getPrevCDB();
	out+=" nextCDB: "+getNextCDB();
	out+=" nextstation: "+get_nextstation();
	int tipoi = (int)getTipoItinerario();
	out+=" type Itin: "+tipoi.ToString();
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