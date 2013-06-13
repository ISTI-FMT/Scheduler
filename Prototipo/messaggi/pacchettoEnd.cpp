#include "pacchettoEnd.h"
#include "utility.h"

pacchettoEnd::pacchettoEnd(void)
{
	NID_PACKET = 0;
}

void pacchettoEnd::serialize(byte *buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
}

void pacchettoEnd::deserialize(byte *buffer, int offset)
{
	NID_PACKET = utility::pop(buffer, 8, offset);
}

pacchettoEnd::~pacchettoEnd(void)
{
}

System::String ^pacchettoEnd::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";

	return out;
}