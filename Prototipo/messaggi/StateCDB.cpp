#include "StateCDB.h"


StateCDB::StateCDB(void)
{
	NID_CDB = 0;
	NID_OPERATIONAL=0;
	Q_STATOCDB = typeStateCDB::cdbStatoIgnoto;
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

bool StateCDB::Update(StateCDB ^newcdb){
	bool ret=false;
	if(newcdb->getNID_CDB()==NID_CDB){
		if(newcdb->getQ_STATOCDB()!=Q_STATOCDB){
			Q_STATOCDB=newcdb->getQ_STATOCDB();
			ret=true;
		}
		if(newcdb->getQ_DEVIATOIO()!=Q_DEVIATOIO){
			Q_DEVIATOIO=newcdb->getQ_DEVIATOIO();
			ret=true;
		}


	}
	return ret;
}