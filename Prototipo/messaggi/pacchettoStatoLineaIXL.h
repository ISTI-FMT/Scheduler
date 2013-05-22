#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS riceve dall'IXl messaggi contenenti informazioni relative allo stato della linea
-------------------------------------------------------------------------------------------------*/

class pacchettoStatoLineaIXL
{
	StatoLineaIXL data;
public:
	pacchettoStatoLineaIXL(void);

	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return data.N_ITER;};
	// in questi metodi index rappresenta l'indice del CDB di cui si vogliono leggere/scrivere le caratteristiche
	// se index è 0, il metodo modificherà i dati relativi al primo CDB, altrimenti modificherà i dati 
	// relativi agli altri CDB.
	void setNID_CDB(int index, int N);
	int getNID_CDB(int index);
	void setQ_STATOCDB(int index, int Q);
	int getQ_STATOCDB(int index);
	void setQ_DEVIATOIO(int index, int Q);
	int getQ_DEVIATOIO(int index);

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buffer);
	void deserialize(byte *buffer);

	~pacchettoStatoLineaIXL(void);
	System::String ^ToString();
};

