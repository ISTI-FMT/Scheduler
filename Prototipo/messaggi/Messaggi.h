#pragma once
#include "pacchettoCommandData.h"
#include "pacchettoMissionData.h"
#include "pacchettopresentazione.h"
#include "pacchettoPositionDataATC.h"
#include "pacchettoAcknowledgement.h"
/*#include "pacchettoStatoItinerario.h"*/
#include "pacchettoComandoItinerari.h"
#include "pacchettoStatoLineaIXL.h"
#include "pacchettoStatoBlocco.h"
#include "pacchettoComandoBlocco.h"
#include "pacchettoStatoSegnali.h"
#include "pacchettoEnd.h"
#include "pacchettoFaultData.h"
/*#include "pachettoStatoScudetti.h"*/

using namespace System;
using namespace System::Globalization;

/*
Rappresenta un messaggio cosi come definito nei documenti di specifica
e contiene i metodi per serializzare e desirializzare un messaggio
*/

public enum class  MessageID : int { StatoLineaATC = 11,  FaultReportingATC = 12, StatoLineaIXL = 1, 
	FaultReportingIXL = 211 , ComandoItinerari = 10, ComandoBlocco=231,MissionPlan = 200,  FaultReportingATO = 213,
	UnconditionCommand=201, Acknol=210,Presentation=215 };

public ref class Messaggi
{
	int NID_MESSAGE;
	int L_MESSAGE;
	int T_TIME;
	int NID_ENGINE;
	
	pacchettoCommandData ^pkgcd1;
	pacchettoMissionData ^pkgMP;
	pacchettopresentazione ^pgkPres;
	pacchettoAcknowledgement ^pkgAck;

	pacchettoStatoLineaIXL ^pkgStatoLineaIXL;
	pacchettoPositionDataATC ^pkgPositionDataATC;

	/*pacchettoStatoItinerario ^pkgStatoItinerari;*/
	pacchettoStatoSegnali ^pkgStatoSegnali;
	pacchettoFaultData ^pkgFaultData;
	pacchettoStatoBlocco ^pkgStatoBlocco;
	/*pachettoStatoScudetti ^pkgStatoScudetti;*/


	pacchettoComandoItinerari ^pkgComandoItinerario;
	pacchettoComandoBlocco ^pkgComandoBlocco;
	pacchettoEnd ^pkgEnd;

private:
	void setL_MESSAGE(int N){L_MESSAGE = N;};
	void setNID_MESSAGE(int N);
	void setTime();

	void set_pacchettoEnd(){pkgEnd = gcnew pacchettoEnd;};
	void set_pacchettoComandoItinerari(){pkgComandoItinerario = gcnew pacchettoComandoItinerari;};
	void set_pacchettoComandoBlocco(){pkgComandoBlocco = gcnew pacchettoComandoBlocco;};
	void set_pacchettoFaultReporting(int ID_PACKET) {pkgFaultData = gcnew pacchettoFaultData(ID_PACKET);}
	void set_pacchettoPositionDataATC() {pkgPositionDataATC = gcnew pacchettoPositionDataATC;}
	/*void set_pacchettoStatoItinerari() {pkgStatoItinerari = gcnew pacchettoStatoItinerario;}*/
	void set_pacchettoStatoLineaIXL() {pkgStatoLineaIXL = gcnew pacchettoStatoLineaIXL;}
	void set_pacchettoStatoSegnali() {pkgStatoSegnali = gcnew pacchettoStatoSegnali;}
	void set_pacchettoStatoBlocco() {pkgStatoBlocco = gcnew pacchettoStatoBlocco;}
	void set_pacchettoCommandData(){ pkgcd1 = gcnew pacchettoCommandData;};
	void set_pacchettoPresentazione(){ pgkPres = gcnew pacchettopresentazione;};
	void set_pacchettoMissionData(){ pkgMP = gcnew pacchettoMissionData;};
	void set_pacchettoAcknowledgement(){ pkgAck = gcnew pacchettoAcknowledgement;};
	/*void set_pacchettoStatoScudetti(){pkgStatoScudetti = gcnew pachettoStatoScudetti;};*/

	void serialize(array<Byte>^buffer);

public:
	Messaggi(void);
	Messaggi(MessageID NID) ;
	

	int getNID_MESSAGE(){return NID_MESSAGE;};
	int getL_MESSAGE(){return L_MESSAGE;};
	int getT_TIME(){return T_TIME;};

	void setNID_ENGINE(int N){NID_ENGINE = N;};
	int getNID_ENGINE(){return NID_ENGINE;};


	pacchettoEnd ^ get_pacchettoEnd(){return pkgEnd;};
	/*pachettoStatoScudetti^ get_pacchettoStatoScudetti(){return pkgStatoScudetti;};*/
	pacchettoComandoItinerari^ get_pacchettoComandoItinerari(){return pkgComandoItinerario;};
	pacchettoComandoBlocco^ get_pacchettoComandoBlocco(){return pkgComandoBlocco;};
	pacchettoFaultData^ get_pacchettoFaultReporting(){return pkgFaultData;}
	pacchettoStatoLineaIXL ^get_pacchettoStatoLineaIXL(){return pkgStatoLineaIXL;}
	pacchettoPositionDataATC ^get_pacchettoPositionDataATC(){return pkgPositionDataATC;}
	/*pacchettoStatoItinerario^ get_pacchettoStatoItinerario(){return pkgStatoItinerari;}*/
	pacchettoStatoSegnali ^get_pacchettoStatoSegnali(){return pkgStatoSegnali;}
	pacchettoStatoBlocco ^get_pacchettoStatoBlocco(){return pkgStatoBlocco;}
	pacchettoCommandData^ get_pacchettoCommandData(){ return pkgcd1;};
	pacchettoMissionData^ get_pacchettoMissionData(){ return pkgMP;};
	pacchettopresentazione^ get_pacchettoPresentazione(){ return pgkPres;};
	pacchettoAcknowledgement^ get_pacchettoAcknowledgement(){ return pkgAck;};

	array<System::Byte>^ serialize();
	void deserialize(array<Byte>^buffer);

	int getSize();
	System::String ^toPrint();
	virtual System::String ^ToString() override;
};

