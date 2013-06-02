#pragma once
#include "utility.h"
#include "stateScudetti.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;
 ref class pachettoStatoScudetti
{
	unsigned int NID_PACKET;
	unsigned int L_PACKET ;
	stateScudetti ^statoscudetti;
	unsigned int N_ITER ;
	List<stateScudetti^> ^vStatoScudetti;
public:
	pachettoStatoScudetti(void);

	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};
	
	void setfirstStatoScud(stateScudetti ^sStatoScud){statoscudetti=sStatoScud;};
	stateScudetti ^getfirstStatoScud(){return statoscudetti;};

	void setlastStatoScud(List< stateScudetti^> ^all){vStatoScudetti=all;};
	List< stateScudetti^> ^getlastStatoScud(){return vStatoScudetti;};

	void setlastStatoScud( stateScudetti^ one){vStatoScudetti->Add(one);};

	
	int getSize();
	void serialize(byte *buffer, int offset);
	void deserialize(byte *buffer, int offset);

	
	virtual System::String ^ToString() override;
};

