#pragma once
#include "utility.h"


/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto Acnowledgement che l'ATS riceve dal ATO
nel messaggio di acnowledgement, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/

/*-----------------------------------------------------------------------------------------------
questa classe rappresenta un Pacchetto di Acnowledgement
L'ATS riceve dal ATO dei messaggi di acnowledgement
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
	void serialize(array<Byte>^buff);
	void deserialize(array<Byte>^buff);
	~pacchettoAcknowledgement(void);
	virtual System::String ^ToString() override;
	
	
};

