#include "AreaCriticaCircolare.h"


AreaCriticaCircolare::AreaCriticaCircolare(List<int> ^listaCdb, int limite)
{
	this->cdbs = gcnew HashSet<int> ();

	for(int i = 0; i < listaCdb->Count; i++)
	{
		cdbs->Add(listaCdb[i]);
	}

	this->limite = limite;
}

bool AreaCriticaCircolare::entrataPermessa(int idTreno, int cdb, AreaCriticaDirezione direzione)
{
	return false;
}

void AreaCriticaCircolare::entrata(int idTreno, AreaCriticaDirezione direzione)
{

}

void AreaCriticaCircolare::uscita(int idTreno, AreaCriticaDirezione direzione)
{

}
