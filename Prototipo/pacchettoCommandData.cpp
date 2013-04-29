#include "pacchettoCommandData.h"
#include "utility.h"

pacchettoCommandData::pacchettoCommandData(void)
{
	
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.Q_COMMAND_TYPE = 0;
	data.M_GOA_LEVEL = 0;
	data.NID_OPERATIONAL = 0;
}

// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 10, ma il controllo sulla 
// dimensione deve essere fatto all'esterno della funzione) e copia in buffer il contenuto del pacchettoCommandData
void pacchettoCommandData::serializepacchettoCommandData(byte *buffer)
{

	push(buffer, data.NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, 59);
	push(buffer, data.Q_COMMAND_TYPE, 3, 72);
	if(data.Q_COMMAND_TYPE==4){
		push(buffer, data.M_GOA_LEVEL, 2, 75);
	}
	if(data.Q_COMMAND_TYPE==5){
		push(buffer, data.NID_OPERATIONAL, 32, 75);

	}

}

void pacchettoCommandData::deserializepacchettoCommandData(byte *buffer)
{

	data.NID_PACKET=pop(buffer,  8, 51);
	data.L_PACKET=pop(buffer, 13, 59);
	data.Q_COMMAND_TYPE=pop(buffer,3, 72);
	if(data.Q_COMMAND_TYPE==4){
		data.M_GOA_LEVEL=pop(buffer, 2, 75);
	}
	if(data.Q_COMMAND_TYPE==5){
		data.NID_OPERATIONAL=pop(buffer, 32, 75);

	}
}

pacchettoCommandData::~pacchettoCommandData(void)
{
}
