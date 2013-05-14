#pragma once
#include "struttureDatiMessaggi.h"
#include "pacchettoCommandData.h"
#include "pacchettoMissionPlan.h"
#include "pacchettopresentazione.h"
#include "pacchettostatolineaatc.h"
#include "pacchettoAcknowledgement.h"


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

	/*

	Queste classi devono essere create simili a pacchettoMissionPlan e tutte le altre...

	pacchettoStatoLinea *pkgStatoLinea;
	pacchettoStatoItinerario *pkgStatoItinerari;
	pacchettoStatoSegnale *pkgStatoSegnali;
	pacchettoFaultData *pkgFaultData;
	pacchettoComandoItinerario *pkgComandoItinerario;
	pacchettoComandoBlocco *pkgComandoBlocco;
	pacchettoEnd *pkgEnd;
	*/
public:
	Messaggi(void);


	void setNID_MESSAGE(int N){head->NID_MESSAGE = N;
	switch (N)
	{
	case 200 : {set_pacchettoMissionPlan();}
	case 201 : { set_pacchettoCommandData();}
	case 215 : { set_pacchettoPresentazione();}
	case 1 : {set_pacchettoStatoLineaATC();}
	case 210 :{set_pacchettoAcknowledgement();}


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


		default:
			break;
		}
		int size = (len/8)+1;
		return size ;
	};
	
	virtual System::String ^ToString() override;
};

