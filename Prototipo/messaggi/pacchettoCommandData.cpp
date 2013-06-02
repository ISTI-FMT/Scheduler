#include "pacchettoCommandData.h"
#include "utility.h"

pacchettoCommandData::pacchettoCommandData(void)
{
	NID_PACKET = 0;
	L_PACKET = 0;
	Q_COMMAND_TYPE = 0;
	M_GOA_LEVEL = 0;
	NID_OPERATIONAL = 0;
	const int WAKE_UP = 0;
	const int CHANGE_GOA_LEVEL = 3;
	const int TRN = 4;
	const int SLEEP = 7;
}

// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 10, ma il controllo sulla 
// dimensione deve essere fatto all'esterno della funzione) e copia in buffer il contenuto del pacchettoCommandData
void pacchettoCommandData::serializepacchettoCommandData(byte *buffer)
{

	push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, L_PACKET, 13, 59);
	push(buffer, Q_COMMAND_TYPE, 3, 72);
	if(Q_COMMAND_TYPE==4){
		push(buffer, M_GOA_LEVEL, 2, 75);
	}
	if(Q_COMMAND_TYPE==5){
		push(buffer, NID_OPERATIONAL, 32, 75);

	}

}

void pacchettoCommandData::deserializepacchettoCommandData(byte *buffer)
{

	NID_PACKET=pop(buffer,  8, 51);
	L_PACKET=pop(buffer, 13, 59);
	Q_COMMAND_TYPE=pop(buffer,3, 72);
	if(Q_COMMAND_TYPE==4){
		M_GOA_LEVEL=pop(buffer, 2, 75);
	}
	if(Q_COMMAND_TYPE==5){
		NID_OPERATIONAL=pop(buffer, 32, 75);

	}
}

pacchettoCommandData::~pacchettoCommandData(void)
{
}

System::String ^pacchettoCommandData::ToString(){
	System::String ^out = "NID_PACKET "+getNID_PACKET()+";\n";
	out = out+"L_PACKET "+getL_PACKET()+";";
	out = out+"Q_COMMAND_TYPE "+getQ_COMMAND_TYPE()+";";

	if(getM_GOA_LEVEL()!=0 && getQ_COMMAND_TYPE() ==4)
		out = out+"M_GOA_LEVEL "+getM_GOA_LEVEL()+";";
	if(getNID_OPERATIONAL()!=0 && getQ_COMMAND_TYPE() ==5)
		out = out+"NID_OPERATIONAL "+getNID_OPERATIONAL()+";";

	return out;

}
