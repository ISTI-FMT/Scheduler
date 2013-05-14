#include "pacckettoEnd.h"
#include "..\\utility.h"

pacckettoEnd::pacckettoEnd(void)
{
	data.NID_PACKET = 0;
}

void pacckettoEnd::serialize(byte *buffer)
{
	push(buffer, data.NID_PACKET, 8, 51);
}

void pacckettoEnd::deserialize(byte *buffer)
{
	data.NID_PACKET = pop(buffer, 8, 51);
}

pacckettoEnd::~pacckettoEnd(void)
{
}
