#pragma once
ref class stateCDB
{
	unsigned int NID_CDB ;
	unsigned int Q_STATOCDB ;
	unsigned int Q_DEVIATOIO ;
public:
	stateCDB(void);
	stateCDB(int nid, int state, int dev);
	void setNID_CDB(int NID){NID_CDB=NID;};
	int getNID_CDB(){return NID_CDB;};
	void setQ_DEVIATOIO(int Q){Q_DEVIATOIO=Q;};
	int getQ_DEVIATOIO(){return Q_DEVIATOIO;};
	void setQ_STATOCDB(int Q){Q_STATOCDB=Q;};
	int getQ_STATOCDB(){return Q_STATOCDB;};
	int Size(){return 32+2+2;}
	virtual System::String ^ToString() override;
};

