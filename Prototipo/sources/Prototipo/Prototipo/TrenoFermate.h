#pragma once
#include <list>
#include "Fermata.h"

/*
Questa classe è utilizzata dalla tabella orario per gestire tutte le fermate di un treno.
Un oggetto di tipo fermata rappresenta una fermata di un treno
*/
class TrenoFermate
{
	int idTreno;
	std::list<Fermata> fermate;
public:
	TrenoFermate(int id);
};

