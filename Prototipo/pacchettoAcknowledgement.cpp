#include "pacchettoAcknowledgement.h"
#include "utility.h"

pacchettoAcknowledgement::pacchettoAcknowledgement(void)
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
void pacchettoAcknowledgement::serialize(byte *buffer)
{
	push(buffer, data.head.NID_MESSAGE, 8, 0);
	push(buffer, data.head.L_MESSAGE, 11, 8);
	push(buffer, data.head.T_TRAIN, 32, 19);
	push(buffer, data.NID_ENGINE, 24, 51);
	push(buffer, data.ack.NID_PACKET, 8, 75);
	push(buffer, data.ack.L_PACKET, 13, 83);
	push(buffer, data.ack.T_TRAIN, 32, 96);
	push(buffer, data.ack.Q_MISSION_RESPONSE, 1, 128);
}

// metodo per la deserializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettoAcknowledgement::deserialize(byte *buff)
{
	data.head.NID_MESSAGE = pop(buff, 8, 0);
	data.head.L_MESSAGE = pop(buff, 11, 8);
	data.head.T_TRAIN = pop(buff, 32, 19);
	data.NID_ENGINE = pop(buff, 24, 51);
	data.ack.NID_PACKET = pop(buff, 8, 75);
	data.ack.L_PACKET = pop(buff, 13, 83);
	data.ack.T_TRAIN = pop(buff, 32, 96);
	data.ack.Q_MISSION_RESPONSE = pop(buff, 1, 128);
}

pacchettoAcknowledgement::~pacchettoAcknowledgement(void)
{
}
