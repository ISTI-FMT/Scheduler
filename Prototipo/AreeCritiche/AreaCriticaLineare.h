#pragma once
#include "areacritica.h"
public ref class AreaCriticaLineare :
public AreaCritica
{
private:
	HashSet<int>^ treniSinistra;
	HashSet<int>^ treniDestra;
public:
	List<int>^ cdbs;
	AreaCriticaLineare(List<int> ^listaCdb);
	virtual bool entrataPermessa(int idTreno, int cdb, int tipoEntrata) override;
	virtual void entrata(int idTreno, int cdb, int tipoEntrata) override;
	virtual bool isInside(int trn) override;
};

