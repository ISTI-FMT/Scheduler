#pragma once
#include "utility.h"
#include "pacchettoBase.h"

/*
Questa classe rappresenta le informazioni contenute nel pacchetto Acnowledgement che l'ATS riceve dal ATO.
Contiene metodi per serializzare e deserializzare il contenuto
*/

ref class pacchettoAcknowledgement : pacchettoBase
{
	 int L_PACKET;
	 int T_TRAIN ;
	 int Q_MISSION_RESPONSE;
	 int padding ;
public:
	pacchettoAcknowledgement(void);

	virtual int getSize() override {return 54;};
	virtual void serialize(array<Byte>^buff, int offset) override;
	virtual void deserialize(array<Byte>^buff, int offset) override;

	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setQ_MISSION_RESPONSE(int Q){Q_MISSION_RESPONSE = Q;};
	int getQ_MISSION_RESPONSE(){return Q_MISSION_RESPONSE;};
	void setT_TRAIN(int N){T_TRAIN = N;};
	int getT_TRAIN(){return T_TRAIN;};
	
	~pacchettoAcknowledgement(void);
	virtual System::String ^ToString() override;	
};

