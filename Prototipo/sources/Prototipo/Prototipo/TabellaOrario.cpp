#include "TabellaOrario.h"
#using <System.Xml.dll>
#include <iostream>
#include <msclr\marshal_cppstd.h>


TabellaOrario::TabellaOrario(void)
{
}

void TabellaOrario::leggiTabellaOrario(string nomeFile)
{
	// apertura del file
	// lettura del file
	// per ogni treno leggo l'id
	TrenoFermate *treno = new TrenoFermate();
	// per tutte le fermate del treno
	Fermata *stop = new Fermata;
	stop->setIdStazione();
	stop->setOrarioArrivo_Ora();
	stop->setOrarioArrivo_Minuto();
	stop->setOrarioArrivo_Secondo();
	stop->setOrarioPartenza_Ora();
	stop->setOrarioPartenza_Minuto();
	stop->setOrarioPartenza_Secondo();
	stop->setBinarioProgrammato();
	stop->setTempoAperturaPorte();
	stop->setLatoAperturaPorte();
	treno->aggiungiFermata(*stop);
	// dopo aver finito il processing di un treno
	aggiungiTreno(*treno);
}

void TabellaOrario::aggiungiTreno(TrenoFermate &treno)
{
	tabella.push_front(treno);
}

TabellaOrario::~TabellaOrario()
{
	// scorro tutta la lista...
	for (std::list<TrenoFermate>::iterator it=tabella.begin(); it != tabella.end(); ++it)
		// ...e cancelo tutti gli elementi uno alla volta
		tabella.erase(it);
}
