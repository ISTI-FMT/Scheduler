#include "stateSegnale.h"


stateSegnale::stateSegnale(void)
{
	NID_SEGN  =0;
	 Q_STATOSEGN =0 ;
}

System::String ^stateSegnale::ToString(){
	System::String ^out;


	out = out+"NID_SEGN: "+NID_SEGN+";";
	out = out+"Q_STATOSEGN: "+Q_STATOSEGN+";";

	return out;
}