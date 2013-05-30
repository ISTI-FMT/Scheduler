#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS invia all'IXl messaggi contenenti comandi sui blocchi
-------------------------------------------------------------------------------------------------*/

class pacchettoComandoBlocco
{
	ComandoBlocco data;
public:
	pacchettoComandoBlocco(void);

	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};
	void setNID_BLOCCO(int N){data.NID_BLOCCO = N;};
	int getNID_BLOCCO(){return data.NID_BLOCCO;};
	void setQ_CMDBLOCCO(int Q){data.Q_CMDBLOCCO = Q;};
	int getQ_CMDBLOCCO(){return data.Q_CMDBLOCCO;};

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buffer);
	void deserialize(byte *buffer);

	~pacchettoComandoBlocco(void);

	System::String ^ToString();
};

