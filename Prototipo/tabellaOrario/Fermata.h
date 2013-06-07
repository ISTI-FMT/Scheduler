#pragma once

#include <time.h>
#include <iostream>
using namespace std;
using namespace System;

const int noApertura = 0;
const int aperturaTrenoDx = 1;
const int aperturaTrenoSx = 2;
const int aperturaTrenoDxSx = 3;
const int aperturaTrenoBanchinaDx = 4;
const int aperturaTrenoBanchinaSx = 5;
const int aperturaTrenoBanchinaDxSx = 6;

/*
Questa classe è utilizzata dalla classe TrenoFermate per gestire le fermate di un singolo treno.
Un oggetto di tipo fermata rappresenta una fermata di un treno
*/
// Commento inutile
ref class Fermata
{
	int idStazione;
	String ^nameStazione;
	double orarioArrivo;
	double orarioPartenza;
	double tempoMinimoAperturaPorte;
	int binarioProgrammato;
	int latoAperturaPorte;

	int iditinerarioentrata;
	String ^nameitinerarioentrata;
	int iditinerariouscita;
	String ^nameitinerariouscita;

	//ostream& operator<<(ostream &out, const Fermata &stop);
public:
	Fermata(void);
	// Funzioni per la manipolazione (set e get) dell'id della stazione
	void setIdStazione(int id){idStazione = id;};
	int getIdStazione(){return idStazione;};
	void setnameStazione(String ^name){nameStazione = name;};
	String^ getnameStazione(){return nameStazione;};
	// Funzioni per la manipolazione (set e get) dell'orario di arrivo
	void setOrarioArrivo(double orario){orarioArrivo = orario;};
	double getOrarioArrivo(){return orarioArrivo;};
	// Funzioni per la manipolazione (set e get) dell'orario di partenza
	void setOrarioPartenza(double orario){orarioPartenza = orario;};
	double getOrarioPartenza(){return orarioPartenza;};
	// Funzioni per la manipolazione (set e get) del tempo minimo di apertura porte
	void settempoMinimoAperturaPorte(double tempo){tempoMinimoAperturaPorte = tempo;};
	double gettempoMinimoAperturaPorte(){return tempoMinimoAperturaPorte;};
	// Funzioni per la manipolazione del binario programmato
	void setBinarioProgrammato(int binario){binarioProgrammato = binario;};
	int getBinarioProgrammato(){return binarioProgrammato;};
	// Funzioni per la manipolazione del tempo di apertura delle porte
	void setLatoAperturaPorte(int lato){latoAperturaPorte = lato;};
	int getLatoAperturaPorte(){return latoAperturaPorte;};

	bool isPassante();

	void setIditinerarioEntrata(int id){iditinerarioentrata = id;};
	int getIditinerarioEntrata(){return iditinerarioentrata;};
	void setnameitinerarioEntrata(String ^name){nameitinerarioentrata = name;};
	String^ getnameitinerarioEntrata(){return nameitinerarioentrata;};

	void setIditinerarioUscita(int id){iditinerariouscita = id;};
	int getIditinerarioUscita(){return iditinerariouscita;};
	void setnameitinerarioUscita(String ^name){nameitinerariouscita = name;};
	String^ getnameitinerarioUscita(){return nameitinerariouscita;};


	virtual System::String^ ToString() override;
};

