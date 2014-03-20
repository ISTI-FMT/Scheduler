#include "pacchettoEnd.h"
#include "utility.h"

pacchettoEnd::pacchettoEnd(void)
{
	setNID_PACKET(PacchettoID::End);
}

void pacchettoEnd::serialize(array<Byte>^buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
}

void pacchettoEnd::deserialize(array<Byte>^buffer, int offset)
{
	NID_PACKET = utility::pop(buffer, 8, offset);
}



System::String ^pacchettoEnd::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";

	return out;
}