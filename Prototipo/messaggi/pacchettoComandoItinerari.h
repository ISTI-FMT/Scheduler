#pragma once
#include "utility.h"

/*-----------------------------------------------------------------------------------------------
questa classe rappresenta un Pacchetto per eseguire dei comandi sugli itinerari
L'ATS invia all'IXl messaggi contenenti comandi sugli itinerari
-------------------------------------------------------------------------------------------------*/
enum  typeCmdItinerari { distruzione = 0,  creazione = 2 };

ref class pacchettoComandoItinerari
{
	unsigned int NID_PACKET;
	unsigned int L_PACKET ;
	unsigned int NID_ITIN ;
	unsigned int Q_CMDITIN ;
public:
	pacchettoComandoItinerari(void);

	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setNID_ITIN(int N){NID_ITIN = N;};
	int getNID_ITIN(){return NID_ITIN;};
	void setQ_CMDITIN(int Q){Q_CMDITIN = Q;};
	int getQ_CMDITIN(){return Q_CMDITIN;};

	// funzione che restituisce la dimensione
	int getSize();
	void serialize(byte *buffer);
	void deserialize(byte *buffer);

	~pacchettoComandoItinerari(void);
	virtual System::String ^ToString() override;

};

