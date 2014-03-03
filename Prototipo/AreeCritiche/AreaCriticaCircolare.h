#pragma once
#include "c:\users\simonedellalonga\projects\prototipo\devel_areecritiche2\scheduler\prototipo\areecritiche\areacritica.h"

using namespace System::Collections::Generic;

ref class AreaCriticaCircolare :
public AreaCritica
{
private:
	//Numero massimo di treni che possono essere nell'area circolare in un dato momento
	int limite;
	HashSet<int>^ cdbs;
	//Treni presenti nell'area
	HashSet<int>^ treni;
public:
	AreaCriticaCircolare(List<int> ^listaCdb, int limite);
	virtual bool entrataPermessa(int idTreno, int cdb, AreaCriticaDirezione direzione) override;
	virtual void entrata(int idTreno, AreaCriticaDirezione direzione) override;
	virtual void uscita(int idTreno, AreaCriticaDirezione direzione) override;
};

