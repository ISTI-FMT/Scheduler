#include "pacchettoCommandData3.h"


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

}

pacchettoCommandData3::~pacchettoCommandData3(void)
{
}
