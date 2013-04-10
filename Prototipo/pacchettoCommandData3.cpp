#include "pacchettoCommandData3.h"


pacchettoCommandData3::pacchettoCommandData3(void)
{
}

// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 14, ma il controllo sulla 
// dimensione deve essere fatto all'esterno della funzione) e copia in buffer il contenuto del pacchettoCommandData1
void pacchettoCommandData3::serializepacchettoCommandData(byte *buffer)
{
	for(int i = 0; i < 14; ++i)
		buffer[i+8] = data.flatData[i];
}

pacchettoCommandData3::~pacchettoCommandData3(void)
{
}
