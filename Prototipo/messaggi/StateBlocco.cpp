#include "StateBlocco.h"


StateBlocco::StateBlocco(void)
{
	setNID_BLOCCO(0);
	setQ_STATOBLOCCO(QStatoBlocco::legale);
}


System::String ^StateBlocco::ToString(){
		System::String ^out;

	out = out+"NID_BLOCCO: "+getNID_BLOCCO()+";";
	out = out+"Q_STATOBLOCCO: "+getQ_STATOBLOCCO()+";";
	
	 return out;
}
