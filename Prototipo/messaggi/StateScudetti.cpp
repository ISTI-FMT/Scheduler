#include "StateScudetti.h"


StateScudetti::StateScudetti(void)
{
	 NID_SCUD =0;
	 Q_STATOSCUD = 0;
}

System::String ^StateScudetti::ToString(){
	System::String ^out;


	out = out+"NID_SCUD: "+NID_SCUD+";";
	out = out+"Q_STATOSCUD: "+Q_STATOSCUD+";";

	return out;
}
