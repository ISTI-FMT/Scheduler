#include "pacchettoAcknowledgement.h"
#include "utility.h"

pacchettoAcknowledgement::pacchettoAcknowledgement(void)
{
	
	NID_PACKET = 0;
	L_PACKET = 0;
	T_TRAIN = 0;
	Q_MISSION_RESPONSE = 0;
}

// metodo per la serializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettoAcknowledgement::serialize(array<Byte>^buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
	offset +=8;
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset);
	offset +=13;
	utility::push(buffer, T_TRAIN, 32, offset);
	offset +=32;
	utility::push(buffer, Q_MISSION_RESPONSE, 1, offset);
}

// metodo per la deserializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettoAcknowledgement::deserialize(array<Byte>^buff, int offset)
{
	NID_PACKET = utility::pop(buff, 8, offset);
	offset += 8;
	L_PACKET = utility::pop(buff, 13, offset);
	offset += 13;
	T_TRAIN = utility::pop(buff, 32, offset);
	offset += 32;
	Q_MISSION_RESPONSE = utility::pop(buff, 1, offset);
}

System::String ^ pacchettoAcknowledgement::ToString(){
		System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+"T_TRAIN: "+T_TRAIN+";";
	out = out+"Q_MISSION_RESPONSE: "+Q_MISSION_RESPONSE+";";
	 return out;
	};

pacchettoAcknowledgement::~pacchettoAcknowledgement(void)
{
	
}
