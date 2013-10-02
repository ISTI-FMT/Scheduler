#include "PositionData.h"


PositionData::PositionData(void)
{
	NID_ENGINE=0;
	NID_OPERATIONAL=0;
		NID_CDB=0;

}

System::String ^PositionData::ToString(){
		System::String ^out;

	
	out = out+"NID_OPERATIONAL: "+NID_OPERATIONAL+";";
	out = out+"NID_ENGINE: "+NID_ENGINE+";";
	out = out+"NID_CDB: "+NID_CDB+";";
	 return out;
}


void PositionData::serialize(array<Byte>^buffer, int offset)
{

	utility::push(buffer, NID_OPERATIONAL, 32, offset);
	utility::push(buffer, NID_ENGINE , 32, offset + 32);
	utility::push(buffer, NID_CDB, 32, offset + 64);
	

}

void PositionData::deserialize(array<Byte>^buffer, int offset)
{

	NID_OPERATIONAL=utility::pop(buffer, 32, offset );
	NID_ENGINE=utility::pop(buffer, 32, offset + 32);
	NID_CDB= utility::pop(buffer, 32, offset + 64);
	
}
