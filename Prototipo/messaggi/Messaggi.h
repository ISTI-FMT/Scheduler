#pragma once
#include "struttureDatiMessaggi.h"
#include "pacchettoCommandData.h"
#include "pacchettoMissionPlan.h"
#include "pacchettopresentazione.h"
#include "pacchettostatolineaatc.h"
#include "pacchettoAcknowledgement.h"
#include "pacchettoStatoItinerario.h"
#include "pacchettoComandoItinerari.h"
#include "pacchettoStatoLineaIXL.h"
#include "pacchettoStatoBlocco.h"
#include "pacchettoComandoBlocco.h"
#include "pacchettoStatoSegnali.h"
#include "pacchettoEnd.h"
#include "pacchettoFaultData.h"

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
	pacchettoMissionPlan ^pkgMP;
	pacchettopresentazione ^pgkPres;
	pacchettostatolineaatc ^pkgStatoATC;
	pacchettoAcknowledgement ^pkgAck;

	// puntatori alle strutture dati per i pacchetti ATS/ATO

	pacchettoStatoLineaIXL ^pkgStatoLineaIXL;
	pacchettoStatoItinerario ^pkgStatoItinerari;
	pacchettoStatoSegnali ^pkgStatoSegnali;
	pacchettoFaultData ^pkgFaultData;
	pacchettoStatoBlocco ^pkgStatoBlocco;

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

	void set_pacchettoComandoItinerari(){pkgComandoItinerario = gcnew pacchettoComandoItinerari;};
	pacchettoComandoItinerari^ get_pacchettoComandoItinerari(){return pkgComandoItinerario;};

	void set_pacchettoComandoBlocco(){pkgComandoBlocco = gcnew pacchettoComandoBlocco;};
	pacchettoComandoBlocco^ get_pacchettoComandoBlocco(){return pkgComandoBlocco;};

	void set_pacchettoFaultReporting() {pkgFaultData = gcnew pacchettoFaultData;}
	pacchettoFaultData^ get_pacchettoFaultReporting(){return pkgFaultData;}

	void set_pacchettoStatoLineaIXL() {pkgStatoLineaIXL = gcnew pacchettoStatoLineaIXL;}
	pacchettoStatoLineaIXL ^get_pacchettoStatoLineaIXL(){return pkgStatoLineaIXL;}

	void set_pacchettoStatoItinerari() {pkgStatoItinerari = gcnew pacchettoStatoItinerario;}
	pacchettoStatoItinerario^ get_pacchettoStatoItinerario(){return pkgStatoItinerari;}

	void set_pacchettoStatoSegnali() {pkgStatoSegnali = gcnew pacchettoStatoSegnali;}
	pacchettoStatoSegnali ^get_pacchettoStatoSegnali(){return pkgStatoSegnali;}

	void set_pacchettoStatoBlocco() {pkgStatoBlocco = gcnew pacchettoStatoBlocco;}
	pacchettoStatoBlocco ^get_pacchettoStatoBlocco(){return pkgStatoBlocco;}

	void set_pacchettoCommandData(){ pkgcd1 = gcnew pacchettoCommandData;};
	pacchettoCommandData^ get_pacchettoCommandData(){ return pkgcd1;};

	void set_pacchettoMissionPlan(){ pkgMP = gcnew pacchettoMissionPlan;};
	pacchettoMissionPlan^ get_pacchettoMissionPlan(){ return pkgMP;};

	void set_pacchettoPresentazione(){ pgkPres = gcnew pacchettopresentazione;};
	pacchettopresentazione^ get_pacchettoPresentazione(){ return pgkPres;};

	void set_pacchettoStatoLineaATC(){ pkgStatoATC = gcnew pacchettostatolineaatc;};
	pacchettostatolineaatc^ get_pacchettoStatoLineaATC(){ return pkgStatoATC;};

	void set_pacchettoAcknowledgement(){ pkgAck = gcnew pacchettoAcknowledgement;};
	pacchettoAcknowledgement^ get_pacchettoAcknowledgement(){ return pkgAck;};

	void serialize(byte *buffer);
	void deserialize(byte *buff);

	array<System::Byte>^ serialize();
	void deserialize(array<System::Byte>^bytez);

	int getSize();

	virtual System::String ^ToString() override;
};

