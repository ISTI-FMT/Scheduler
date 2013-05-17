#include "pacchettoEnd.h"
#include "..\\utility.h"

pacchettoEnd::pacchettoEnd(void)
{
	data.NID_PACKET = 0;
}

void pacchettoEnd::serialize(byte *buffer, int offset)
{
	push(buffer, data.NID_PACKET, 8, offset + 51);
}

void pacchettoEnd::deserialize(byte *buffer, int offset)
{
	data.NID_PACKET = pop(buffer, 8, offset + 51);
}

pacchettoEnd::~pacchettoEnd(void)
{
}
