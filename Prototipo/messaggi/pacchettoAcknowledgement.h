#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS riceve dal treno dei messaggi di acnowledgement
-----------------------------------------------------------------------------------------------*/

class pacchettoAcknowledgement
{
	missionAck data;
public:
	pacchettoAcknowledgement(void);
	// funzione che restituisce la dimensione in bit
	int getSize(){return 54;};
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto

	
	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};
	void setQ_MISSION_RESPONSE(int Q){data.Q_MISSION_RESPONSE = Q;};
	int getQ_MISSION_RESPONSE(){return data.Q_MISSION_RESPONSE;};
	void setT_TRAIN(int N){data.T_TRAIN = N;};
	int getT_TRAIN(){return data.T_TRAIN;};
	// metodi per la serializzazione e deserializzazione del messaggio
	// il buffer di byte deve essere stato precedentemente correttamente allocato.
	void serialize(byte *buff);
	void deserialize(byte *buff);
	~pacchettoAcknowledgement(void);
	
	System::String ^ ToString(){
		System::String ^out;

	out = out+"NID_PACKET: "+data.NID_PACKET+";";
	out = out+"L_PACKET: "+data.L_PACKET+";";
	out = out+"T_TRAIN: "+data.T_TRAIN+";";
	out = out+"Q_MISSION_RESPONSE: "+data.Q_MISSION_RESPONSE+";";
	 return out;
	};
};

