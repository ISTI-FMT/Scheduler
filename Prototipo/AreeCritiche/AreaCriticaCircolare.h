#pragma once
#include "areacritica.h"

using namespace System::Collections::Generic;

public ref class AreaCriticaCircolare :
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
	virtual bool entrataPermessa(int idTreno, int cdb, int tipoEntrata) override;
	virtual void entrata(int idTreno, int cdb, int tipoEntrata) override;
	virtual bool isInside(int trn) override;
	virtual void Reset() override;
};

