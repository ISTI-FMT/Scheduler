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
	structuredHeader *head;
	// puntatori alle strutture dati per i pacchetti ATS/ATO
	pacchettoCommandData *pkgcd1;
	pacchettoMissionPlan *pkgMP;
	pacchettopresentazione *pgkPres;
	pacchettostatolineaatc *pkgStatoATC;
	pacchettoAcknowledgement *pkgAck;

	// puntatori alle strutture dati per i pacchetti ATS/ATO

	pacchettoStatoLineaIXL *pkgStatoLineaIXL;
	pacchettoStatoItinerario *pkgStatoItinerari;
	pacchettoStatoSegnali *pkgStatoSegnali;
	pacchettoFaultData *pkgFaultData;
	pacchettoStatoBlocco *pkgStatoBlocco;
	pacchettoComandoItinerari *pkgComandoItinerario;
	pacchettoComandoBlocco *pkgComandoBlocco;
	pacchettoEnd *pkgEnd;

public:
	Messaggi(void);


	void setNID_MESSAGE(int N){head->NID_MESSAGE = N;
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
	int getNID_MESSAGE(){return head->NID_MESSAGE;};
	void setL_MESSAGE(int N){head->L_MESSAGE = N;};
	int getL_MESSAGE(){return head->L_MESSAGE;};
	void setT_TIME(int N){head->T_TIME = N;};
	int getT_TIME(){return head->T_TIME;};

	void setNID_ENGINE(int N){head->NID_ENGINE = N;};
	int getNID_ENGINE(){return head->NID_ENGINE;};

	void set_pacchettoEnd(){pkgEnd = new pacchettoEnd;};
	pacchettoEnd* get_pacchettoEnd(){return pkgEnd;};

	void set_pacchettoComandoItinerari(){pkgComandoItinerario = new pacchettoComandoItinerari;};
	pacchettoComandoItinerari* get_pacchettoComandoItinerari(){return pkgComandoItinerario;};

	void set_pacchettoComandoBlocco(){pkgComandoBlocco = new pacchettoComandoBlocco;};
	pacchettoComandoBlocco* get_pacchettoComandoBlocco(){return pkgComandoBlocco;};

	void set_pacchettoFaultReporting() {pkgFaultData = new pacchettoFaultData;}
	pacchettoFaultData* get_pacchettoFaultReporting(){return pkgFaultData;}

	void set_pacchettoStatoLineaIXL() {pkgStatoLineaIXL = new pacchettoStatoLineaIXL;}
	pacchettoStatoLineaIXL* get_pacchettoStatoLineaIXL(){return pkgStatoLineaIXL;}

	void set_pacchettoStatoItinerari() {pkgStatoItinerari = new pacchettoStatoItinerario;}
	pacchettoStatoItinerario* get_pacchettoStatoItinerario(){return pkgStatoItinerari;}

	void set_pacchettoStatoSegnali() {pkgStatoSegnali = new pacchettoStatoSegnali;}
	pacchettoStatoSegnali* get_pacchettoStatoSegnali(){return pkgStatoSegnali;}

	void set_pacchettoStatoBlocco() {pkgStatoBlocco = new pacchettoStatoBlocco;}
	pacchettoStatoBlocco* get_pacchettoStatoBlocco(){return pkgStatoBlocco;}

	void set_pacchettoCommandData(){ pkgcd1 = new pacchettoCommandData;};
	pacchettoCommandData* get_pacchettoCommandData(){ return pkgcd1;};

	void set_pacchettoMissionPlan(){ pkgMP = new pacchettoMissionPlan;};
	pacchettoMissionPlan* get_pacchettoMissionPlan(){ return pkgMP;};

	void set_pacchettoPresentazione(){ pgkPres = new pacchettopresentazione;};
	pacchettopresentazione* get_pacchettoPresentazione(){ return pgkPres;};

	void set_pacchettoStatoLineaATC(){ pkgStatoATC = new pacchettostatolineaatc;};
	pacchettostatolineaatc* get_pacchettoStatoLineaATC(){ return pkgStatoATC;};

	void set_pacchettoAcknowledgement(){ pkgAck = new pacchettoAcknowledgement;};
	pacchettoAcknowledgement* get_pacchettoAcknowledgement(){ return pkgAck;};

	void serialize(byte *buffer);
	void deserialize(byte *buff);

	void serialize(array<System::Byte>^bytez);
	void deserialize(array<System::Byte>^bytez);

	int getSize(){
		
		// 51 bit per l'header 
		//24 di engine dove serve
		int len =51;
		switch (head->NID_MESSAGE)
		{
		case 200 : {len+=pkgMP->getSize();break;}
		case 201 : {len+=pkgcd1->getSize();break;}
		case 215 : {len+=24+pgkPres->getSize();break;}
		case 1 : {len+=pkgStatoATC->getSize();break;}
		case 210 :{len+=24+pkgAck->getSize();break;}
		case 101: {len += pkgStatoLineaIXL->getSize() + pkgStatoItinerari->getSize() + pkgStatoSegnali->getSize() + pkgStatoBlocco->getSize() + pkgEnd->getSize(); break;}
		case 102: {len += pkgFaultData->getSize(); break;}
		case 110: {pkgComandoItinerario->getSize(); pkgEnd->getSize(); break;}
		case 111: {pkgComandoBlocco->getSize(); pkgEnd->getSize(); break;}
		default: break;
		}
		int size = (len/8)+1;
		return size ;
	};
	
	virtual System::String ^ToString() override;
};

