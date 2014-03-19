#include "Fermata.h"

using namespace System;
using namespace System::Globalization;
Fermata::Fermata(void)
{
	idStazione = 0;
	nameStazione = "";
	orarioArrivo = 0;
	orarioPartenza = 0;
	tempoMinimoAperturaPorte = 0;
	binarioProgrammato = 0;
	latoAperturaPorte = FermataType::noApertura;
	iditinerarioentrata=0;
	nameitinerarioentrata="";
	iditinerariouscita=0;
	nameitinerariouscita="";
}
bool Fermata::isPassante(){
	bool result=false;
	if(orarioArrivo-orarioPartenza==0){
		return true;
	}
	return result;
}


System::String^ Fermata::ToString() {
	String ^out;


	TimeSpan Arrivo = TimeSpan::FromSeconds(orarioArrivo*30);
	TimeSpan Partenza = TimeSpan::FromSeconds(orarioPartenza*30);

	int lato = (int) latoAperturaPorte;
	out+="ID stazione : "+idStazione+"\n\r";
	out+=" Nome stazione : "+nameStazione+"\n\r";
	out+=" orario arrivo : "+ Arrivo.ToString()+"\n\r";
	out+=" orario partenza : "+Partenza.ToString()+"\n\r";
	out+=" binario programmato : "+binarioProgrammato+"\n\r";
	out+=" tempoMinimoAperturaPorte : "+tempoMinimoAperturaPorte+"\n\r";
	out+=" latoAperturaPorte : "+ lato +"\n\r";
	out+=" iditinerarioentrata : "+iditinerarioentrata+"\n\r";
	out+=" nameitinerarioentrata : "+nameitinerarioentrata+"\n\r";
	out+=" iditinerariouscita : "+iditinerariouscita+"\n\r";
	out+=" nameitinerariouscita : "+nameitinerariouscita+"\n\r";

	return out;
}



void Fermata::setOrarioArrivo(DateTime arr){
	DateTime orarioSupporto3 = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);

	TimeSpan sinceMidnighta = arr - orarioSupporto3;

	double	darrivo = sinceMidnighta.TotalSeconds/30;

	setOrarioArrivo(darrivo);

}
void Fermata::setOrarioPartenza(DateTime orario){
	DateTime orarioSupporto3 = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);

	TimeSpan sinceMidnighta = orario - orarioSupporto3;

	double	dpart= sinceMidnighta.TotalSeconds/30;

	setOrarioPartenza(dpart);
}


bool Fermata::Equals(Fermata^ otherKey){
	if(idStazione==otherKey->getIdStazione()){

		return true;
	}else{
		return false;
	}
}