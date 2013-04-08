#pragma once
#include <list>
#include "Fermata.h"

/*
Questa classe � utilizzata dalla tabella orario per gestire tutte le fermate di un treno.
Un oggetto di tipo fermata rappresenta una fermata di un treno.
*/
class TrenoFermate
{
	int idTreno;
	std::list<Fermata> fermate;
	// funzione di utilit� che confronta due orari. 
	// La funzione ritorna 1 se il primo orario � maggiore del secondo; -1 se il primo orario � minore del secondo; 0 se 
	// i due orari sono uguali.
	int confrontaTempi(tm &orario1, tm &orario2);
public:
	TrenoFermate(int id);
	// funzione che permette l'inserimento di una nuova fermata della tabella orario del treno in questione.
	// le fermate sono mantenute in ordine crescente di orario partenza
	// alla funzione viene passato per riferimento un oggetto di tipo Fermata, che deve essere stato 
	// precedentemente correttamente istanziato.
	void aggiungiFermata(Fermata &stop);
	~TrenoFermate();
};

