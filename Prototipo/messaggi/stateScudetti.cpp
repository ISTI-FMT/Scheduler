#include "stateScudetti.h"


stateScudetti::stateScudetti(void)
{
}

System::String ^stateScudetti::ToString(){
	System::String ^out;


	out = out+"NID_SCUD: "+NID_SCUD+";";
	out = out+"Q_STATOSCUD: "+Q_STATOSCUD+";";

	return out;
}
