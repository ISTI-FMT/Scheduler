#include "StateCDB.h"


StateCDB::StateCDB(void)
{
	NID_CDB = 0;
	NID_OPERATIONAL=0;
	NID_ENGINE=0;
	Q_STATOCDB = QStateCDB::cdbOccupato;
	Q_DEVIATOIO = QStateDeviatoio::deviatoioStatoIgnoto;
}
StateCDB::StateCDB(int nid, int state, int dev)
{
	NID_CDB = nid;
	Q_STATOCDB = state;
	Q_DEVIATOIO =  dev;
	NID_OPERATIONAL=0;
	NID_ENGINE=0;
}

StateCDB::StateCDB(int nid, int state, int dev, int idtrain)
{
	NID_CDB = nid;
	Q_STATOCDB = state;
	Q_DEVIATOIO =  dev;
	NID_OPERATIONAL=idtrain;
	NID_ENGINE=0;
}

StateCDB::StateCDB(int nid, int state, int dev, int idltrain, int idftrain)
{
	NID_CDB = nid;
	Q_STATOCDB = state;
	Q_DEVIATOIO =  dev;
	NID_OPERATIONAL=idltrain;
	NID_ENGINE = idftrain;
}

System::String ^StateCDB::ToString() {
	System::String ^out;
	out = out+"NID_CDB: "+NID_CDB+";";
	out = out+"Q_STATOCDB: "+Q_STATOCDB+";";
	out = out+"Q_DEVIATIOIO: "+Q_DEVIATOIO+";";
	if(NID_OPERATIONAL>0){
		out = out+"NID_OPERATIONAL: "+NID_OPERATIONAL+";";
	}
	if(NID_ENGINE>0){
		out = out+"NID_ENGINE: "+NID_ENGINE+";";
	}

	return out;
}

bool StateCDB::Equals( Object^ obj ) {
	StateCDB ^o2 = safe_cast<StateCDB^>(obj);
	if(o2->getNID_CDB()==NID_CDB)
	{
		return true;
	}
	return false;
}