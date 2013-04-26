#include "pacchettopresentazione.h"
#include "utility.h"

pacchettopresentazione::pacchettopresentazione(void)
{
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.M_PORT =0;
	
}

// metodo per la serializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettopresentazione::serialize(byte *buffer)
{
	//push(buffer, data.NID_ENGINE, 24, 51);
	push(buffer, data.NID_PACKET, 8, 75);
	push(buffer, data.L_PACKET, 13, 83);
	push(buffer, data.M_PORT, 32, 96);
	
}

// metodo per la deserializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettopresentazione::deserialize(byte *buff)
{
	
	
	//data.NID_ENGINE = pop(buff, 24, 51);
	data.NID_PACKET = pop(buff, 8, 75);
	data.L_PACKET = pop(buff, 13, 83);
	data.M_PORT = pop(buff, 32, 96);
	
}

pacchettopresentazione::~pacchettopresentazione(void)
{
}
