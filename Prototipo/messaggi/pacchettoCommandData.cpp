#include "pacchettoCommandData.h"
#include "utility.h"

pacchettoCommandData::pacchettoCommandData(void)
{
	setNID_PACKET(PacchettoID::CommandData);
	L_PACKET = 0;
	setQ_COMMAND_TYPE(QCmdData::WAKE_UP);
	setM_GOA_LEVEL(GOA_LEVEL::Level_2);
	setNID_OPERATIONAL(0);
	setQ_DOORS(FermataType::aperturaTrenoBanchinaDxSx);
}

void pacchettoCommandData::serialize(array<Byte>^buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
	offset +=8;
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset);
	offset +=13;
	utility::push(buffer, Q_COMMAND_TYPE, 3, offset);
	offset +=3;
	if(Q_COMMAND_TYPE==(int)QCmdData::CHANGE_GOA_LEVEL){
		utility::push(buffer, M_GOA_LEVEL, 2, offset);
		offset +=2;
	}
	if(Q_COMMAND_TYPE==(int)QCmdData::TRN){
		utility::push(buffer, NID_OPERATIONAL, 32, offset);
		offset +=32;
	}
	if(Q_COMMAND_TYPE==(int)QCmdData::Door){
		utility::push(buffer, Q_DOORS, 4, offset);
		offset +=4;
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
	if(Q_COMMAND_TYPE==(int)QCmdData::CHANGE_GOA_LEVEL){
		M_GOA_LEVEL=utility::pop(buffer, 2, offset);
		offset +=2;
	}
	if(Q_COMMAND_TYPE==(int)QCmdData::TRN){
		NID_OPERATIONAL=utility::pop(buffer, 32, offset);
		offset +=32;
	}
	if(Q_COMMAND_TYPE==(int)QCmdData::Door){
		Q_DOORS=utility::pop(buffer, 4, offset);
		offset +=4;
	}
}



System::String ^pacchettoCommandData::ToString()
{
	int cmdType = (int)getQ_COMMAND_TYPE();
	System::String ^out = "NID_PACKET "+NID_PACKET+";";
	out = out+"L_PACKET "+getL_PACKET()+";";
	out = out+"Q_COMMAND_TYPE "+cmdType+";";

	if(getQ_COMMAND_TYPE() ==(int)QCmdData::CHANGE_GOA_LEVEL)
		out = out+"M_GOA_LEVEL "+getM_GOA_LEVEL()+";";
	if(getQ_COMMAND_TYPE() ==(int)QCmdData::TRN)
		out = out+"NID_OPERATIONAL "+getNID_OPERATIONAL()+";";
	if(getQ_COMMAND_TYPE() ==(int)QCmdData::Door)
		out = out+"Q_DOORS "+getQ_DOORS()+";";
	return out;
}
