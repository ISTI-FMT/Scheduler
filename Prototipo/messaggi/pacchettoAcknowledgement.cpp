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
void pacchettoAcknowledgement::serialize(byte *buffer)
{
	
	//utility::push(buffer, NID_ENGINE, 24, 51);
	utility::push(buffer, NID_PACKET, 8, 75);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, 83);
	utility::push(buffer, T_TRAIN, 32, 96);
	utility::push(buffer, Q_MISSION_RESPONSE, 1, 128);
}

// metodo per la deserializzazion del messaggio
// il buffer di byte deve essere stato precedentemente correttamente allocato.
void pacchettoAcknowledgement::deserialize(byte *buff)
{
	
	//NID_ENGINE = utility::pop(buff, 24, 51);
	NID_PACKET = utility::pop(buff, 8, 75);
	L_PACKET = utility::pop(buff, 13, 83);
	T_TRAIN = utility::pop(buff, 32, 96);
	Q_MISSION_RESPONSE = utility::pop(buff, 1, 128);
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
