#include "pacchettoCommandData.h"
#include "utility.h"



pacchettoCommandData::pacchettoCommandData(void)
{
	setNID_PACKET(PacchettoATO::PacchettoCommandData);
	L_PACKET = 0;
	Q_COMMAND_TYPE = 0;
	M_GOA_LEVEL = 0;
	NID_OPERATIONAL = 0;
}

// questa funzione prende in ingresso un buffer di byte (la cui dimensione deve essere almeno 10, ma il controllo sulla 
// dimensione deve essere fatto all'esterno della funzione) e copia in buffer il contenuto del pacchettoCommandData
void pacchettoCommandData::serialize(array<Byte>^buffer, int offset)
{

	utility::push(buffer, NID_PACKET, 8, offset);
	offset +=8;
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset);
	offset +=13;
	utility::push(buffer, Q_COMMAND_TYPE, 3, offset);
	offset +=3;
	if(Q_COMMAND_TYPE==typeCmdData::CHANGE_GOA_LEVEL){
		utility::push(buffer, M_GOA_LEVEL, 2, offset);
		offset +=2;
	}
	if(Q_COMMAND_TYPE==typeCmdData::TRN){
		utility::push(buffer, NID_OPERATIONAL, 32, offset);
		offset +=32;
	}
}

void pacchettoCommandData::deserialize(array<Byte>^buffer, int offset)
{
	NID_PACKET=utility::pop(buffer, 8, offset);
	offset +=8;
	L_PACKET=utility::pop(buffer, 13, offset);
	offset +=13;
	Q_COMMAND_TYPE=utility::pop(buffer,3, offset);
	offset +=3;
	if(Q_COMMAND_TYPE==typeCmdData::CHANGE_GOA_LEVEL){
		M_GOA_LEVEL=utility::pop(buffer, 2, offset);
		offset +=2;
	}
	if(Q_COMMAND_TYPE==typeCmdData::TRN){
		NID_OPERATIONAL=utility::pop(buffer, 32, offset);
		offset +=32;
	}
}

pacchettoCommandData::~pacchettoCommandData(void)
{
}

System::String ^pacchettoCommandData::ToString(){
	System::String ^out = "NID_PACKET "+NID_PACKET+";\n";
	out = out+"L_PACKET "+getL_PACKET()+";";
	out = out+"Q_COMMAND_TYPE "+getQ_COMMAND_TYPE()+";";

	if(getM_GOA_LEVEL()!=0 && getQ_COMMAND_TYPE() ==4)
		out = out+"M_GOA_LEVEL "+getM_GOA_LEVEL()+";";
	if(getNID_OPERATIONAL()!=0 && getQ_COMMAND_TYPE() ==5)
		out = out+"NID_OPERATIONAL "+getNID_OPERATIONAL()+";";

	return out;

}
