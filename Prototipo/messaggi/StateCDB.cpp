#include "StateCDB.h"


StateCDB::StateCDB(void)
{
	NID_CDB = 0;
	NID_OPERATIONAL=0;
	Q_STATOCDB = typeStateCDB::cdbOccupato;
	Q_DEVIATOIO = typeStateDeviatoio::deviatoioStatoIgnoto;
}
StateCDB::StateCDB(int nid, int state, int dev)
{
	NID_CDB = nid;
	setQ_STATOCDB(state);
	setQ_DEVIATOIO( dev);
	NID_OPERATIONAL=0;
}

StateCDB::StateCDB(int nid, int state, int dev, int idtrain)
{
	NID_CDB = nid;
	setQ_STATOCDB(state);
	setQ_DEVIATOIO( dev);
	NID_OPERATIONAL=idtrain;
}

System::String ^StateCDB::ToString() {
	System::String ^out;
	out = out+"NID_CDB: "+NID_CDB+";";
	out = out+"Q_STATOCDB: "+Q_STATOCDB+";";
	out = out+"Q_DEVIATIOIO: "+Q_DEVIATOIO+";";
	if(NID_OPERATIONAL>0){
		out = out+"NID_OPERATIONAL: "+NID_OPERATIONAL+";";
	}

	return out;
}

