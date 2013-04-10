#pragma once
#include "struttureDatiMessaggi.h"

class pacchettoCommandData2
{
	commandData2 data;
public:
	pacchettoCommandData2(void);
	// funzioni di interfaccia per l'accesso in scrittura e lettura dei campi dati della struttura commandData
	void setNID_PACKET(int NID){data.structuredCommandData.NID_PACKET = NID;};
	int getNID_PACKET(){return data.structuredCommandData.NID_PACKET;};
	void setL_PACKET(int L){data.structuredCommandData.L_PACKET = L;};
	int getL_PACKET(){return data.structuredCommandData.L_PACKET;};
	void setQ_COMMAND_TYPE(int Q){data.structuredCommandData.Q_COMMAND_TYPE = Q;};
	int getQ_COMMAND_TYPE(){return data.structuredCommandData.Q_COMMAND_TYPE;};
	void setM_GOA_LEVEL(int M){data.structuredCommandData.M_GOA_LEVEL = M;};
	int getM_GOA_LEVEL(){return data.structuredCommandData.M_GOA_LEVEL;};
	// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 20, ma il controllo sulla 
	// dimensione deve essere fatto all'esterno della funzione) e copia nei primi 12 byte del buffer il contenuto dell'header
	// e nei successivi 8 byte il contenuto del pacchettoCommandData
	void serializepacchettoCommandData(byte *buffer);
	~pacchettoCommandData2(void);
};

