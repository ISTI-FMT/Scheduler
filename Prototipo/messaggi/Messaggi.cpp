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
	case MessATO::MissionPlan : {set_pacchettoMissionData();break;}
	case MessATO::UnconditionCommand : { set_pacchettoCommandData();break;}
	case MessATO::Presentation : { set_pacchettoPresentazione();break;}
	case MessATC::StatoLineaATC : {set_pacchettoStatoLineaATC();break;}
	case MessATO::Acknol :{set_pacchettoAcknowledgement();break;}
	case MessIXL::StatoLineaIXL: { set_pacchettoStatoLineaIXL(); 
		set_pacchettoStatoItinerari(); 
		set_pacchettoStatoSegnali(); 
		set_pacchettoStatoBlocco(); 
		set_pacchettoEnd(); break;}
	case MessIXL::FaultReportingIXL: {set_pacchettoFaultReporting(); break;}
	case MessIXL::ComandoItinerari: {set_pacchettoComandoItinerari(); set_pacchettoEnd(); break;}
	case MessIXL::ComandoBlocco: {set_pacchettoComandoBlocco(); set_pacchettoEnd(); break;}		
	default:
		break;
	}


};

void Messaggi::serialize(array<Byte>^buffer)
{
	utility::push(buffer, NID_MESSAGE, 8, 0);
	setL_MESSAGE(getSize());
	utility::push(buffer, L_MESSAGE, 11, 8);
	utility::push(buffer, T_TIME, 32, 19);
	int N = NID_MESSAGE;
	int offset = 0;
	switch (N)
	{
	case MessATO::MissionPlan : {get_pacchettoMissionData()->serializeMissionPlanPkt(buffer);
		break;}
	case MessATO::UnconditionCommand : {get_pacchettoCommandData()->serializepacchettoCommandData(buffer);
		break;}
	case MessATO::Presentation : {utility::push(buffer, NID_ENGINE, 24, 51);
		get_pacchettoPresentazione()->serialize(buffer);
		break;}
	case  MessATC::StatoLineaATC : {get_pacchettoStatoLineaATC()->serialize(buffer);
		break;}
	case MessATO::Acknol  :{utility::push(buffer, NID_ENGINE, 24, 51);
		get_pacchettoAcknowledgement()->serialize(buffer);
		break;}
	case MessIXL::StatoLineaIXL: {offset += 51; 
		get_pacchettoStatoLineaIXL()->serialize(buffer); 
		offset += get_pacchettoStatoLineaIXL()->getSize(); 
		//get_pacchettoStatoItinerario()->serialize(buffer, offset);
		//offset += get_pacchettoStatoItinerario()->getSize();
		get_pacchettoStatoSegnali()->serialize(buffer, offset);
		offset += get_pacchettoStatoSegnali()->getSize();
		get_pacchettoStatoBlocco()->serialize(buffer, offset);
		offset += get_pacchettoStatoBlocco()->getSize();
		get_pacchettoEnd()->serialize(buffer, offset);
		break;}
	case MessIXL::FaultReportingIXL: {get_pacchettoFaultReporting()->serialize(buffer); 
		break;}
	case  MessIXL::ComandoItinerari: { offset += 51;
		get_pacchettoComandoItinerari()->serialize(buffer); 
		offset += get_pacchettoComandoItinerari()->getSize();
		get_pacchettoEnd()->serialize(buffer, offset);
		break;}
	case  MessIXL::ComandoBlocco: { offset += 51;
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
	
	serialize(bytez);

	

	return bytez;
}

void Messaggi::deserialize(array<Byte>^buffer)
{
	NID_MESSAGE= utility::pop(buffer, 8, 0);
	L_MESSAGE=utility::pop(buffer,11, 8);
	T_TIME=utility::pop(buffer, 32, 19);
	int offset = 0;
	switch (NID_MESSAGE)
	{
	case MessATO::MissionPlan : {set_pacchettoMissionData();
		pkgMP->deserializeMissionPlanPkt(buffer);
		break;

			   }
	case MessATO::UnconditionCommand : {set_pacchettoCommandData();
		pkgcd1->deserializepacchettoCommandData(buffer);
		break;

			   }

	case MessATO::Presentation : {NID_ENGINE = utility::pop(buffer, 24, 51);
		set_pacchettoPresentazione();
		pgkPres->deserialize(buffer);
		break;

			   }

	case  MessATC::StatoLineaATC  : {set_pacchettoStatoLineaATC();
		pkgStatoATC->deserialize(buffer);
		break;
			 }

	case MessATO::Acknol : {NID_ENGINE = utility::pop(buffer, 24, 51);
		set_pacchettoAcknowledgement();
		pkgAck->deserialize(buffer);
		break;
			   }

	case MessIXL::StatoLineaIXL: {offset += 51; 
		set_pacchettoStatoLineaIXL();
		get_pacchettoStatoLineaIXL()->deserialize(buffer); 
		offset += get_pacchettoStatoLineaIXL()->getL_PACKET();// ->getSize();
		//set_pacchettoStatoItinerari();
		//get_pacchettoStatoItinerario()->deserialize(buffer, offset);
		//offset += get_pacchettoStatoItinerario()->getSize();
		set_pacchettoStatoSegnali();
		get_pacchettoStatoSegnali()->deserialize(buffer, offset);
		offset += get_pacchettoStatoSegnali()->getL_PACKET();// ->getSize();
		
		set_pacchettoStatoBlocco();
		get_pacchettoStatoBlocco()->deserialize(buffer, offset);
		offset += get_pacchettoStatoBlocco()->getL_PACKET();// ->getSize();
		set_pacchettoEnd();
		get_pacchettoEnd()->deserialize(buffer, offset);
		break;}
	case MessIXL::FaultReportingIXL: {get_pacchettoFaultReporting()->deserialize(buffer); 
		break;}
	case  MessIXL::ComandoItinerari: { offset += 51;
		set_pacchettoComandoItinerari();
		get_pacchettoComandoItinerari()->deserialize(buffer); 
		offset += get_pacchettoComandoItinerari()->getSize();
		set_pacchettoEnd();
		get_pacchettoEnd()->deserialize(buffer, offset);
		break;}
	case  MessIXL::ComandoBlocco: { offset += 51;
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
		out= out+get_pacchettoMissionData()->ToString();
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
	if(pkgStatoScudetti)
		out= out+get_pacchettoStatoScudetti()->ToString();
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
		case MessATO::MissionPlan : {len+=pkgMP->getSize();break;}
		case MessATO::UnconditionCommand : {len+=pkgcd1->getSize();break;}
		case MessATO::Presentation : {len+=24+pgkPres->getSize();break;}
		case  MessATC::StatoLineaATC  : {len+=pkgStatoATC->getSize();break;}
		case MessATO::Acknol :{len+=24+pkgAck->getSize();break;}
		case MessIXL::StatoLineaIXL: {len += pkgStatoLineaIXL->getSize() + pkgStatoSegnali->getSize() + pkgStatoBlocco->getSize() + pkgEnd->getSize();//+ pkgStatoItinerari->getSize() 
			break;}
		case MessIXL::FaultReportingIXL: {len += pkgFaultData->getSize(); break;}
		case  MessIXL::ComandoItinerari: {len +=pkgComandoItinerario->getSize()+ pkgEnd->getSize(); break;}
		case  MessIXL::ComandoBlocco: {len +=pkgComandoBlocco->getSize()+ pkgEnd->getSize(); break;}
		default: break;
		}
		int size = (len/8)+1;
		return size ;
	};