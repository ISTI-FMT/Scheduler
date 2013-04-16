#include "pacchettoCommandData1.h"


pacchettoCommandData1::pacchettoCommandData1(void)
{
	for(int i = 0; i < 12; ++i)
		data.flatData[i] = 0;
}

// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 10, ma il controllo sulla 
// dimensione deve essere fatto all'esterno della funzione) e copia in buffer il contenuto del pacchettoCommandData1
void pacchettoCommandData1::serializepacchettoCommandData(byte *buffer)
{
	buffer[0] = data.flatData[0];
	buffer[1] = data.flatData[1];
	for(int i = 0; i < 10; ++i)
		buffer[i] = data.flatData[i];
}

pacchettoCommandData1::~pacchettoCommandData1(void)
{
}
