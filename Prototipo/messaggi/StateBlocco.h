#pragma once

public enum class  QStatoBlocco {  illegale = 0, legale = 1};

/*
Rappresenta le informazioni dello stato del blocco del pacchetto StatoBlocco da inviare all'IXL
*/
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
public ref class StateBlocco
{
	int NID_BLOCCO ;
	int Q_STATOBLOCCO;
public:
	StateBlocco(void);
	StateBlocco(int N, int Q){NID_BLOCCO=N;Q_STATOBLOCCO=Q;};
	int Size(){return 34;}
	void setNID_BLOCCO(int N){NID_BLOCCO=N;};
	int getNID_BLOCCO(){return NID_BLOCCO;};
	void setQ_STATOBLOCCO( QStatoBlocco Q){Q_STATOBLOCCO=(int)Q;};
	int getQ_STATOBLOCCO(){return Q_STATOBLOCCO;};
	virtual System::String ^ToString() override;
};

