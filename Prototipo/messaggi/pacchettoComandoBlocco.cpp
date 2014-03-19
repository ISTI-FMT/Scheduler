#include "pacchettoComandoBlocco.h"
#include "utility.h"

pacchettoComandoBlocco::pacchettoComandoBlocco(void)
{
	setNID_PACKET(Pacchetto::PacchettoComandoBlocco);
	L_PACKET = 0;
	NID_BLOCCO = 0;
	Q_CMDBLOCCO = 0;
}

int pacchettoComandoBlocco::getSize()
{
	return 55;
}

void pacchettoComandoBlocco::serialize(array<Byte>^buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
	offset += 8;
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset);
	offset += 13;
	utility::push(buffer, NID_BLOCCO, 32, offset);
	offset += 32;
	utility::push(buffer, Q_CMDBLOCCO, 2, offset);}

void pacchettoComandoBlocco::deserialize(array<Byte>^buffer, int offset)
{
	NID_PACKET=utility::pop(buffer,  8, offset);
	offset += 8;
	L_PACKET=utility::pop(buffer, 13, offset);
	offset += 13;
	NID_BLOCCO=utility::pop(buffer, 32, offset);
	offset += 32;
	Q_CMDBLOCCO=utility::pop(buffer, 2, offset);
}

pacchettoComandoBlocco::~pacchettoComandoBlocco(void)
{
}

System::String ^pacchettoComandoBlocco::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+"NID_BLOCCO: "+NID_BLOCCO+";";
	out = out+"Q_CMDBLOCCO: "+Q_CMDBLOCCO+";";
	return out;
}