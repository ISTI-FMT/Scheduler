#pragma once
#include "utility.h"
#include "Fault.h"
#include "pacchettoBase.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/* 
Rappresenta le informazioni contenute nel pacchetto Fault Data che l'ATS riceve dal IXL o ATO nel messaggio di Fault Reporting
*/

public ref class pacchettoFaultData : pacchettoBase
{
	int L_PACKET ;
	
	int N_ITER ;
	List<Fault^> ^vGuasto;
public:
	//Costruttore che accetta l'id del pacchetto.
	//FaultData può avere id diversi a seconda dell'utilizzo
	pacchettoFaultData(int ID_PACKET);
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};
	void setFault(Fault^ f){vGuasto->Add(f);};
	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;

	virtual System::String ^ToString() override;
};
