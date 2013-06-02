#pragma once
#include "utility.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS riceve dal treno dei messaggi di acnowledgement
-----------------------------------------------------------------------------------------------*/

ref class pacchettoAcknowledgement
{
	unsigned int NID_PACKET;
	unsigned int L_PACKET;
	unsigned int T_TRAIN ;
	unsigned int Q_MISSION_RESPONSE;
	unsigned int padding ;
public:
	pacchettoAcknowledgement(void);
	// funzione che restituisce la dimensione in bit
	int getSize(){return 54;};
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto

	
	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setQ_MISSION_RESPONSE(int Q){Q_MISSION_RESPONSE = Q;};
	int getQ_MISSION_RESPONSE(){return Q_MISSION_RESPONSE;};
	void setT_TRAIN(int N){T_TRAIN = N;};
	int getT_TRAIN(){return T_TRAIN;};
	// metodi per la serializzazione e deserializzazione del messaggio
	// il buffer di byte deve essere stato precedentemente correttamente allocato.
	void serialize(byte *buff);
	void deserialize(byte *buff);
	~pacchettoAcknowledgement(void);
	virtual System::String ^ToString() override;
	
	
};

