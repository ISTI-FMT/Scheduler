#include "AreaCriticaLineare.h"


AreaCriticaLineare::AreaCriticaLineare(List<int> ^lcdb)
{
	cdbs = lcdb;
	treniSinistra = gcnew HashSet<int>();
	treniDestra = gcnew HashSet<int>();
}

bool AreaCriticaLineare::isInside(int trn)
{
	return cdbs->Contains(trn);
}

void AreaCriticaLineare::Reset()
{
	treniSinistra->Clear();
	treniDestra->Clear();
}

bool AreaCriticaLineare::entrataPermessa(int idTreno, int cdb, int tipoEntrata)
{
	bool res = true;
	if (tipoEntrata > 0)
	{
		if (tipoEntrata == 3) //Entrata da sinistra (se il cdb è il primo della lista e non ero già entrato da destra)
		{
			if (treniDestra->Count > 0)
			{
				res = false;
			}
		}
		else if (tipoEntrata == 2) //Entrata da sinistra (se il cdb è l'ultimo della lista e non ero già entrato da destra)
		{
			if (treniSinistra->Count > 0)
			{
				res = false;
			}
		}
	}
	return res;
}

void AreaCriticaLineare::entrata(int idTreno, int cdb, int tipoEntrata)
{
	if (tipoEntrata > 0)
	{
		if (tipoEntrata == 3) //entrata da sinistra
		{
			if (!treniSinistra->Contains(idTreno))
			{
				treniSinistra->Add(idTreno);
			}
		}
		else if (tipoEntrata == 2) //entrata da destra
		{
			if (!treniDestra->Contains(idTreno))
			{
				treniDestra->Add(idTreno);
			}
		}
	}
	else //sto entrando in un cdb che non è di questa area. Rimuovo il treno
	{
		if (tipoEntrata == -3 && treniSinistra->Contains(idTreno))
		{
			treniSinistra->Remove(idTreno);
		}
		else if (tipoEntrata == -2 && treniDestra->Contains(idTreno))
		{
			treniDestra->Remove(idTreno);
		}
	}
}
