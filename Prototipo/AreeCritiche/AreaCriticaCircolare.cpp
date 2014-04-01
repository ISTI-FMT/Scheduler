#include "AreaCriticaCircolare.h"


AreaCriticaCircolare::AreaCriticaCircolare(List<int> ^listaCdb, int limite)
{
	this->cdbs = gcnew HashSet<int> ();
	treni = gcnew HashSet<int>();

	for(int i = 0; i < listaCdb->Count; i++)
	{
		cdbs->Add(listaCdb[i]);
	}

	this->limite = limite;
}

bool AreaCriticaCircolare::entrataPermessa(int idTreno, int cdb, int tipoEntrata)
{
	bool res = true;
	//l'ingresso è negato se:
	//- il cdb è uno di quelli dell'area
	//- il treno non è già dentro l'area
	//- l'area ha già il numero massimo di treni
	if (tipoEntrata == 1 && !treni->Contains(idTreno))
	{
		if (treni->Count >= limite)
		{
			res = false;
		}
	}
	return res;
}

void AreaCriticaCircolare::entrata(int idTreno, int cdb, int tipoEntrata)
{
	if (tipoEntrata == 1)
	{
		if (!treni->Contains(idTreno))
		{
			treni->Add(idTreno);
		}
	}
	else if(tipoEntrata == -1)
	{
		if (treni->Contains(idTreno))
		{
			treni->Remove(idTreno);
		}
	}
}
