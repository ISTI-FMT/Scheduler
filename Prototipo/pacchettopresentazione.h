#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
L'ATS riceve dal treno dei messaggi di 
-------------------------------------------------------------------------------------------------*/

class pacchettopresentazione
{
	presentation data;
public:
	pacchettopresentazione(void);
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize(){return 16;};
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	void setNID_MESSAGE(int N){data.head.NID_MESSAGE = N;};
	int getNID_MESSAGE(){return data.head.NID_MESSAGE;};
	void setL_MESSAGE(int N){data.head.L_MESSAGE = N;};
	int getL_MESSAGE(){return data.head.L_MESSAGE;};
	void setT_TRAIN(int N){data.head.T_TRAIN = N;};
	int getT_TRAIN(){return data.head.T_TRAIN;};
	void setNID_ENGINE(int N){data.NID_ENGINE = N;};
	int getNID_ENGINE(){return data.NID_ENGINE;};
	void setNID_PACKET(int N){data.net.NID_PACKET = N;};
	int getNID_PACKET(){return data.net.NID_PACKET;};
	void setL_PACKET(int L){data.net.L_PACKET = L;};
	int getL_PACKET(){return data.net.L_PACKET;};
	void setM_PORT(int Q){data.net.M_PORT = Q;};
	int getM_PORT(){return data.net.M_PORT;};
	// metodi per la serializzazione e deserializzazione del messaggio
	// il buffer di byte deve essere stato precedentemente correttamente allocato.
	void serialize(byte *buff);
	void deserialize(byte *buff);
	~pacchettopresentazione(void);
};

