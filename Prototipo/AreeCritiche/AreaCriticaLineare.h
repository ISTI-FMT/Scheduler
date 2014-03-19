#pragma once
#include "areacritica.h"
public ref class AreaCriticaLineare :
public AreaCritica
{
private:
	List<int>^ cdbs;
	HashSet<int>^ treniSinistra;
	HashSet<int>^ treniDestra;
public:
	AreaCriticaLineare(List<int> ^listaCdb);
	virtual bool entrataPermessa(int idTreno, int cdb) override;
	virtual void entrata(int idTreno, int cdb) override;
};

