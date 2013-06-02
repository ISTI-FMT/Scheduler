#include "stateCDB.h"


stateCDB::stateCDB(void)
{
	NID_CDB = 0;
	Q_STATOCDB = 0;
	Q_DEVIATOIO = 0;
}
stateCDB::stateCDB(int nid, int state, int dev)
{
	NID_CDB = nid;
	Q_STATOCDB = state;
	Q_DEVIATOIO = dev;
}

System::String ^stateCDB::ToString() {
	System::String ^out;



	out = out+"NID_CDB: "+NID_CDB+";";
	out = out+"Q_STATOCDB: "+Q_STATOCDB+";";
	out = out+"Q_DEVIATIOIO: "+Q_DEVIATOIO+";";

	return out;
}