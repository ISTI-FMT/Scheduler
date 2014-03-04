#include "AreaCriticaLineare.h"


AreaCriticaLineare::AreaCriticaLineare(List<int> ^lcdb)
{
	cdbs = lcdb;
	treniSinistra = gcnew HashSet<int>();
	treniDestra = gcnew HashSet<int>();
}

bool AreaCriticaLineare::entrataPermessa(int idTreno, int cdb)
{
	bool res = true;
	if (cdbs->Contains(cdb))
	{
		if (cdbs[0] == cdb) //entrata da sinistra
		{
			if (!treniSinistra->Contains(idTreno))
			{
				if (treniDestra->Count > 0)
				{
					res = false;
				}
			}
		}
		else if (cdbs[cdbs->Count -1] == cdb) //entrata da destra
		{
			if (!treniDestra->Contains(idTreno))
			{
				if (treniSinistra->Count > 0)
				{
					res = false;
				}
			}
		}
	}
	return res;
}

void AreaCriticaLineare::entrata(int idTreno, int cdb)
{
	if (cdbs->Contains(cdb))
	{
		if (cdbs[0] == cdb) //entrata da sinistra
		{
			if (!treniSinistra->Contains(idTreno))
			{
				treniSinistra->Add(idTreno);
			}
		}
		else if (cdbs[cdbs->Count -1] == cdb) //entrata da destra
		{
			if (!treniDestra->Contains(idTreno))
			{
				treniDestra->Add(idTreno);
			}
		}
	}
	else //sto entrando in un cdb che non è di questa area. Rimuovo il treno
	{
		if (treniSinistra->Contains(idTreno))
		{
			treniSinistra->Remove(idTreno);
		}
		else if (treniDestra->Contains(idTreno))
		{
			treniDestra->Remove(idTreno);
		}
	}
}
