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

/*Utilizzo questa classe per creare serializzare deserializzare i messaggi specificando
i pacchetti da inserire nel messaggio*/

//questa classe rappresenta un messaggio cosi come definito nei documenti di specifica
//e contiene i metodi per serializzare e desirializzare un messaggio

enum  MessATC{ StatoLineaATC = 11,  FaultReportingATC = 12 };
enum  MessIXL{ StatoLineaIXL = 1,  FaultReportingIXL = 211 , ComandoItinerari = 10, ComandoBlocco=231};
enum  MessATO{ MissionPlan = 100,  FaultReportingATO = 113, UnconditionCommand=101, Acknol=110,Presentation=115 };
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

public:
	Messaggi(void);


	void setNID_MESSAGE(int N);
	int getNID_MESSAGE(){return NID_MESSAGE;};
	void setL_MESSAGE(int N){L_MESSAGE = N;};
	int getL_MESSAGE(){return L_MESSAGE;};
	void setT_TIME(int N){T_TIME = N;};
	int getT_TIME(){return T_TIME;};

	void setNID_ENGINE(int N){NID_ENGINE = N;};
	int getNID_ENGINE(){return NID_ENGINE;};

	void set_pacchettoEnd(){pkgEnd = gcnew pacchettoEnd;};
	pacchettoEnd ^ get_pacchettoEnd(){return pkgEnd;};

	void set_pacchettoStatoScudetti(){pkgStatoScudetti = gcnew pachettoStatoScudetti;};
	pachettoStatoScudetti^ get_pacchettoStatoScudetti(){return pkgStatoScudetti;};

	void set_pacchettoComandoItinerari(){pkgComandoItinerario = gcnew pacchettoComandoItinerari;};
	pacchettoComandoItinerari^ get_pacchettoComandoItinerari(){return pkgComandoItinerario;};

	void set_pacchettoComandoBlocco(){pkgComandoBlocco = gcnew pacchettoComandoBlocco;};
	pacchettoComandoBlocco^ get_pacchettoComandoBlocco(){return pkgComandoBlocco;};

	void set_pacchettoFaultReporting() {pkgFaultData = gcnew pacchettoFaultData;}
	pacchettoFaultData^ get_pacchettoFaultReporting(){return pkgFaultData;}

	void set_pacchettoStatoLineaIXL() {pkgStatoLineaIXL = gcnew pacchettoStatoLineaIXL;}
	pacchettoStatoLineaIXL ^get_pacchettoStatoLineaIXL(){return pkgStatoLineaIXL;}

	void set_pacchettoPositionDataATC() {pkgPositionDataATC = gcnew pacchettoPositionDataATC;}
	pacchettoPositionDataATC ^get_pacchettoPositionDataATC(){return pkgPositionDataATC;}

	void set_pacchettoStatoItinerari() {pkgStatoItinerari = gcnew pacchettoStatoItinerario;}
	pacchettoStatoItinerario^ get_pacchettoStatoItinerario(){return pkgStatoItinerari;}

	void set_pacchettoStatoSegnali() {pkgStatoSegnali = gcnew pacchettoStatoSegnali;}
	pacchettoStatoSegnali ^get_pacchettoStatoSegnali(){return pkgStatoSegnali;}

	void set_pacchettoStatoBlocco() {pkgStatoBlocco = gcnew pacchettoStatoBlocco;}
	pacchettoStatoBlocco ^get_pacchettoStatoBlocco(){return pkgStatoBlocco;}

	void set_pacchettoCommandData(){ pkgcd1 = gcnew pacchettoCommandData;};
	pacchettoCommandData^ get_pacchettoCommandData(){ return pkgcd1;};

	void set_pacchettoMissionData(){ pkgMP = gcnew pacchettoMissionData;};
	pacchettoMissionData^ get_pacchettoMissionData(){ return pkgMP;};

	void set_pacchettoPresentazione(){ pgkPres = gcnew pacchettopresentazione;};
	pacchettopresentazione^ get_pacchettoPresentazione(){ return pgkPres;};

	//void set_pacchettoStatoLineaATC(){ pkgStatoATC = gcnew pacchettostatolineaatc;};
	//pacchettostatolineaatc^ get_pacchettoStatoLineaATC(){ return pkgStatoATC;};

	void set_pacchettoAcknowledgement(){ pkgAck = gcnew pacchettoAcknowledgement;};
	pacchettoAcknowledgement^ get_pacchettoAcknowledgement(){ return pkgAck;};

	void serialize(array<Byte>^buffer);
	

	array<System::Byte>^ serialize();
	void deserialize(array<Byte>^buffer);

	int getSize();

	virtual System::String ^ToString() override;
};

