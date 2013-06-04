#include "StateScudetti.h"


StateScudetti::StateScudetti(void)
{
}

System::String ^StateScudetti::ToString(){
	System::String ^out;


	out = out+"NID_SCUD: "+NID_SCUD+";";
	out = out+"Q_STATOSCUD: "+Q_STATOSCUD+";";

	return out;
}
