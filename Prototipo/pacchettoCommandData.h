#pragma once
#include "struttureDatiMessaggi.h"



class pacchettoCommandData
{
	commandData data;
public:
	pacchettoCommandData(void);
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sar� chiamata da chi vorr� serializzare il messaggio, per poter allocare il buffer
	int getSize(){
		//header 51 mess +24 fissi=75/8=10
		if(getQ_COMMAND_TYPE()==5){
			return 14;
		}
		return 10;};
	// funzioni di interfaccia per l'accesso in scrittura e lettura dei campi dati della struttura commandData
	
	void setNID_PACKET(int NID){data.NID_PACKET = NID;};
	int getNID_PACKET(){return data.NID_PACKET;};
	void setL_PACKET(int L){data.L_PACKET = L;};
	int getL_PACKET(){return data.L_PACKET;};
	void setQ_COMMAND_TYPE(int Q){data.Q_COMMAND_TYPE = Q;};
	int getQ_COMMAND_TYPE(){return data.Q_COMMAND_TYPE;};
	void setM_GOA_LEVEL(int M){data.M_GOA_LEVEL = M;};
	int getM_GOA_LEVEL(){return data.M_GOA_LEVEL;};
	void setNID_OPERATIONAL(int NID){data.NID_OPERATIONAL = NID;};
	int getNID_OPERATIONAL(){return data.NID_OPERATIONAL;};
	// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 20, ma il controllo sulla 
	// dimensione deve essere fatto all'esterno della funzione) e copia nei primi 12 byte del buffer il contenuto dell'header
	// e nei successivi 8 byte il contenuto del pacchettoCommandData
	void serializepacchettoCommandData(byte *buffer);
	void deserializepacchettoCommandData(byte *buff);
	~pacchettoCommandData(void);
};

