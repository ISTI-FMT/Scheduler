#pragma once
enum  typeStateCDB { cdbStatoIgnoto = -1, cdbOccupato = 0, cdbImpegnato = 1, cdbLibero = 2,  cdbFuoriControllo = 3};
enum  typeStateDeviatoio{deviatoioStatoIgnoto = -1, deviatoioNonPresente = 0, deviatoioNormale = 1, deviatoioRovescio = 2};
ref class StateCDB
{
	unsigned int NID_CDB ;
	int Q_STATOCDB ;
	int Q_DEVIATOIO ;
	int NID_OPERATIONAL ;
public:
	StateCDB(void);
	StateCDB(int nid, int state, int dev);
	void setNID_CDB(int NID){NID_CDB=NID;};
	int getNID_CDB(){return NID_CDB;};
	void setQ_DEVIATOIO(int Q){
		if((Q>-2) & (Q<3)){
			Q_DEVIATOIO=Q;
		}else{
			Q_DEVIATOIO=typeStateDeviatoio::deviatoioStatoIgnoto;
		}

	};
	int getQ_DEVIATOIO(){return Q_DEVIATOIO;};
	void setQ_STATOCDB(int Q){
		if((Q>-2)& (Q<4)){
			Q_STATOCDB=Q;
		}else{
			Q_STATOCDB=typeStateCDB::cdbStatoIgnoto;
		}
	};
	int getQ_STATOCDB(){return Q_STATOCDB;};
	bool Update(StateCDB ^newcdb);

	void setNID_OPERATIONAL(int NID){NID_OPERATIONAL=NID;};
	int getNID_OPERATIONAL(){return NID_OPERATIONAL;};


	int Size(){return 32+2+2;}

	StateCDB ^Clone(){return gcnew StateCDB(NID_CDB,Q_STATOCDB,Q_DEVIATOIO);}

	virtual System::String ^ToString() override;
};

