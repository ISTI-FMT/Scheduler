#include "Fermata.h"
#include <iostream>
using namespace std;

Fermata::Fermata(void)
{
	idStazione = "";
	orarioArrivo.tm_hour = 0;
	orarioArrivo.tm_min = 0;
	orarioArrivo.tm_sec = 0;
	orarioPartenza.tm_hour = 0;
	orarioPartenza.tm_min = 0;
	orarioPartenza.tm_sec = 0;
	binarioProgrammato = 0;
	latoAperturaPorte = noApertura;
}

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

Fermata::~Fermata()
{
}

