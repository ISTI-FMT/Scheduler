#pragma once
#include "utility.h"
#include "Fault.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;
/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS riceve dall'IXl messaggi di fault reporting con cui l'IXL comunica l'occorrenza di guasti
-------------------------------------------------------------------------------------------------*/

ref class pacchettoFaultData
{
	unsigned int NID_PACKET ;
	unsigned int L_PACKET ;
	Fault ^guasto;
	unsigned int N_ITER ;
	List<Fault^> ^vGuasto;
public:
	pacchettoFaultData(void);
	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};
	

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buffer);
	void deserialize(byte *buffer);

	virtual System::String ^ToString() override;
};
