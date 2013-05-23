#include "Fermata.h"

using namespace System;
using namespace System::Globalization;
Fermata::Fermata(void)
{
	idStazione = "";
	orarioArrivo = 0;
	orarioPartenza = 0;
	tempoMinimoAperturaPorte = 0;
	binarioProgrammato = 0;
	latoAperturaPorte = noApertura;
}

 System::String^ Fermata::ToString() {
	 String ^out;
	
	
	 TimeSpan Arrivo = TimeSpan::FromSeconds(orarioArrivo*30);
	 TimeSpan Partenza = TimeSpan::FromSeconds(orarioPartenza*30);

	 out+="ID stazione : "+idStazione+"\n\r";
	 out+=" orario arrivo : "+ Arrivo.ToString()+"\n\r";
	 out+=" orario partenza : "+Partenza.ToString()+"\n\r";
	 out+=" binario programmato : "+binarioProgrammato+"\n\r";
	  out+=" tempoMinimoAperturaPorte : "+tempoMinimoAperturaPorte+"\n\r";
	   out+=" latoAperturaPorte : "+latoAperturaPorte+"\n\r";

	 return out;
 }

/*
ostream& operator<<(ostream &out, const Fermata &stop)
{
	out << "ID stazione : " << stop.idStazione.c_str() << endl;
	out << "orario arrivo : " << stop.orarioArrivo.tm_hour << ":" << stop.orarioArrivo.tm_min << ":" << stop.orarioArrivo.tm_sec << endl;
	out << "orario partenza : " << stop.orarioPartenza.tm_hour << ":" << stop.orarioPartenza.tm_min << ":" << stop.orarioPartenza.tm_sec << endl;
	out << "binario programmato : " << stop.binarioProgrammato << endl;
	string lato;
	if(stop.latoAperturaPorte == aperturaTrenoDx)
		lato = "destra";
	else if(stop.latoAperturaPorte == aperturaTrenoSx)
		lato = "sinistra";
	else if(stop.latoAperturaPorte == aperturaTrenoDxSx)
		lato = "destra/sinistra";
	else
		lato = "no apertura";
	out << "lato apertura porte : " << lato.c_str() << endl;

	return out;
}
*/

