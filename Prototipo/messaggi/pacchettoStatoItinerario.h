#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS riceve dall'IXl messaggi contenenti informazioni relative allo stato degli itnerari
-------------------------------------------------------------------------------------------------*/

class pacchettoStatoItinerario
{
	StatoItinerario data;
public:
	pacchettoStatoItinerario(void);

	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};

	// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
	void setN_ITER(int N);
	int getN_ITER(){return data.N_ITER;};
	// in questi metodi index rappresenta l'indice dell'itinerario di cui si vogliono leggere/scrivere le caratteristiche
	// se index � 0, il metodo modificher� i dati relativi al primo itinerario, altrimenti modificher� i dati 
	// relativi agli altri itinerari.
	void setNID_ITIN(int index, int N);
	int getNID_ITIN(int index);
	void setSTATO_ITIN(int index, int S);
	int getSTATO_ITIN(int index);

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sar� chiamata da chi vorr� serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buffer);
	void deserialize(byte *buffer);

	~pacchettoStatoItinerario(void);
};

