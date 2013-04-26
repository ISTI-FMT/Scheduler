#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
L'ATS riceve dal treno dei messaggi di acnowledgement
-------------------------------------------------------------------------------------------------*/

class pacchettoAcknowledgement
{
	missionAck data;
public:
	pacchettoAcknowledgement(void);
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize(){return 17;};
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto

	
	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};
	void setQ_MISSION_RESPONSE(int Q){data.Q_MISSION_RESPONSE = Q;};
	int getQ_MISSION_RESPONSE(){return data.Q_MISSION_RESPONSE;};
	// metodi per la serializzazione e deserializzazione del messaggio
	// il buffer di byte deve essere stato precedentemente correttamente allocato.
	void serialize(byte *buff);
	void deserialize(byte *buff);
	~pacchettoAcknowledgement(void);
};

