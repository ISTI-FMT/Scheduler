#pragma once
#include "utility.h"
#include "pacchettoBase.h"

/*
Rappresenta le informazioni contenute nel pacchetto Presentazione che l'ATS riceve dal ATO nel messaggio di Presentazione
*/

public ref class pacchettopresentazione : pacchettoBase
{
	int L_PACKET;
	int M_PORT;
public:
	pacchettopresentazione(void);

	virtual int getSize() override {return 53;};
	
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setM_PORT(int Q){M_PORT = Q;};
	int getM_PORT(){return M_PORT;};

	virtual void serialize(array<Byte>^buff, int offset) override;
	virtual void deserialize(array<Byte>^buff, int offset) override;
	
	virtual System::String ^ToString() override;
};

