#include "TrenoFermate.h"


TrenoFermate::TrenoFermate(int id)
{
	idTreno = id;
}

// funzione di utilità che confronta due orari. 
// La funzione ritorna 1 se il primo orario è maggiore del secondo; -1 se il primo orario è minore del secondo; 0 se 
// i due orari sono uguali.
int TrenoFermate::confrontaTempi(tm &orario1, tm &orario2)
{
	// confronto le ore
	if(orario1.tm_hour > orario2.tm_hour)
		return 1;
	else if(orario1.tm_hour < orario2.tm_hour)
		return -1;
	// se le ore sono uguali
	else {
		// confronto i minuti
		if(orario1.tm_min > orario2.tm_min)
			return 1;
		else if(orario1.tm_min < orario2.tm_min)
			return -1;
		// se i minuti sono uguali
		else {
			// confronto i secondi
			if(orario1.tm_sec > orario2.tm_sec)
				return 1;
			else if(orario1.tm_sec < orario2.tm_sec)
				return -1;
			// se i secondi sono uguali i due orari sono uguali
			else
				return 0;
		}
	}
}

// funzione che permette l'inserimento di una nuova fermata della tabella orario del treno in questione.
// le fermate sono mantenute in ordine crescente di orario partenza
// alla funzione viene passato per riferimento un oggetto di tipo Fermata, che deve essere stato 
// precedentemente correttamente istanziato.
void TrenoFermate::aggiungiFermata(Fermata &stop)
{
	// scorro tutta la lista finchè non sono arrivato alla fine oppure finchè non ho trovato una fermata che ha 
	// orario di partenza maggiore rispetto alla fermata che devo inserire.
	std::list<Fermata>::iterator it=fermate.begin();
	while(it != fermate.end() && confrontaTempi((*it).getOrarioPartenza(), stop.getOrarioPartenza()) == -1)
		++it;
	// se sono uscito dal for perchè sono arrivato alla fine della lista
	if(it == fermate.end())
		// inserisco in coda alla lista
		fermate.push_back(stop);
	else
		fermate.insert(it, stop);
}

TrenoFermate::~TrenoFermate()
{
	// scorro tutta la lista...
	for (std::list<Fermata>::iterator it=fermate.begin(); it != fermate.end(); ++it)
		// ...e cancelo tutti gli elementi uno alla volta
		fermate.erase(it);
}