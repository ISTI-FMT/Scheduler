#pragma once
#include "utility.h"
#include "pacchettoBase.h"

/*
Rappresenta i dati inviati dal pacchetto ComandoBlocco che l'ATS invia all'IXL
*/
enum  QCmdBlocco { direzioneLegale = 1, direzioneIllegale = 0};

ref class pacchettoComandoBlocco : pacchettoBase
{
	int L_PACKET ;
	int NID_BLOCCO ;
	int Q_CMDBLOCCO ;
public:
	pacchettoComandoBlocco(void);

	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setNID_BLOCCO(int N){NID_BLOCCO = N;};
	int getNID_BLOCCO(){return NID_BLOCCO;};
	void setQ_CMDBLOCCO(QCmdBlocco Q){Q_CMDBLOCCO = Q;};
	QCmdBlocco getQ_CMDBLOCCO(){return (QCmdBlocco)Q_CMDBLOCCO;};

	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;

	~pacchettoComandoBlocco(void);

	virtual System::String ^ToString() override;
};

