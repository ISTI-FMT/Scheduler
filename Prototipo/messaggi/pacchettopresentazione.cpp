#include "pacchettopresentazione.h"
#include "utility.h"

pacchettopresentazione::pacchettopresentazione(void)
{

	NID_PACKET = 0;
	L_PACKET = 0;
	M_PORT =0;

}

// metodo per la serializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettopresentazione::serialize(byte *buffer)
{
	//push(buffer, data.NID_ENGINE, 24, 51);
	push(buffer, NID_PACKET, 8, 75);
	setL_PACKET(getSize());
	push(buffer, L_PACKET, 13, 83);
	push(buffer, M_PORT, 32, 96);

}

// metodo per la deserializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettopresentazione::deserialize(byte *buff)
{


	//data.NID_ENGINE = pop(buff, 24, 51);
	NID_PACKET = pop(buff, 8, 75);
	L_PACKET = pop(buff, 13, 83);
	M_PORT = pop(buff, 32, 96);

}



String ^pacchettopresentazione::ToString() {
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+"M_PORT: "+M_PORT+";";
	return out;
}