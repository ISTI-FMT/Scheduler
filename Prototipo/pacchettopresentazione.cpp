#include "pacchettopresentazione.h"
#include "utility.h"

pacchettopresentazione::pacchettopresentazione(void)
{
	data.head.NID_MESSAGE = 0;
	data.head.L_MESSAGE = 0;
	data.head.T_TRAIN = 0;
	data.NID_ENGINE = 0;
	data.net.NID_PACKET = 0;
	data.net.L_PACKET = 0;
	data.net.M_PORT =0;
	
}

// metodo per la serializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettopresentazione::serialize(byte *buffer)
{
	push(buffer, data.head.NID_MESSAGE, 8, 0);
	push(buffer, data.head.L_MESSAGE, 11, 8);
	push(buffer, data.head.T_TRAIN, 32, 19);
	push(buffer, data.NID_ENGINE, 24, 51);
	push(buffer, data.net.NID_PACKET, 8, 75);
	push(buffer, data.net.L_PACKET, 13, 83);
	push(buffer, data.net.M_PORT, 32, 96);
	
}

// metodo per la deserializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettopresentazione::deserialize(byte *buff)
{
	data.head.NID_MESSAGE = pop(buff, 8, 0);
	data.head.L_MESSAGE = pop(buff, 11, 8);
	data.head.T_TRAIN = pop(buff, 32, 19);
	data.NID_ENGINE = pop(buff, 24, 51);
	data.net.NID_PACKET = pop(buff, 8, 75);
	data.net.L_PACKET = pop(buff, 13, 83);
	data.net.M_PORT = pop(buff, 32, 96);
	
}

pacchettopresentazione::~pacchettopresentazione(void)
{
}
