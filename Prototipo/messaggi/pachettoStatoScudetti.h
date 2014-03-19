#pragma once
#include "utility.h"
#include "StateScudetti.h"
#include "pacchettoBase.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;
using namespace System::Diagnostics::CodeAnalysis;
/*
Rappresenta le informazioni contenute nel pacchetto Stato dei Scudetti che l'ATS riceve dal IXL nel messaggio di stato della linea ** Messaggio cambio pacchetto non più usato
*/


[ExcludeFromCodeCoverage]
public ref class pachettoStatoScudetti : pacchettoBase
{
	int L_PACKET ;	
	int N_ITER ;
	List<StateScudetti^> ^vStatoScudetti;
public:
	pachettoStatoScudetti(void);

	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};
	
	void setStatoScud(List< StateScudetti^> ^all){vStatoScudetti=all;};
	void setStatoScud( StateScudetti^ one){vStatoScudetti->Add(one);};
	List< StateScudetti^> ^getStatoScud(){return vStatoScudetti;};
		
	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;
		
	virtual System::String ^ToString() override;
};

