#include "StateCDB.h"


StateCDB::StateCDB(void)
{
	setNID_CDB( 0);
	setNID_OPERATIONAL(0);
	setNID_ENGINE(0);
	setQ_STATOCDB( QStateCDB::cdbOccupato);
	setQ_DEVIATOIO( QStateDeviatoio::deviatoioStatoIgnoto);
}
StateCDB::StateCDB(int nid, QStateCDB state, QStateDeviatoio dev)
{
	setNID_CDB( nid);
	setQ_STATOCDB( state);
	setQ_DEVIATOIO(dev);
	setNID_OPERATIONAL(0);
	setNID_ENGINE(0);
}

StateCDB::StateCDB(int nid, QStateCDB state, QStateDeviatoio dev, int idtrain)
{
	setNID_CDB( nid);
	setQ_STATOCDB( state);
	setQ_DEVIATOIO(dev);
	setNID_OPERATIONAL(idtrain);
	setNID_ENGINE(0);
}

StateCDB::StateCDB(int nid, int state, int dev, int idtrain, int idftrain)
{
	setNID_CDB( nid);
	Q_STATOCDB = state;
	Q_DEVIATOIO =  dev;
	setNID_OPERATIONAL(idtrain);
	setNID_ENGINE(idftrain);
}

StateCDB::StateCDB(int nid, int state, int dev)
{
	setNID_CDB( nid);
	Q_STATOCDB = state;
	Q_DEVIATOIO =  dev;
	setNID_OPERATIONAL(0);
	setNID_ENGINE(0);
}

StateCDB::StateCDB(int nid, QStateCDB state, QStateDeviatoio dev, int idltrain, int idftrain)
{
	setNID_CDB( nid);
	setQ_STATOCDB( state);
	setQ_DEVIATOIO(dev);
	setNID_OPERATIONAL(idltrain);
	setNID_ENGINE(idftrain);
}

System::String ^StateCDB::ToString() {
	System::String ^out;
	out = out+"NID_CDB: "+getNID_CDB()+";";
	out = out+"Q_STATOCDB: "+getQ_STATOCDB()+";";
	out = out+"Q_DEVIATIOIO: "+getQ_DEVIATOIO()+";";
	if(NID_OPERATIONAL>0){
		out = out+"NID_OPERATIONAL: "+getNID_OPERATIONAL()+";";
	}
	if(NID_ENGINE>0){
		out = out+"NID_ENGINE: "+getNID_ENGINE()+";";
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