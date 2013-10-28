#pragma once
enum  typeStateCDB { cdbOccupato = 1, cdbImpegnato = 2, cdbLibero = 0,  cdbFuoriControllo = 3};
enum  typeStateDeviatoio{deviatoioStatoIgnoto = 4, deviatoioNonPresente = 0, deviatoioNormale = 1, deviatoioRovescio = 2};

/*Utilizzo questa classe per serializzare le informazioni dello stato del CDB del pacchetto stato linea da ricevere all'ATC o IXL*/


//questa classe rappresenta lo stato di un CDB

ref class StateCDB
{
	unsigned int NID_CDB ;
	unsigned int Q_STATOCDB ;
	unsigned int Q_DEVIATOIO ;
	unsigned int NID_OPERATIONAL ;
	unsigned int NID_ENGINE ;
public:
	StateCDB(void);
	StateCDB(int nid, int state, int dev);
	StateCDB(int nid, int state,  int dev, int idtrain);
	StateCDB(int nid, int state, int dev, int idltrain, int idftrain);
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
			if(newcdb->getNID_OPERATIONAL()!=NID_OPERATIONAL){
				NID_OPERATIONAL=newcdb->getNID_OPERATIONAL();
				ret=true;
			}
			if(newcdb->getNID_ENGINE()!=NID_ENGINE){
				NID_ENGINE=newcdb->getNID_ENGINE();
				ret=true;
			}


		}
		return ret;
	};

	void setNID_OPERATIONAL(int NID){NID_OPERATIONAL=NID;};
	int getNID_OPERATIONAL(){return NID_OPERATIONAL;};

	void setNID_ENGINE(int NID){NID_ENGINE=NID;};
	int getNID_ENGINE(){return NID_ENGINE;};


	//int Size(){return 32+2+2;}

	StateCDB ^Clone(){return gcnew StateCDB(NID_CDB,Q_STATOCDB,Q_DEVIATOIO,NID_OPERATIONAL,NID_ENGINE);}

	virtual System::String ^ToString() override;

	virtual bool Equals( Object^ obj ) override;
};

