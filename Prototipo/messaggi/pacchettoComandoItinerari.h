#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS invia all'IXl messaggi contenenti comandi sugli itinerari
-------------------------------------------------------------------------------------------------*/

class pacchettoComandoItinerari
{
	ComandoItinerario data;
public:
	pacchettoComandoItinerari(void);

	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};
	void setNID_ITIN(int N){data.NID_ITIN = N;};
	int getNID_ITIN(){return data.NID_ITIN;};
	void setQ_CMDITIN(int Q){data.Q_CMDITIN = Q;};
	int getQ_CMDITIN(){return data.Q_CMDITIN;};

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buffer);
	void deserialize(byte *buffer);

	~pacchettoComandoItinerari(void);
};

