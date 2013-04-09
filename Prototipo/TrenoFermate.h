#pragma once
#include <list>
#include "Fermata.h"
#include <iostream>
using namespace std;

/*
Questa classe è utilizzata dalla tabella orario per gestire tutte le fermate di un treno.
Un oggetto di tipo fermata rappresenta una fermata di un treno.
*/
class TrenoFermate
{
	// id del treno
	int idTreno;
	// lista delle fermate del treno
	std::list<Fermata> fermate;
	// funzione di utilità che confronta due orari. 
	// La funzione ritorna 1 se il primo orario è maggiore del secondo; -1 se il primo orario è minore del secondo; 0 se 
	// i due orari sono uguali.
	int confrontaTempi(tm &orario1, tm &orario2);
	friend ostream& operator<<(ostream& out, TrenoFermate &treno);
public:
	TrenoFermate(int id);
	// funzione che permette l'inserimento di una nuova fermata della tabella orario del treno in questione.
	// le fermate sono mantenute in ordine crescente di orario partenza
	// alla funzione viene passato per riferimento un oggetto di tipo Fermata, che deve essere stato 
	// precedentemente correttamente istanziato.
	void aggiungiFermata(Fermata &stop);
	~TrenoFermate();
};

