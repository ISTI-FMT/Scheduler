#include "pacchettoAcknowledgement.h"
#include "utility.h"

pacchettoAcknowledgement::pacchettoAcknowledgement(void)
{
	
	//data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.T_TRAIN = 0;
	data.Q_MISSION_RESPONSE = 0;
}

// metodo per la serializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettoAcknowledgement::serialize(byte *buffer)
{
	
	//push(buffer, data.NID_ENGINE, 24, 51);
	push(buffer, data.NID_PACKET, 8, 75);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, 83);
	push(buffer, data.T_TRAIN, 32, 96);
	push(buffer, data.Q_MISSION_RESPONSE, 1, 128);
}

// metodo per la deserializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettoAcknowledgement::deserialize(byte *buff)
{
	
	//data.NID_ENGINE = pop(buff, 24, 51);
	data.NID_PACKET = pop(buff, 8, 75);
	data.L_PACKET = pop(buff, 13, 83);
	data.T_TRAIN = pop(buff, 32, 96);
	data.Q_MISSION_RESPONSE = pop(buff, 1, 128);
}

pacchettoAcknowledgement::~pacchettoAcknowledgement(void)
{
	
}
