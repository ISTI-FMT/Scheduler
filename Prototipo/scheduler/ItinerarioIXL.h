#pragma once

const int itinerarioStatoIgnoto = -1;
const int itinerarioStatoNonInAtto = 0;
const int itinerarioStatoInAtto = 1;

ref class ItinerarioIXL
{
	int id;
	int statoItinerario;
public:
	ItinerarioIXL(void);
	ItinerarioIXL(int idItinerario);
	ItinerarioIXL(int idItinerario, int stato);
	void setItinerarioNonInAtto(){statoItinerario = itinerarioStatoInAtto;};
	void setItinerarioInAtto(){statoItinerario = itinerarioStatoInAtto;};
	int getStatoItinerario(){return statoItinerario;};
};

