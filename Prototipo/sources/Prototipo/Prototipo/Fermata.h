#pragma once

#include <time.h>

enum aperturaPorte {destra, sinistra, destraSinistra, noApertura};

/*
Questa classe è utilizzata dalla classe TrenoFermate per gestire le fermate di un singolo treno.
Un oggetto di tipo fermata rappresenta una fermata di un treno
*/
// Commento inutile
class Fermata
{
	int idStazione;
	tm *orarioArrivo;
	tm *orarioPartenza;
	int binarioProgrammato;
	int tempoAperturaPorte;
	aperturaPorte latoAperturaPorte;

public:
	Fermata(void);
	// Funzioni per la manipolazione (set e get) dell'orario di arrivo
	void setOrarioArrivo(tm orario){*orarioArrivo = orario;};
	void setOrarioArrivo_Ora(int ora){orarioArrivo->tm_hour = ora;};
	void setOrarioArrivo_Minuto(int minuto){orarioArrivo->tm_min = minuto;};
	void setOrarioArrivo_Secondo(int secondo){orarioArrivo->tm_sec = secondo;};
	tm getOrarioArrivo(){return *orarioArrivo;};
	int getOrarioArrivo_Ora(){return orarioArrivo->tm_hour;};
	int getOrarioArrivo_Minuto(){return orarioArrivo->tm_min;};
	int getOrarioArrivo_Secondo(){return orarioArrivo->tm_sec;};
	// Funzioni per la manipolazione (set e get) dell'orario di partenza
	void setOrarioPartenza(tm orario){*orarioPartenza = orario;};
	void setOrarioPartenza_Ora(int ora){orarioPartenza->tm_hour = ora;};
	void setOrarioPartenza_Minuto(int minuto){orarioPartenza->tm_min = minuto;};
	void setOrarioPartenza_Secondo(int secondo){orarioPartenza->tm_sec = secondo;};
	tm getOrarioPartenza(){return *orarioPartenza;};
	int getOrarioPartenza_Ora(){return orarioPartenza->tm_hour;};
	int getOrarioPartenza_Minuto(){return orarioArrivo->tm_min;};
	int getOrarioPartenza_Secondo(){return orarioPartenza->tm_sec;};
	// Funzioni per la manipolazione del binario programmato
	void setBinarioProgrammato(int binario){binarioProgrammato = binario;};
	int getBinarioProgrammato(){return binarioProgrammato;};
	// setTempoAperturaPOrte();
	// Funzioni per la manipolazione del tempo di apertura delle porte
	void setTempoAperturaPorte(int tempo){tempoAperturaPorte = tempo;};
	int getTempoAperturaPorte(){return tempoAperturaPorte;};
	// Funzioni per la manipolazione del tempo di apertura delle porte
	void setLatoAperturaPorte(aperturaPorte lato){latoAperturaPorte = lato;};
	int getLatoAperturaPorte(){return latoAperturaPorte;};
	~Fermata();
};

