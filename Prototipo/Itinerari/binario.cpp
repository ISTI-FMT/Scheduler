#include "binario.h"

binario::binario(void)
{
	namebin= gcnew String("");
	bin=0;
	direzione = gcnew String("");
	info_lrgb = gcnew lrbg();
	setD_stop( 0);
	porteBanchina = false;
	latoBanchina = 0;
	nextCDB = 0;
	prevCDB = 0;
	CDB = 0;
}

System::String^ binario::ToString(){
	String ^out="";
	out+=" Nome Binario: "+ getNameBin()+"\n";
	out+=" Binario: "+bin+"\n";
	out+=" Direzione: "+getDirezione()+"\n";
	out+=" Id lrgb: "+info_lrgb+"\n";
	out+=" D_stop: "+getD_stop()+"\n";
	out+=" Porte Banchina: "+getPorteBanchina()+"\n";
	String^ strlatobanchina ="";
	if(getLatoBanchina() == 1)
		strlatobanchina ="dx";
	else if(getLatoBanchina() ==2)
		strlatobanchina =  "sx";
	else if(getLatoBanchina() == 3)
		strlatobanchina =  "sd";

	out+=" Lato Banchina: "+strlatobanchina+"\n";
	out+=" prevCDB: "+getPrevCDB()+"\n";
	out+=" nextCDB: "+getNextCDB()+"\n";
	out+=" CDB: "+getCDB()+"\n";
	return out;
}
