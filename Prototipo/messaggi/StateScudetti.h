#pragma once

/*
Rappresenta le informazioni sullo stato degli scudetti del pacchetto stato scudetti rivevuto dall'IXL
*/
public enum class QStatoScud { Riposo = 0, OrigineInviato = 1, OrigineInAtto = 2, FineInviato = 3, FineInAtto = 4};
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
public ref class StateScudetti
{
	int NID_SCUD ;
	int Q_STATOSCUD ;
public:
	StateScudetti(void);
	StateScudetti(int N, int Q){NID_SCUD=N;Q_STATOSCUD=Q;};
	void setNID_SCUD( int N){NID_SCUD=N;};
	int getNID_SCUD(){return NID_SCUD;};
	void setQ_STATOSCUD( QStatoScud Q){Q_STATOSCUD=(int)Q;};
	int getQ_STATOSCUD(){return Q_STATOSCUD;};
	int Size(){return 32+3;};
	virtual System::String ^ToString() override;
};

