#pragma once
#include "struttureDatiMessaggi.h"
 ref class pachettoStatoScudetti
{
	StatoScudetti &data;
public:
	pachettoStatoScudetti();

	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return data.N_ITER;};
	
	void setNID_SCUD(int index, int N);
	int getNID_SCUD(int index);
	void setQ_STATOSCUD(int index, int Q);
	int getQ_STATOSCUD(int index);

	
	int getSize();
	void serialize(byte *buffer, int offset);
	void deserialize(byte *buffer, int offset);

	~pachettoStatoScudetti(void);
	virtual System::String ^ToString() override;
};

