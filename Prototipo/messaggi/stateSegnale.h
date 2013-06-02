#pragma once
ref class stateSegnale
{
	unsigned int NID_SEGN ;
	unsigned int Q_STATOSEGN ;
public:
	stateSegnale(void);
	stateSegnale(int N, int Q){NID_SEGN=N;Q_STATOSEGN=Q;};
	void setNID_SEGN( int N){NID_SEGN=N;};
	int getNID_SEGN(){return NID_SEGN;};
	void setQSTATO_SEGN( int Q){Q_STATOSEGN=Q;};
	int getQSTATO_SEGN(){return Q_STATOSEGN;};
	int Size(){return 37;}
	virtual System::String ^ToString() override;
};

