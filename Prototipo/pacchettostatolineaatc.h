#pragma once
#include "struttureDatiMessaggi.h"

class pacchettostatolineaatc
{
public:
	pacchettostatolineaatc();
	pkgstatolinea data;

	
	
public:
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buff);
	void deserialize(byte *buff);
	
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	

	void setNID_PACKET(int NID){data.NID_PACKET = NID;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};

	void setNID_OPERATIONAL(int NID){data.NID_OPERATIONAL = NID;};
	int getNID_OPERATIONAL(){return data.NID_OPERATIONAL;};

	void setN_ITER(int N);
	int getN_ITER(){return data.N_ITER;};

	void setNID_CDB(int index, int NID);
	int getNID_CDB(int index);
	void setQ_DEVIATIOIO(int index, int Q);
	int getQ_DEVIATIOIO(int index);
	void setQ_STATOCDB(int index, int Q);
	int getQ_STATOCDB(int index);

	System::String^ toPrint();

};

