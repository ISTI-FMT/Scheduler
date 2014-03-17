#pragma once
enum  QStateCDB { cdbOccupato = 1, cdbImpegnato = 2, cdbLibero = 0,  cdbFuoriControllo = 3};
enum  QStateDeviatoio{deviatoioStatoIgnoto = 4, deviatoioNonPresente = 0, deviatoioNormale = 1, deviatoioRovescio = 2};

/*
Rappresenta lo stato di un CDB del pacchetto stato linea da ricevere all'ATC o IXL
*/

public ref class StateCDB
{
	int NID_CDB ;
	int Q_STATOCDB ;
	int Q_DEVIATOIO ;
	int NID_OPERATIONAL ;
	int NID_ENGINE ;
public:
	StateCDB(void);
	StateCDB(int nid, QStateCDB state, QStateDeviatoio dev);
	StateCDB(int nid, QStateCDB state, QStateDeviatoio dev, int idtrain);
	StateCDB(int nid, QStateCDB state, QStateDeviatoio dev, int idltrain, int idftrain);
	void setNID_CDB(int NID){NID_CDB=NID;};
	int getNID_CDB(){return NID_CDB;};
	void setQ_DEVIATOIO(QStateDeviatoio Q){
		if((Q>=0) & (Q<3)){
			Q_DEVIATOIO=Q;
		}else{
			Q_DEVIATOIO=QStateDeviatoio::deviatoioStatoIgnoto;
		}

	};
	QStateDeviatoio getQ_DEVIATOIO(){return (QStateDeviatoio)Q_DEVIATOIO;};
	void setQ_STATOCDB(QStateCDB Q){
		if((Q>=0)& (Q<4)){
			Q_STATOCDB=Q;
		}else{
			Q_STATOCDB=QStateCDB::cdbFuoriControllo;
		}
	};
	QStateCDB getQ_STATOCDB(){return (QStateCDB)Q_STATOCDB;};
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
	
	StateCDB ^Clone(){return gcnew StateCDB(NID_CDB,(QStateCDB)Q_STATOCDB,(QStateDeviatoio)Q_DEVIATOIO,NID_OPERATIONAL,NID_ENGINE);}

	virtual System::String ^ToString() override;

	virtual bool Equals( Object^ obj ) override;
};

