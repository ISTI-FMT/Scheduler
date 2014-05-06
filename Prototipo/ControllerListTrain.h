#pragma once
#include "ListTrainModel.h"
#include "Train.h"

/*rappresenta il controllo nel pattern mvc*/
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
ref class ControllerListTrain
{
	
	ListTrainModel ^model;
public:
	ControllerListTrain(ListTrainModel ^m);

	 void OnSetTrain(Train^ train);
	 void OnNextIt(Train ^key);
	  System::Collections::Generic::List< Train^> ^ getListTrain();
	 void OnDelete();
	 void changePrior(Train ^key, int newprior);
	 void changeStato(Train ^key, StateTrain state);
	 void RePaint();
	 void Sort();
	 void AggiornaOrario(Train ^train, List<Fermata^> ^nuovior);
};

