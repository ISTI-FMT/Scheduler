#include "pacchettoCommandData2.h"
#include "utility.h"

pacchettoCommandData2::pacchettoCommandData2(void)
{
	data.head.NID_MESSAGE = 0;
	data.head.L_MESSAGE = 0;
	data.head.T_TRAIN = 0;
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.Q_COMMAND_TYPE = 0;
	data.M_GOA_LEVEL = 0;
	data.PADDING = 0;
}

// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 10, ma il controllo sulla 
// dimensione deve essere fatto all'esterno della funzione) e copia in buffer il contenuto del pacchettoCommandData1
void pacchettoCommandData2::serializepacchettoCommandData(byte *buffer)
{
	push(buffer, data.head.NID_MESSAGE, 8, 0);
	push(buffer, data.head.L_MESSAGE, 11, 8);
	push(buffer, data.head.T_TRAIN, 32, 19);
	push(buffer, data.NID_PACKET, 8, 51);
	push(buffer, data.L_PACKET, 13, 59);
	push(buffer, data.Q_COMMAND_TYPE, 3, 72);
	push(buffer, data.M_GOA_LEVEL, 2, 75);
}

pacchettoCommandData2::~pacchettoCommandData2(void)
{
}
