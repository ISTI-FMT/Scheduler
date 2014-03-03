#pragma once
#include "c:\users\simonedellalonga\projects\prototipo\devel_areecritiche2\scheduler\prototipo\areecritiche\areacritica.h"
ref class AreaCriticaLineare :
public AreaCritica
{
private:
	List<int>^ listaCdb;
public:
	AreaCriticaLineare(List<int> ^listaCdb);
	virtual bool entrataPermessa(int idTreno, int cdb, AreaCriticaDirezione direzione) override;
	virtual void entrata(int idTreno, AreaCriticaDirezione direzione) override;
	virtual void uscita(int idTreno, AreaCriticaDirezione direzione) override;
};

