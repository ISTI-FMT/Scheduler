#include "pacchettopresentazione.h"
#include "utility.h"

pacchettopresentazione::pacchettopresentazione(void)
{
	setNID_PACKET(PacchettoID::NetworkData);
	L_PACKET = 0;
	setM_PORT(0);

}

void pacchettopresentazione::serialize(array<Byte>^buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
	offset += 8;
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset);
	offset += 13;
	utility::push(buffer, M_PORT, 24, offset);
	offset += 24;

}

void pacchettopresentazione::deserialize(array<Byte>^buff, int offset)
{
	NID_PACKET = utility::pop(buff, 8, offset);
	offset += 8;
	L_PACKET = utility::pop(buff, 13, offset);
	offset += 13;
	M_PORT = utility::pop(buff, 24, offset);
	offset += 24;
}

String ^pacchettopresentazione::ToString() {
	System::String ^out;

	out = out+"NID_PACKET: "+get_NID_PACKET()+";";
	out = out+"L_PACKET: "+getL_PACKET()+";";
	out = out+"M_PORT: "+getM_PORT()+";";
	return out;
}