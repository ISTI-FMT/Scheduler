#include "StateSegnale.h"


StateSegnale::StateSegnale(void)
{
	NID_SEGN  =0;
	 Q_STATOSEGN =0 ;
}

System::String ^StateSegnale::ToString(){
	System::String ^out;


	out = out+"NID_SEGN: "+NID_SEGN+";";
	out = out+"Q_STATOSEGN: "+Q_STATOSEGN+";";

	return out;
}