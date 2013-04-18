#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
L'ATS riceve dal treno dei messaggi di acnowledgement
-------------------------------------------------------------------------------------------------*/

class pacchettoAcknowledgement
{
	acknowledgement data;
public:
	pacchettoAcknowledgement(void);
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize(){return 17;};
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	void setNID_MESSAGE(int N){data.head.NID_MESSAGE = N;};
	int getNID_MESSAGE(){return data.head.NID_MESSAGE;};
	void setL_MESSAGE(int N){data.head.L_MESSAGE = N;};
	int getL_MESSAGE(){return data.head.L_MESSAGE;};
	void setT_TRAIN(int N){data.head.T_TRAIN = N; data.ack.T_TRAIN = N;};
	int getT_TRAIN(){return data.head.T_TRAIN;};
	void setNID_ENGINE(int N){data.NID_ENGINE = N;};
	int getNID_ENGINE(){return data.NID_ENGINE;};
	void setNID_PACKET(int N){data.ack.NID_PACKET = N;};
	int getNID_PACKET(){return data.ack.NID_PACKET;};
	void setL_PACKET(int L){data.ack.L_PACKET = L;};
	int getL_PACKET(){return data.ack.L_PACKET;};
	void setQ_MISSION_RESPONSE(int Q){data.ack.Q_MISSION_RESPONSE = Q;};
	int getQ_MISSION_RESPONSE(){return data.ack.Q_MISSION_RESPONSE;};
	// metodi per la serializzazione e deserializzazione del messaggio
	// il buffer di byte deve essere stato precedentemente correttamente allocato.
	void serialize(byte *buff);
	void deserialize(byte *buff);
	~pacchettoAcknowledgement(void);
};

