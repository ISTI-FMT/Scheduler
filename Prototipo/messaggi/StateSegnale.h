#pragma once

/*
Rappresenta lo stato dei segnali del pacchetto stato segnali rivevuto dall'IXL
*/

ref class StateSegnale
{
	int NID_SEGN ;
	int Q_STATOSEGN ;
public:
	StateSegnale(void);
	StateSegnale(int N, int Q){NID_SEGN=N;Q_STATOSEGN=Q;};
	void setNID_SEGN( int N){NID_SEGN=N;};
	int getNID_SEGN(){return NID_SEGN;};
	void setQSTATO_SEGN( int Q){Q_STATOSEGN=Q;};
	int getQSTATO_SEGN(){return Q_STATOSEGN;};
	int Size(){return 37;}
	virtual System::String ^ToString() override;
};

