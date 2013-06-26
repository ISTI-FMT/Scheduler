#include "Messaggi.h"
#include "utility.h"


Messaggi::Messaggi(void)
{
	NID_MESSAGE = 0;
	L_MESSAGE = 0;
	T_TIME = 0;
	NID_ENGINE=0;
}

void Messaggi::setNID_MESSAGE(int N){
	NID_MESSAGE = N;
	switch (N)
	{
	case 200 : {set_pacchettoMissionPlan();break;}
	case 201 : { set_pacchettoCommandData();break;}
	case 215 : { set_pacchettoPresentazione();break;}
	case 1 : {set_pacchettoStatoLineaATC();break;}
	case 210 :{set_pacchettoAcknowledgement();break;}
	case 101: { set_pacchettoStatoLineaIXL(); 
		set_pacchettoStatoItinerari(); 
		set_pacchettoStatoSegnali(); 
		set_pacchettoStatoBlocco(); 
		set_pacchettoEnd(); break;}
	case 102: {set_pacchettoFaultReporting(); break;}
	case 110: {set_pacchettoComandoItinerari(); set_pacchettoEnd(); break;}
	case 111: {set_pacchettoComandoBlocco(); set_pacchettoEnd(); break;}		
	default:
		break;
	}


};

void Messaggi::serialize(byte *buffer)
{
	utility::push(buffer, NID_MESSAGE, 8, 0);
	setL_MESSAGE(getSize());
	utility::push(buffer, L_MESSAGE, 11, 8);
	utility::push(buffer, T_TIME, 32, 19);
	int N = NID_MESSAGE;
	int offset = 0;
	switch (N)
	{
	case 200 : {get_pacchettoMissionPlan()->serializeMissionPlanPkt(buffer);
		break;}
	case 201 : {get_pacchettoCommandData()->serializepacchettoCommandData(buffer);
		break;}
	case 215 : {utility::push(buffer, NID_ENGINE, 24, 51);
		get_pacchettoPresentazione()->serialize(buffer);
		break;}
	case 1 : {get_pacchettoStatoLineaATC()->serialize(buffer);
		break;}
	case 210 :{utility::push(buffer, NID_ENGINE, 24, 51);
		get_pacchettoAcknowledgement()->serialize(buffer);
		break;}
	case 101: {offset += 51; 
		get_pacchettoStatoLineaIXL()->serialize(buffer); 
		offset += get_pacchettoStatoLineaIXL()->getSize(); 
		get_pacchettoStatoItinerario()->serialize(buffer, offset);
		offset += get_pacchettoStatoItinerario()->getSize();
		get_pacchettoStatoSegnali()->serialize(buffer, offset);
		offset += get_pacchettoStatoSegnali()->getSize();
		get_pacchettoStatoBlocco()->serialize(buffer, offset);
		offset += get_pacchettoStatoBlocco()->getSize();
		get_pacchettoEnd()->serialize(buffer, offset);
		break;}
	case 102: {get_pacchettoFaultReporting()->serialize(buffer); 
		break;}
	case 110: { offset += 51;
		get_pacchettoComandoItinerari()->serialize(buffer); 
		offset += get_pacchettoComandoItinerari()->getSize();
		get_pacchettoEnd()->serialize(buffer, offset);
		break;}
	case 111: { offset += 51;
		get_pacchettoComandoBlocco()->serialize(buffer); 
		offset += get_pacchettoComandoBlocco()->getSize();
		get_pacchettoEnd()->serialize(buffer, offset);
		break;}


	default:
		break;
	}

}

array<System::Byte>^ Messaggi::serialize(){
	array<Byte>^bytez = gcnew array<Byte>(getSize());
	int len=getSize();
	byte *buffer = new byte[len];
	for(int i = 0; i < len; ++i)
		buffer[i] = 0;
	serialize(buffer);

	for(int i = 0; i < len; ++i)
		bytez[i] = buffer[i];

	return bytez;
}

void Messaggi::deserialize(byte *buffer)
{
	NID_MESSAGE= utility::pop(buffer, 8, 0);
	L_MESSAGE=utility::pop(buffer,11, 8);
	T_TIME=utility::pop(buffer, 32, 19);
	int offset = 0;
	switch (NID_MESSAGE)
	{
	case 200 : {set_pacchettoMissionPlan();
		pkgMP->deserializeMissionPlanPkt(buffer);
		break;

			   }
	case 201 : {set_pacchettoCommandData();
		pkgcd1->deserializepacchettoCommandData(buffer);
		break;

			   }

	case 215 : {NID_ENGINE = utility::pop(buffer, 24, 51);
		set_pacchettoPresentazione();
		pgkPres->deserialize(buffer);
		break;

			   }

	case 1 : {set_pacchettoStatoLineaATC();
		pkgStatoATC->deserialize(buffer);
		break;
			 }

	case 210 : {NID_ENGINE = utility::pop(buffer, 24, 51);
		set_pacchettoAcknowledgement();
		pkgAck->deserialize(buffer);
		break;
			   }

	case 101: {offset += 51; 
		set_pacchettoStatoLineaIXL();
		get_pacchettoStatoLineaIXL()->deserialize(buffer); 
		offset += get_pacchettoStatoLineaIXL()->getSize(); 
		set_pacchettoStatoItinerari();
		get_pacchettoStatoItinerario()->deserialize(buffer, offset);
		offset += get_pacchettoStatoItinerario()->getSize();
		set_pacchettoStatoSegnali();
		get_pacchettoStatoSegnali()->deserialize(buffer, offset);
		offset += get_pacchettoStatoSegnali()->getSize();
		set_pacchettoStatoBlocco();
		get_pacchettoStatoBlocco()->deserialize(buffer, offset);
		offset += get_pacchettoStatoBlocco()->getSize();
		set_pacchettoEnd();
		get_pacchettoEnd()->deserialize(buffer, offset);
		break;}
	case 102: {get_pacchettoFaultReporting()->deserialize(buffer); 
		break;}
	case 110: { offset += 51;
		set_pacchettoComandoItinerari();
		get_pacchettoComandoItinerari()->deserialize(buffer); 
		offset += get_pacchettoComandoItinerari()->getSize();
		set_pacchettoEnd();
		get_pacchettoEnd()->deserialize(buffer, offset);
		break;}
	case 111: { offset += 51;
		set_pacchettoComandoBlocco();
		get_pacchettoComandoBlocco()->deserialize(buffer); 
		offset += get_pacchettoComandoBlocco()->getSize();
		set_pacchettoEnd();
		get_pacchettoEnd()->deserialize(buffer, offset);
		break;}

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
	out = out+"T_TRAIN "+getT_TIME()+";";
	if(getNID_ENGINE()>0){
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

	if(pkgStatoLineaIXL)
		out= out+get_pacchettoStatoLineaIXL()->ToString();
	if(pkgStatoItinerari)
		out= out+get_pacchettoStatoItinerario()->ToString();
	if(pkgStatoSegnali)
		out= out+get_pacchettoStatoSegnali()->ToString();
	if(pkgFaultData)
		out= out+get_pacchettoFaultReporting()->ToString();
	if(pkgStatoBlocco)
		out= out+get_pacchettoStatoBlocco()->ToString();
	if(pkgComandoItinerario)
		out= out+get_pacchettoComandoItinerari()->ToString();
	if(pkgComandoBlocco)
		out= out+get_pacchettoComandoBlocco()->ToString();
	if(pkgEnd)
		out= out+get_pacchettoEnd()->ToString();





	return out;

}

int Messaggi::getSize(){

		// 51 bit per l'header 
		//24 di engine dove serve
		int len =51;
		switch (NID_MESSAGE)
		{
		case 200 : {len+=pkgMP->getSize();break;}
		case 201 : {len+=pkgcd1->getSize();break;}
		case 215 : {len+=24+pgkPres->getSize();break;}
		case 1 : {len+=pkgStatoATC->getSize();break;}
		case 210 :{len+=24+pkgAck->getSize();break;}
		case 101: {len += pkgStatoLineaIXL->getSize() + pkgStatoItinerari->getSize() + pkgStatoSegnali->getSize() + pkgStatoBlocco->getSize() + pkgEnd->getSize(); break;}
		case 102: {len += pkgFaultData->getSize(); break;}
		case 110: {len +=pkgComandoItinerario->getSize()+ pkgEnd->getSize(); break;}
		case 111: {len +=pkgComandoBlocco->getSize()+ pkgEnd->getSize(); break;}
		default: break;
		}
		int size = (len/8)+1;
		return size ;
	};