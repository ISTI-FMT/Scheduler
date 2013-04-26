#include "Messaggi.h"
#include "utility.h"


Messaggi::Messaggi(void)
{
	head = new structuredHeader;
	head->NID_MESSAGE = 0;
	head->L_MESSAGE = 0;
	head->T_TRAIN = 0;
	head->NID_ENGINE=0;
}


void Messaggi::serialize(byte *buffer)
{
	push(buffer, head->NID_MESSAGE, 8, 0);
	push(buffer, head->L_MESSAGE, 11, 8);
	push(buffer, head->T_TRAIN, 32, 19);
	int N = head->NID_MESSAGE;
	switch (N)
	{
	case 200 : {get_pacchettoMissionPlan()->serializeMissionPlanPkt(buffer);
			   break;}
	case 201 : {get_pacchettoCommandData()->serializepacchettoCommandData(buffer);
			   break;}
	case 215 : {push(buffer, head->NID_ENGINE, 24, 51);
		get_pacchettoPresentazione()->serialize(buffer);
			   break;}
	case 1 : {get_pacchettoStatoLineaATC()->serialize(buffer);
			 break;}
	case 210 :{push(buffer, head->NID_ENGINE, 24, 51);
		get_pacchettoAcknowledgement()->serialize(buffer);
			  break;}


	default:
		break;
	}

}

void Messaggi::serialize(array<System::Byte>^bytez){
	int len=0;
	switch (head->NID_MESSAGE)
	{
	case 200 : {len=pkgMP->getSize();break;}
	case 201 : {len=pkgcd1->getSize();break;}
	case 215 : {len=pgkPres->getSize();break;}
	case 1 : {len=pkgStatoATC->getSize();break;}
	case 210 :{len=pkgAck->getSize();break;}


	default:
		break;
	}
	byte *buffer = new byte[len];
	for(int i = 0; i < len; ++i)
		buffer[i] = 0;
	serialize(buffer);

	for(int i = 0; i < len; ++i)
		bytez[i] = buffer[i];
	
}

void Messaggi::deserialize(byte *buffer)
{
	head->NID_MESSAGE= pop(buffer, 8, 0);
	head->L_MESSAGE=pop(buffer,11, 8);
	head->T_TRAIN=pop(buffer, 32, 19);
	switch (head->NID_MESSAGE)
	{
	case 200 : {set_pacchettoMissionPlan();
		pkgMP->deserializeMissionPlanPkt(buffer);
		break;

			   }
	case 201 : {set_pacchettoCommandData();
		pkgcd1->deserializepacchettoCommandData(buffer);
		break;

			   }

	case 215 : {head->NID_ENGINE = pop(buffer, 24, 51);
		set_pacchettoPresentazione();
		pgkPres->deserialize(buffer);
		break;

			   }

	case 1 : {set_pacchettoStatoLineaATC();
		pkgStatoATC->deserialize(buffer);
		break;
			 }

	case 210 : {head->NID_ENGINE = pop(buffer, 24, 51);
		set_pacchettoAcknowledgement();
		pkgAck->deserialize(buffer);
		break;
			   }
	default:
		break;
	}

}
void Messaggi::deserialize(array<System::Byte>^bytez){
	
	byte *buffer = new byte[bytez->Length];
	for(int i = 0; i < bytez->Length; ++i)
		buffer[i] = bytez[i];
	
	deserialize(buffer);
	
	//
}


String ^Messaggi::ToString(){

	String ^out = "NID_MESSAGE "+getNID_MESSAGE()+";\n";
	out = out+"L_MESSAGE "+getL_MESSAGE()+";";
	out = out+"T_TRAIN "+getT_TRAIN()+";";
	if(getNID_ENGINE()){
		out = out+"NID_ENGINE "+getNID_ENGINE()+";";
	}
	if(pkgcd1)
		out= out+get_pacchettoCommandData()->ToString();

	if( pkgMP)
		out= out+get_pacchettoMissionPlan()->ToString();
	if(pgkPres)
		out= out+get_pacchettoPresentazione()->ToString();
	 if(pkgStatoATC)
		 out= out+get_pacchettoStatoLineaATC()->toPrint();
	if(pkgAck)
		out= out+get_pacchettoAcknowledgement()->ToString();

	return out;

}