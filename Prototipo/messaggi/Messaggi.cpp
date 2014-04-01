#include "Messaggi.h"
#include "utility.h"
#include "..//logger//Logger.h"
#define TRACE
Messaggi::Messaggi(void)
{
	NID_MESSAGE = 0;
	setTime();

	L_MESSAGE = 0;
	setNID_ENGINE(0);
}

Messaggi::Messaggi(MessageID NID)
{
	setNID_MESSAGE((int)NID);
	setTime();
	L_MESSAGE = 0;
	setNID_ENGINE(0);
}


void Messaggi::setTime()
{
	DateTime orarioSupporto3 = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
	TimeSpan ^sinceMidnight =  DateTime::Now - orarioSupporto3;
	T_TIME = (int)sinceMidnight->TotalSeconds/30;
}

void Messaggi::setNID_MESSAGE(int N){
	NID_MESSAGE = N;
	switch (N)
	{
	case MessageID::MissionPlan : {set_pacchettoMissionData();break;}
	case MessageID::UnconditionCommand : { set_pacchettoCommandData();break;}
	case MessageID::Presentation : { set_pacchettoPresentazione();break;}
	case MessageID::StatoLineaATC : {set_pacchettoPositionDataATC(); 
		//set_pacchettoEnd();
		break;}
	case MessageID::Acknol :{set_pacchettoAcknowledgement();break;}
	case MessageID::StatoLineaIXL: { set_pacchettoStatoLineaIXL();
		//set_pacchettoStatoItinerari();
		set_pacchettoStatoSegnali();
		set_pacchettoStatoBlocco();
		set_pacchettoEnd();
		break;}
	case MessageID::FaultReportingIXL: {set_pacchettoFaultReporting(PacchettoID::FaultDataIXL); break;}
	case MessageID::ComandoItinerari: {set_pacchettoComandoItinerari(); set_pacchettoEnd(); break;}
	case MessageID::ComandoBlocco: {set_pacchettoComandoBlocco(); set_pacchettoEnd(); break;}
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
	case MessageID::MissionPlan : {
		offset += 51;
		get_pacchettoMissionData()->serialize(buffer, offset);
		break;}
	case MessageID::UnconditionCommand : {
		offset += 51;
		get_pacchettoCommandData()->serialize(buffer, offset);
		break;}
	case MessageID::Presentation : {
		offset += 51;
		utility::push(buffer, NID_ENGINE, 24, 51);
		offset += 24;
		get_pacchettoPresentazione()->serialize(buffer, offset);
		break;}
	case MessageID::StatoLineaATC : 
		{
			offset += 51;
			get_pacchettoPositionDataATC()->serialize(buffer, offset);
			//offset += get_pacchettoPositionDataATC()->getSize();
			//get_pacchettoEnd()->serialize(buffer, offset);
			break;}
	case MessageID::Acknol :{
		offset += 51;
		utility::push(buffer, NID_ENGINE, 24, 51);
		offset += 24;
		get_pacchettoAcknowledgement()->serialize(buffer, offset);
		break;}
	case MessageID::StatoLineaIXL: {
		offset += 51;
		get_pacchettoStatoLineaIXL()->serialize(buffer, offset);
		offset += get_pacchettoStatoLineaIXL()->getSize();
		//get_pacchettoStatoItinerario()->serialize(buffer, offset);
		//offset += get_pacchettoStatoItinerario()->getSize();
		get_pacchettoStatoSegnali()->serialize(buffer, offset);
		offset += get_pacchettoStatoSegnali()->getSize();
		get_pacchettoStatoBlocco()->serialize(buffer, offset);
		offset += get_pacchettoStatoBlocco()->getSize();
		get_pacchettoEnd()->serialize(buffer, offset);
		break;}
	case MessageID::FaultReportingIXL: {
		offset += 51;
		get_pacchettoFaultReporting()->serialize(buffer, offset);
		break;}
	case MessageID::ComandoItinerari: { 
		offset += 51;
		get_pacchettoComandoItinerari()->serialize(buffer, offset);
		offset += get_pacchettoComandoItinerari()->getSize();
		get_pacchettoEnd()->serialize(buffer, offset);
		break;}
	case MessageID::ComandoBlocco: { 
		offset += 51;
		get_pacchettoComandoBlocco()->serialize(buffer, offset);
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
	try{
		NID_MESSAGE= utility::pop(buffer, 8, 0);
		L_MESSAGE=utility::pop(buffer,11, 8);
		T_TIME=utility::pop(buffer, 32, 19);
		int offset = 0;
		switch (NID_MESSAGE)
		{
		case MessageID::MissionPlan : {set_pacchettoMissionData();
			offset += 51;
			pkgMP->deserialize(buffer, offset);
			break;

								 }
		case MessageID::UnconditionCommand : {
			offset += 51;
			set_pacchettoCommandData();
			pkgcd1->deserialize(buffer, offset);
			break;

										}

		case MessageID::Presentation : {
			offset += 51;
			NID_ENGINE = utility::pop(buffer, 24, 51);
			offset += 24;
			set_pacchettoPresentazione();
			pgkPres->deserialize(buffer, offset);
			break;

								  }

		case MessageID::StatoLineaATC : {
			offset += 51;
			set_pacchettoPositionDataATC();
			pkgPositionDataATC->deserialize(buffer, offset);
			//offset += get_pacchettoPositionDataATC()->getL_PACKET();// ->getSize();
			//set_pacchettoEnd();
			//get_pacchettoEnd()->deserialize(buffer, offset);
			break;
								   }

		case MessageID::Acknol : {
			offset += 51;
			NID_ENGINE = utility::pop(buffer, 24, 51);
			offset += 24;
			set_pacchettoAcknowledgement();
			pkgAck->deserialize(buffer, offset);
			break;
							}

		case MessageID::StatoLineaIXL: {
			offset += 51;
			set_pacchettoStatoLineaIXL();
			get_pacchettoStatoLineaIXL()->deserialize(buffer, offset);
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
		case MessageID::FaultReportingIXL: {
			offset += 51;
			get_pacchettoFaultReporting()->deserialize(buffer, offset);
			break;}
		case MessageID::ComandoItinerari: { 
			offset += 51;
			set_pacchettoComandoItinerari();
			get_pacchettoComandoItinerari()->deserialize(buffer, offset);
			offset += get_pacchettoComandoItinerari()->getSize();
			set_pacchettoEnd();
			get_pacchettoEnd()->deserialize(buffer, offset);
			break;}
		case MessageID::ComandoBlocco: { 
			offset += 51;
			set_pacchettoComandoBlocco();
			get_pacchettoComandoBlocco()->deserialize(buffer, offset);
			offset += get_pacchettoComandoBlocco()->getSize();
			set_pacchettoEnd();
			get_pacchettoEnd()->deserialize(buffer, offset);
			break;}

		default:
			break;
		}
	}catch(Exception ^e){
#ifdef TRACE
		String ^module = "Errore -Messaggi- Messaggio non deserializzato: "+BitConverter::ToString(buffer);
		Logger::Exception(e,module);
#endif // TRACE
		Console::ForegroundColor = ConsoleColor::Red;
		Console::WriteLine( "-Messaggi- Errore deserializzazione: {0}", e->Message );
		Console::ResetColor();
	}
}



String ^Messaggi::ToString(){

	String ^out = "NID_MESSAGE "+getNID_MESSAGE()+";";
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
	if(pkgPositionDataATC)
		out= out+get_pacchettoPositionDataATC()->toPrint();
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
	try{
		switch (NID_MESSAGE)
		{
		case MessageID::MissionPlan : {len+=pkgMP->getSize();break;}
		case MessageID::UnconditionCommand : {len+=pkgcd1->getSize();break;}
		case MessageID::Presentation : {len+=24+pgkPres->getSize();break;}
		case MessageID::StatoLineaATC : {len+=pkgPositionDataATC->getSize();//+ pkgEnd->getSize();
			break;}
		case MessageID::Acknol :{len+=24+pkgAck->getSize();break;}
		case MessageID::StatoLineaIXL: {len += pkgStatoLineaIXL->getSize() + pkgStatoSegnali->getSize() + pkgStatoBlocco->getSize() + pkgEnd->getSize();//+ pkgStatoItinerari->getSize()
			break;}
		case MessageID::FaultReportingIXL: {len += pkgFaultData->getSize(); break;}
		case MessageID::ComandoItinerari: {len +=pkgComandoItinerario->getSize()+ pkgEnd->getSize(); break;}
		case MessageID::ComandoBlocco: {len +=pkgComandoBlocco->getSize()+ pkgEnd->getSize(); break;}
		default: break;
		}
	}catch(Exception ^e){
		Console::WriteLine("Errore nella Getsize dei messaggi, error: {0}",e->Message);
		return 1345;
	}
	int size = (len/8)+1;
	return size ;
};