#include "AreaCriticaLineare.h"


AreaCriticaLineare::AreaCriticaLineare(List<int> ^lcdb)
{
	listaCdb = lcdb;
}

bool AreaCriticaLineare::entrataPermessa(int idTreno, int cdb, AreaCriticaDirezione direzione)
{
	return false;
}

void AreaCriticaLineare::entrata(int idTreno, AreaCriticaDirezione direzione)
{

}

void AreaCriticaLineare::uscita(int idTreno, AreaCriticaDirezione direzione)
{

}