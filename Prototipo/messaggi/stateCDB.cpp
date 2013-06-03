#include "stateCDB.h"


stateCDB::stateCDB(void)
{
	NID_CDB = 0;
	Q_STATOCDB = typeStateCDB::cdbStatoIgnoto;
	Q_DEVIATOIO = typeStateDeviatoio::deviatoioStatoIgnoto;
}
stateCDB::stateCDB(int nid, int state, int dev)
{
	NID_CDB = nid;
	setQ_STATOCDB(state);
	setQ_DEVIATOIO( dev);
}

System::String ^stateCDB::ToString() {
	System::String ^out;



	out = out+"NID_CDB: "+NID_CDB+";";
	out = out+"Q_STATOCDB: "+Q_STATOCDB+";";
	out = out+"Q_DEVIATIOIO: "+Q_DEVIATOIO+";";

	return out;
}