#pragma once
#include "struttureDatiMessaggi.h"

class pacckettoAcknowledgement
{
	acknowledgement data;
public:
	pacckettoAcknowledgement(void);
// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	void setNID_MESSAGE(int N){data.structuredData.head.NID_MESSAGE = N;};
	int getNID_MESSAGE(){return data.structuredData.head.NID_MESSAGE;};
	void setL_MESSAGE(int N){data.structuredData.head.L_MESSAGE = N;};
	int getL_MESSAGE(){return data.structuredData.head.L_MESSAGE;};
	void setT_TRAIN(int N){data.structuredData.head.T_TRAIN = N;};
	int getT_TRAIN(){return data.structuredData.head.T_TRAIN;};
	void setNID_ENGINE(int N){data.structuredData.NID_ENGINE = N;};
	int getNID_ENGINE(){return data.structuredData.NID_ENGINE;};
	void setNID_PACKET(int N){data.structuredData.ack.NID_PACKET = N;};
	int getNID_PACKET(){return data.structuredData.ack.NID_PACKET;};
	void setL_PACKET(int L){data.structuredData.ack.L_PACKET = L;};
	int getL_PACKET(){return data.structuredData.ack.L_PACKET;};
	//void setT_TRAIN(int T){data.structuredData.ack.T_TRAIN = T;};
	//int getT_TRAIN(){return data.structuredData.ack.T_TRAIN;};
	void setQ_MISSION_RESPONSE(int Q){data.structuredData.ack.Q_MISSION_RESPONSE = Q;};
	int getQ_MISSION_RESPONSE(){return data.structuredData.ack.Q_MISSION_RESPONSE;};
	// metodi per la serializzazione e deserializzazione del messaggio
	// il buffer di byte deve essere stato precedentemente correttamente allocato.
	void serialize(byte *buff);
	void deserialize(byte *buff);
	~pacckettoAcknowledgement(void);
};

