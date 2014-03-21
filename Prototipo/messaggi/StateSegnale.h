#pragma once

/*
Rappresenta lo stato dei segnali del pacchetto stato segnali rivevuto dall'IXL
*/

public enum class QStatoSegn {NessunAggiornamento = 0, R=1, G=2, Gx = 3, V = 4, RG = 5, RGx = 6, RV = 7, GV = 8, GxVx = 9, GpVp = 10, GG = 11, RGV = 12, RGxVx = 13, RGpVp = 14, RGG = 15};
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
public ref class StateSegnale
{
	int NID_SEGN ;
	int Q_STATOSEGN ;
public:
	StateSegnale(void);
	StateSegnale(int N, int Q){NID_SEGN=N;Q_STATOSEGN=Q;};
	void setNID_SEGN( int N){NID_SEGN=N;};
	int getNID_SEGN(){return NID_SEGN;};
	void setQSTATO_SEGN( QStatoSegn Q){Q_STATOSEGN=(int)Q;};
	int getQSTATO_SEGN(){return Q_STATOSEGN;};
	int Size(){return 37;}
	virtual System::String ^ToString() override;
};

