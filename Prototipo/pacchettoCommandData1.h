#pragma once
#include "struttureDatiMessaggi.h"

class pacchettoCommandData1
{
	commandData1 data;
public:
	pacchettoCommandData1(void);
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize(){return 10;};
	// funzioni di interfaccia per l'accesso in scrittura e lettura dei campi dati della struttura commandData
	void setNID_MESSAGE(int N){data.head.NID_MESSAGE = N;};
	int getNID_MESSAGE(){return data.head.NID_MESSAGE;};
	void setL_MESSAGE(int N){data.head.L_MESSAGE = N;};
	int getL_MESSAGE(){return data.head.L_MESSAGE;};
	void setT_TRAIN(int N){data.head.T_TRAIN = N;};
	int getT_TRAIN(){return data.head.T_TRAIN;};
	void setNID_PACKET(int NID){data.NID_PACKET = NID;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};
	void setQ_COMMAND_TYPE(int Q){data.Q_COMMAND_TYPE = Q;};
	int getQ_COMMAND_TYPE(){return data.Q_COMMAND_TYPE;};
	// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 20, ma il controllo sulla 
	// dimensione deve essere fatto all'esterno della funzione) e copia nei primi 12 byte del buffer il contenuto dell'header
	// e nei successivi 8 byte il contenuto del pacchettoCommandData
	void serializepacchettoCommandData(byte *buffer);
	void deserializepacchettoCommandData(byte *buff);
	~pacchettoCommandData1(void);
};

