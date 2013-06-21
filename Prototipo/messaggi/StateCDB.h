#pragma once
enum  typeStateCDB { cdbOccupato = 1, cdbImpegnato = 2, cdbLibero = 0,  cdbFuoriControllo = 3};
enum  typeStateDeviatoio{deviatoioStatoIgnoto = 4, deviatoioNonPresente = 0, deviatoioNormale = 1, deviatoioRovescio = 2};
ref class StateCDB
{
	unsigned int NID_CDB ;
	unsigned int Q_STATOCDB ;
	unsigned int Q_DEVIATOIO ;
	unsigned int NID_OPERATIONAL ;
public:
	StateCDB(void);
	StateCDB(int nid, int state, int dev);
	StateCDB(int nid, int state,  int dev, int idtrain);
	void setNID_CDB(int NID){NID_CDB=NID;};
	int getNID_CDB(){return NID_CDB;};
	void setQ_DEVIATOIO(int Q){
		if((Q>=0) & (Q<3)){
			Q_DEVIATOIO=Q;
		}else{
			Q_DEVIATOIO=typeStateDeviatoio::deviatoioStatoIgnoto;
		}

	};
	int getQ_DEVIATOIO(){return Q_DEVIATOIO;};
	void setQ_STATOCDB(int Q){
		if((Q>=0)& (Q<4)){
			Q_STATOCDB=Q;
		}else{
			Q_STATOCDB=typeStateCDB::cdbFuoriControllo;
		}
	};
	int getQ_STATOCDB(){return Q_STATOCDB;};
	bool Update(StateCDB ^newcdb){
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

	void setNID_OPERATIONAL(int NID){NID_OPERATIONAL=NID;};
	int getNID_OPERATIONAL(){return NID_OPERATIONAL;};


	int Size(){return 32+2+2;}

	StateCDB ^Clone(){return gcnew StateCDB(NID_CDB,Q_STATOCDB,Q_DEVIATOIO,NID_OPERATIONAL);}

	virtual System::String ^ToString() override;

	virtual bool Equals( Object^ obj ) override;
};

