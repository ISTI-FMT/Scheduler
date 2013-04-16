#include "pacckettoAcknowledgement.h"


pacckettoAcknowledgement::pacckettoAcknowledgement(void)
{
	data.head.NID_MESSAGE = 0;
	data.head.L_MESSAGE = 0;
	data.head.T_TRAIN = 0;
	data.NID_ENGINE = 0;
	data.ack.NID_PACKET = 0;
	data.ack.L_PACKET = 0;
	data.ack.T_TRAIN = 0;
	data.ack.Q_MISSION_RESPONSE = 0;
}

// metodo per la serializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacckettoAcknowledgement::serialize(byte *buff)
{

}

// metodo per la deserializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacckettoAcknowledgement::deserialize(byte *buff)
{

}

pacckettoAcknowledgement::~pacckettoAcknowledgement(void)
{
}
