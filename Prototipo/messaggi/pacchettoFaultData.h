#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS riceve dall'IXl messaggi di fault reporting con cui l'IXL comunica l'occorrenza di guasti
-------------------------------------------------------------------------------------------------*/

class pacchettoFaultData
{
	FaultData data;
public:
	pacchettoFaultData(void);
	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};
	// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
	void setN_ITER(int N);
	int getN_ITER(){return data.N_ITER;};
	// in questi metodi index rappresenta l'indice del guasto di cui si vogliono leggere/scrivere le caratteristiche
	// se index è 0, il metodo modificherà i dati relativi al primo guasto, altrimenti modificherà i dati 
	// relativi agli altri guasti.
	void setNID_COMPONENT(int index, int N);
	int getNID_COMPONENT(int index);
	void setM_FAULT(int index, int M);
	int getM_FAULT(int index);

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buffer);
	void deserialize(byte *buffer);

	~pacchettoFaultData(void);
	System::String ^ToString();
};
