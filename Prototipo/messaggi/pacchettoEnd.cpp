#include "pacchettoEnd.h"
#include "..\\utility.h"

pacchettoEnd::pacchettoEnd(void)
{
	data.NID_PACKET = 0;
}

void pacchettoEnd::serialize(byte *buffer)
{
	push(buffer, data.NID_PACKET, 8, 51);
}

void pacchettoEnd::deserialize(byte *buffer)
{
	data.NID_PACKET = pop(buffer, 8, 51);
}

pacchettoEnd::~pacchettoEnd(void)
{
}
