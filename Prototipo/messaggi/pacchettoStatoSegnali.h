#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS riceve dall'IXL messaggi contenenti informazioni relative allo stato degi segnali
-------------------------------------------------------------------------------------------------*/

class pacchettoStatoSegnali
{
	StatoSegnale data;
public:
	pacchettoStatoSegnali(void);

	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return data.N_ITER;};

	// in questi metodi index rappresenta l'indice del segnale di cui si vogliono leggere/scrivere le caratteristiche
	// se index è 0, il metodo modificherà i dati relativi al primo segnale, altrimenti modificherà i dati 
	// relativi agli altri segnali.
	void setNID_SEGN(int index, int N);
	int getNID_SEGN(int index);
	void setQSTATO_SEGN(int index, int Q);
	int getQSTATO_SEGN(int index);

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buffer, int offset);
	void deserialize(byte *buffer, int offset);

	~pacchettoStatoSegnali(void);
	System::String ^ToString();
};

