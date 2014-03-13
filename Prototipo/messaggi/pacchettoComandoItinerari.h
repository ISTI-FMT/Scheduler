#pragma once
#include "utility.h"
#include "pacchettoBase.h"

/*
Rappresenta le informazioni contenute nel pacchetto Comando Itinerari che l'ATS invia dal IXL nel messaggio di Comando Itinerari
*/
enum  QCmdItinerari { distruzione = 0,  creazione = 2 };

ref class pacchettoComandoItinerari : pacchettoBase
{
	int L_PACKET ;
	int NID_ITIN ;
	int Q_CMDITIN ;
public:
	pacchettoComandoItinerari(void);

	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setNID_ITIN(int N){NID_ITIN = N;};
	int getNID_ITIN(){return NID_ITIN;};
	void setQ_CMDITIN(QCmdItinerari Q){Q_CMDITIN = Q;};
	int getQ_CMDITIN(){return Q_CMDITIN;};

	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;

	~pacchettoComandoItinerari(void);
	virtual System::String ^ToString() override;

};

