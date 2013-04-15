#include "pacckettoAcknowledgement.h"


pacckettoAcknowledgement::pacckettoAcknowledgement(void)
{
	data.structuredData.head.NID_MESSAGE = 0;
	data.structuredData.head.L_MESSAGE = 0;
	data.structuredData.head.T_TRAIN = 0;
	data.structuredData.NID_ENGINE = 0;
	data.structuredData.ack.NID_PACKET = 0;
	data.structuredData.ack.L_PACKET = 0;
	data.structuredData.ack.T_TRAIN = 0;
	data.structuredData.ack.Q_MISSION_RESPONSE = 0;
}

// metodo per la serializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacckettoAcknowledgement::serialize(byte *buff)
{
	for(int i = 0; i < 17; ++i)
		buff[i] = data.flatData[i];
}

// metodo per la deserializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacckettoAcknowledgement::deserialize(byte *buff)
{
	for(int i = 0; i < 17; ++i)
		data.flatData[i] = buff[i];
}

pacckettoAcknowledgement::~pacckettoAcknowledgement(void)
{
}
