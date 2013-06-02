#pragma once
ref class stateBlocco
{
	unsigned int NID_BLOCCO ;
	unsigned int Q_STATOBLOCCO;
public:
	stateBlocco(void);
	stateBlocco(int N, int Q){NID_BLOCCO=N;Q_STATOBLOCCO=Q;};
	int Size(){return 34;}
	void setNID_BLOCCO(int N){NID_BLOCCO=N;};
	int getNID_BLOCCO(){return NID_BLOCCO;};
	void setQ_STATOBLOCCO( int Q){Q_STATOBLOCCO=Q;};
	int getQ_STATOBLOCCO(){return Q_STATOBLOCCO;};
	virtual System::String ^ToString() override;
};

