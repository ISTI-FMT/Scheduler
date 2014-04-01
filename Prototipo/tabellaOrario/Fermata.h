#pragma once
#include "..\FermataType.h"

using namespace System;



/*Utilizzo questa classe per serializzare le informazioni sulle fermate presenti nella tabella orario
Questa classe è utilizzata dalla classe TrenoFermate per gestire le fermate di un singolo treno.
Un oggetto di tipo fermata rappresenta una fermata di un treno
*/

public ref class Fermata  : public IEquatable<Fermata^>
{
	int idStazione;
	String ^nameStazione;
	double orarioArrivo;
	double orarioPartenza;
	double tempoMinimoAperturaPorte;
	int binarioProgrammato;
	FermataType latoAperturaPorte;
	int iditinerarioentrata;
	String ^nameitinerarioentrata;
	int iditinerariouscita;
	String ^nameitinerariouscita;

	//ostream& operator<<(ostream &out, const Fermata &stop);
public:
	Fermata(void);
	Fermata(int i, String ^n,double oa, double op,double tmpa,int bp, FermataType lap,int idie,String ^nie,int idiu,String ^niu){
		idStazione=i;
		nameStazione=n;
		orarioArrivo=oa;
		orarioPartenza=op;
		tempoMinimoAperturaPorte=tmpa;
		binarioProgrammato=bp;
		latoAperturaPorte=lap;

		iditinerarioentrata=idie;
		nameitinerarioentrata=nie;
		iditinerariouscita=idiu;
		nameitinerariouscita=niu;

	}
	Fermata(int i){

		idStazione=i;
		nameStazione = "";
		orarioArrivo = 0;
		orarioPartenza = 0;
		tempoMinimoAperturaPorte = 0;
		binarioProgrammato = 0;
		latoAperturaPorte = FermataType::noApertura;
		iditinerarioentrata=0;
		nameitinerarioentrata="";
		iditinerariouscita=0;
		nameitinerariouscita="";

	}
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
	void setLatoAperturaPorte(FermataType lato){latoAperturaPorte = lato;};
	FermataType getLatoAperturaPorte(){return latoAperturaPorte;};

	bool isPassante();

	void setIditinerarioEntrata(int id){iditinerarioentrata = id;};
	int getIditinerarioEntrata(){return iditinerarioentrata;};
	void setnameitinerarioEntrata(String ^name){nameitinerarioentrata = name;};
	String^ getnameitinerarioEntrata(){return nameitinerarioentrata;};

	void setIditinerarioUscita(int id){iditinerariouscita = id;};
	int getIditinerarioUscita(){return iditinerariouscita;};
	void setnameitinerarioUscita(String ^name){nameitinerariouscita = name;};
	String^ getnameitinerarioUscita(){return nameitinerariouscita;};

	void setOrarioArrivo(DateTime arr);
	void setOrarioPartenza(DateTime orario);

	Fermata ^Clone(){
		return gcnew Fermata(idStazione,nameStazione,orarioArrivo,orarioPartenza,tempoMinimoAperturaPorte,binarioProgrammato,latoAperturaPorte,iditinerarioentrata,nameitinerarioentrata,iditinerariouscita,nameitinerariouscita);
	}

	virtual System::String^ ToString() override;
	virtual bool Equals(Fermata^ otherKey);
};

