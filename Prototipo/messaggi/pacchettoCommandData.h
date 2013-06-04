#pragma once
#include "utility.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS manda messaggi di wake-up e TRN al treno con messaggi di tipo unconditional command
mission plan
-------------------------------------------------------------------------------------------------*/

ref class pacchettoCommandData
{
	unsigned int NID_PACKET;
	unsigned int L_PACKET;
	unsigned int Q_COMMAND_TYPE;
	unsigned int M_GOA_LEVEL;
	unsigned int NID_OPERATIONAL ;
	unsigned int PADDING;

public:

	pacchettoCommandData(void);
	// funzione che restituisce la dimensione in bit
	int getSize(){
		//header 51 mess +24 fissi o+2 o +32
		if(getQ_COMMAND_TYPE()==5){
			return 56;
		}
		if(getQ_COMMAND_TYPE()==4){
			return 26;
		}
		return 24;};
	// funzioni di interfaccia per l'accesso in scrittura e lettura dei campi dati della struttura commandData
	
	void setNID_PACKET(int NID){NID_PACKET = NID;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setQ_COMMAND_TYPE(int Q){Q_COMMAND_TYPE = Q;};
	int getQ_COMMAND_TYPE(){return Q_COMMAND_TYPE;};
	void setM_GOA_LEVEL(int M){M_GOA_LEVEL = M;};
	int getM_GOA_LEVEL(){return M_GOA_LEVEL;};
	void setNID_OPERATIONAL(int NID){NID_OPERATIONAL = NID;};
	int getNID_OPERATIONAL(){return NID_OPERATIONAL;};
	// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 20, ma il controllo sulla 
	// dimensione deve essere fatto all'esterno della funzione) e copia nei primi 12 byte del buffer il contenuto dell'header
	// e nei successivi 8 byte il contenuto del pacchettoCommandData
	void serializepacchettoCommandData(byte *buffer);
	void deserializepacchettoCommandData(byte *buff);
	
	virtual System::String ^ToString() override;

	
	~pacchettoCommandData(void);
};

