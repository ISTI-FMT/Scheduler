#include "pacchettoCommandData3.h"
#include "utility.h"


pacchettoCommandData3::pacchettoCommandData3(void)
{
	data.head.NID_MESSAGE = 0;
	data.head.L_MESSAGE = 0;
	data.head.T_TRAIN = 0;
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.Q_COMMAND_TYPE = 0;
	data.NID_OPERATIONAL = 0;
	data.PADDING = 0;
}

// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 14, ma il controllo sulla 
// dimensione deve essere fatto all'esterno della funzione) e copia in buffer il contenuto del pacchettoCommandData1
void pacchettoCommandData3::serializepacchettoCommandData(byte *buffer)
{
	push(buffer, data.head.NID_MESSAGE, 8, 0);
	push(buffer, data.head.L_MESSAGE, 11, 8);
	push(buffer, data.head.T_TRAIN, 32, 19);
	push(buffer, data.NID_PACKET, 8, 51);
	push(buffer, data.L_PACKET, 13, 59);
	push(buffer, data.Q_COMMAND_TYPE, 3, 72);
	push(buffer, data.NID_OPERATIONAL, 32, 75);
}
void pacchettoCommandData3::deserializepacchettoCommandData(byte *buffer)
{
	data.head.NID_MESSAGE= pop(buffer, 8, 0);
	data.head.L_MESSAGE=pop(buffer,11, 8);
	data.head.T_TRAIN=pop(buffer, 32, 19);
	data.NID_PACKET=pop(buffer,  8, 51);
	data.L_PACKET=pop(buffer, 13, 59);
	data.Q_COMMAND_TYPE=pop(buffer,3, 72);
	data.NID_OPERATIONAL=pop(buffer, 32, 75);
}
pacchettoCommandData3::~pacchettoCommandData3(void)
{
}
