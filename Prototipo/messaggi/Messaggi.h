#pragma once
#include "pacchettoCommandData.h"
#include "pacchettoMissionData.h"
#include "pacchettopresentazione.h"

//#include "pacchettostatolineaatc.h"
#include "pacchettoPositionDataATC.h"
#include "pacchettoAcknowledgement.h"
#include "pacchettoStatoItinerario.h"
#include "pacchettoComandoItinerari.h"
#include "pacchettoStatoLineaIXL.h"
#include "pacchettoStatoBlocco.h"
#include "pacchettoComandoBlocco.h"
#include "pacchettoStatoSegnali.h"
#include "pacchettoEnd.h"
#include "pacchettoFaultData.h"
#include "pachettoStatoScudetti.h"

using namespace System;
using namespace System::Globalization;

/*Utilizzo questa classe per creare serializzare deserializzare i messaggi specificando
i pacchetti da inserire nel messaggio*/

//questa classe rappresenta un messaggio cosi come definito nei documenti di specifica
//e contiene i metodi per serializzare e desirializzare un messaggio

enum  MessATC{ StatoLineaATC = 11,  FaultReportingATC = 12 };
enum  MessIXL{ StatoLineaIXL = 1,  FaultReportingIXL = 211 , ComandoItinerari = 10, ComandoBlocco=231};
enum  MessATO{ MissionPlan = 200,  FaultReportingATO = 213, UnconditionCommand=201, Acknol=210,Presentation=215 };
ref class Messaggi
{
	// puntatore all'header per i messaggi ATS/ATO
	//structuredHeader *head;
	unsigned int NID_MESSAGE;
	unsigned int L_MESSAGE;
	unsigned int T_TIME;
	unsigned int NID_ENGINE;
	// puntatori alle strutture dati per i pacchetti ATS/ATO
	pacchettoCommandData ^pkgcd1;
	pacchettoMissionData ^pkgMP;
	pacchettopresentazione ^pgkPres;
	//pacchettostatolineaatc ^pkgStatoATC;
	pacchettoAcknowledgement ^pkgAck;

	// puntatori alle strutture dati per i pacchetti ATS/ATO

	pacchettoStatoLineaIXL ^pkgStatoLineaIXL;
	pacchettoPositionDataATC ^pkgPositionDataATC;

	pacchettoStatoItinerario ^pkgStatoItinerari;
	pacchettoStatoSegnali ^pkgStatoSegnali;
	pacchettoFaultData ^pkgFaultData;
	pacchettoStatoBlocco ^pkgStatoBlocco;
	pachettoStatoScudetti ^pkgStatoScudetti;


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
	void set_pacchettoStatoItinerari() {pkgStatoItinerari = gcnew pacchettoStatoItinerario;}
	void set_pacchettoStatoLineaIXL() {pkgStatoLineaIXL = gcnew pacchettoStatoLineaIXL;}
	void set_pacchettoStatoSegnali() {pkgStatoSegnali = gcnew pacchettoStatoSegnali;}
	void set_pacchettoStatoBlocco() {pkgStatoBlocco = gcnew pacchettoStatoBlocco;}
	void set_pacchettoCommandData(){ pkgcd1 = gcnew pacchettoCommandData;};
	void set_pacchettoPresentazione(){ pgkPres = gcnew pacchettopresentazione;};
	void set_pacchettoMissionData(){ pkgMP = gcnew pacchettoMissionData;};
	void set_pacchettoAcknowledgement(){ pkgAck = gcnew pacchettoAcknowledgement;};
	//void set_pacchettoStatoLineaATC(){ pkgStatoATC = gcnew pacchettostatolineaatc;};

	void serialize(array<Byte>^buffer);

public:
	Messaggi(void);
	Messaggi(int NID_MESSAGE);

	int getNID_MESSAGE(){return NID_MESSAGE;};
	int getL_MESSAGE(){return L_MESSAGE;};
	int getT_TIME(){return T_TIME;};

	void setNID_ENGINE(int N){NID_ENGINE = N;};
	int getNID_ENGINE(){return NID_ENGINE;};


	pacchettoEnd ^ get_pacchettoEnd(){return pkgEnd;};
	pachettoStatoScudetti^ get_pacchettoStatoScudetti(){return pkgStatoScudetti;};
	pacchettoComandoItinerari^ get_pacchettoComandoItinerari(){return pkgComandoItinerario;};
	pacchettoComandoBlocco^ get_pacchettoComandoBlocco(){return pkgComandoBlocco;};
	pacchettoFaultData^ get_pacchettoFaultReporting(){return pkgFaultData;}
	pacchettoStatoLineaIXL ^get_pacchettoStatoLineaIXL(){return pkgStatoLineaIXL;}
	pacchettoPositionDataATC ^get_pacchettoPositionDataATC(){return pkgPositionDataATC;}
	pacchettoStatoItinerario^ get_pacchettoStatoItinerario(){return pkgStatoItinerari;}
	pacchettoStatoSegnali ^get_pacchettoStatoSegnali(){return pkgStatoSegnali;}
	pacchettoStatoBlocco ^get_pacchettoStatoBlocco(){return pkgStatoBlocco;}
	pacchettoCommandData^ get_pacchettoCommandData(){ return pkgcd1;};
	pacchettoMissionData^ get_pacchettoMissionData(){ return pkgMP;};
	pacchettopresentazione^ get_pacchettoPresentazione(){ return pgkPres;};
	//pacchettostatolineaatc^ get_pacchettoStatoLineaATC(){ return pkgStatoATC;};
	pacchettoAcknowledgement^ get_pacchettoAcknowledgement(){ return pkgAck;};

	array<System::Byte>^ serialize();
	void deserialize(array<Byte>^buffer);

	int getSize();

	virtual System::String ^ToString() override;
};

