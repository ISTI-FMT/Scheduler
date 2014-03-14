#pragma once
#include "utility.h"
#include "StateSegnale.h"
#include "pacchettoBase.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*
Rappresenta le informazioni contenute nel pacchetto Stato Segnali che l'ATS riceve dal IXL nel messaggio di stato della linea
*/

public ref class pacchettoStatoSegnali : pacchettoBase
{
	int L_PACKET ;
	int N_ITER ;
	List<StateSegnale^> ^vStatoSegnale;
public:
	pacchettoStatoSegnali(void);

	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};

	void setstatoSegnale(List< StateSegnale^> ^all){vStatoSegnale=all;};
	void setstatoSegnale( StateSegnale^ one){vStatoSegnale->Add(one);};
	List< StateSegnale^> ^getstatoSegnale(){return vStatoSegnale;};
	
	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;

	virtual System::String ^ToString() override;
};

