#pragma once
#include "struttureDatiMessaggi.h"

class pacchettoCommandData3
{
	commandData3 data;
public:
	pacchettoCommandData3(void);
	// funzioni di interfaccia per l'accesso in scrittura e lettura dei campi dati della struttura commandData
	void setNID_PACKET(int NID){data.structuredData.NID_PACKET = NID;};
	int getNID_PACKET(){return data.structuredData.NID_PACKET;};
	void setL_PACKET(int L){data.structuredData.L_PACKET = L;};
	int getL_PACKET(){return data.structuredData.L_PACKET;};
	void setQ_COMMAND_TYPE(int Q){data.structuredData.Q_COMMAND_TYPE = Q;};
	int getQ_COMMAND_TYPE(){return data.structuredData.Q_COMMAND_TYPE;};
	void setNID_OPERATIONAL(int NID){data.structuredData.NID_OPERATIONAL = NID;};
	int getNID_OPERATIONAL(){return data.structuredData.NID_OPERATIONAL;};
	// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 20, ma il controllo sulla 
	// dimensione deve essere fatto all'esterno della funzione) e copia nei primi 12 byte del buffer il contenuto dell'header
	// e nei successivi 8 byte il contenuto del pacchettoCommandData
	void serializepacchettoCommandData(byte *buffer);
	~pacchettoCommandData3(void);
};

