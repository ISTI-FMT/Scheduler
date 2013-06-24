#pragma once
#include "utility.h"
#include "StateScudetti.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;
 ref class pachettoStatoScudetti
{
	unsigned int NID_PACKET;
	unsigned int L_PACKET ;
	
	unsigned int N_ITER ;
	List<StateScudetti^> ^vStatoScudetti;
public:
	pachettoStatoScudetti(void);

	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};
	
	

	void setStatoScud(List< StateScudetti^> ^all){vStatoScudetti=all;};
	List< StateScudetti^> ^getStatoScud(){return vStatoScudetti;};

	void setStatoScud( StateScudetti^ one){vStatoScudetti->Add(one);};

	
	int getSize();
	void serialize(byte *buffer, int offset);
	void deserialize(byte *buffer, int offset);

	
	virtual System::String ^ToString() override;
};

