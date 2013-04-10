#include "pacchettoCommandData2.h"

pacchettoCommandData2::pacchettoCommandData2(void)
{
	for(int i = 0; i < 10; ++i)
		data.flatData[i] = 0;
}

// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 10, ma il controllo sulla 
// dimensione deve essere fatto all'esterno della funzione) e copia in buffer il contenuto del pacchettoCommandData1
void pacchettoCommandData2::serializepacchettoCommandData(byte *buffer)
{
	for(int i = 0; i < 10; ++i)
		buffer[i+8] = data.flatData[i];
}
