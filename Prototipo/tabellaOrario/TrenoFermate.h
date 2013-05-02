#pragma once

#include "Fermata.h"

#using <System.dll>
using namespace System::Collections::Generic;

/*
Questa classe � utilizzata dalla tabella orario per gestire tutte le fermate di un treno.
Un oggetto di tipo fermata rappresenta una fermata di un treno.
*/
ref class TrenoFermate
{   
	int idTreno;
	List<Fermata^> ^fermate;
	
	// funzione di utilit� che confronta due orari. 
	// La funzione ritorna 1 se il primo orario � maggiore del secondo; -1 se il primo orario � minore del secondo; 0 se 
	// i due orari sono uguali.
	// int confrontaTempi(tm &orario1, tm &orario2);
	// friend ostream& operator<<(ostream& out, TrenoFermate &treno);
public:
	TrenoFermate(int id);
	void setIdTreno(int id){idTreno = id;};
	int getIdTreno(){return idTreno;};
	// funzione che permette l'inserimento di una nuova fermata della tabella orario del treno in questione.
	// le fermate sono mantenute in ordine crescente di orario partenza
	// alla funzione viene passato per riferimento un oggetto di tipo Fermata, che deve essere stato 
	// precedentemente correttamente istanziato.
	void aggiungiFermata(Fermata ^stop);
	// funzione che restituisce un riferimento alla lista delle fermate del treno
	List<Fermata^>^ getListaFermate(){return fermate;};
};
