#include "StateBlocco.h"


StateBlocco::StateBlocco(void)
{
	NID_BLOCCO=0;
	Q_STATOBLOCCO=0;
}


System::String ^StateBlocco::ToString(){
		System::String ^out;

	
	out = out+"NID_BLOCCO: "+NID_BLOCCO+";";
	out = out+"Q_STATOBLOCCO: "+Q_STATOBLOCCO+";";
	
	 return out;
}
