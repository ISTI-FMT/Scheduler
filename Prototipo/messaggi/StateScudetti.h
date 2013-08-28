#pragma once

/*Utilizzo questa classe per serializzare le informazioni sullo stato degli scudetti del pacchetto stato scudetti
rivevuto dall'IXL*/


//questa classe rappresenta lo stato di uno scudetto
ref class StateScudetti
{
	unsigned int NID_SCUD ;
	unsigned int Q_STATOSCUD ;
public:
	StateScudetti(void);
	StateScudetti(int N, int Q){NID_SCUD=N;Q_STATOSCUD=Q;};
	void setNID_SCUD( int N){NID_SCUD=N;};
	int getNID_SCUD(){return NID_SCUD;};
	void setQ_STATOSCUD( int Q){Q_STATOSCUD=Q;};
	int getQ_STATOSCUD(){return Q_STATOSCUD;};
	int Size(){return 32+3;};
	virtual System::String ^ToString() override;
};

