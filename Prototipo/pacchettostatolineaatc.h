#pragma once
#include "struttureDatiMessaggi.h"

class pacchettostatolineaatc
{
public:
	pacchettostatolineaatc();
	messtatolinea data;

	void serializeStructuredHeader(byte *buff, messtatolinea &h, int &index);
	void deserializeStructuredHeader(byte *buff, messtatolinea &h, int &index);
	
public:
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serializeStructuredHeader(byte *buff, int &index){serializeStructuredHeader(buff, data, index);};
	void deserializeStructuredHeader(byte *buff, int &index){deserializeStructuredHeader(buff, data, index);};
	
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	void setNID_MESSAGE(int N){data.head.NID_MESSAGE = N;};
	int getNID_MESSAGE(){return data.head.NID_MESSAGE;};
	void setL_MESSAGE(int N){data.head.L_MESSAGE = N;};
	int getL_MESSAGE(){return data.head.L_MESSAGE;};
	void setT_TRAIN(int N){data.head.T_TRAIN = N;};
	int getT_TRAIN(){return data.head.T_TRAIN;};
	void setNID_PACKET(int NID){data.pkg.NID_PACKET = NID;};
	int getNID_PACKET(){return data.pkg.NID_PACKET;};
	void setL_PACKET(int L){data.pkg.L_PACKET = L;};
	int getL_PACKET(){return data.pkg.L_PACKET;};
};

