#pragma once
ref class stateCDB
{
	unsigned int NID_CDB ;
	unsigned int Q_STATOCDB ;
	unsigned int Q_DEVIATOIO ;
	enum typeStateCDB { cdbStatoIgnoto = -1, cdbOccupato = 0, cdbImpegnato = 1, cdbLibero = 2,  cdbFuoriControllo = 3};
	enum typeStateDeviatoio{deviatoioStatoIgnoto = -1, deviatoioNonPresente = 0, deviatoioNormale = 1, deviatoioRovescio = 2};
public:
	stateCDB(void);
	stateCDB(int nid, int state, int dev);
	void setNID_CDB(int NID){NID_CDB=NID;};
	int getNID_CDB(){return NID_CDB;};
	void setQ_DEVIATOIO(int Q){
		if(Q>-2 & Q<3){
			Q_DEVIATOIO=Q;
		}else{
			Q_DEVIATOIO=typeStateDeviatoio::deviatoioStatoIgnoto;
		}

	};
	int getQ_DEVIATOIO(){return Q_DEVIATOIO;};
	void setQ_STATOCDB(int Q){
		if(Q>-2 & Q<4){
			Q_STATOCDB=Q;
		}else{
			Q_STATOCDB=typeStateCDB::cdbStatoIgnoto;
		}
	};
	int getQ_STATOCDB(){return Q_STATOCDB;};
	bool Update(stateCDB ^newcdb){
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
	};
	int Size(){return 32+2+2;}
	virtual System::String ^ToString() override;
};

