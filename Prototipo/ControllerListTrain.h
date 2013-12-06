#pragma once
#include "ListTrainModel.h"
#include "Train.h"


ref class ControllerListTrain
{
	
	ListTrainModel ^model;
public:
	ControllerListTrain(ListTrainModel ^m);

	virtual void OnSetTrain(Train^ train);
	virtual void OnNextIt(Train ^key);
	virtual  System::Collections::Generic::List< Train^> ^ getListTrain();
	virtual void OnDelete();
	virtual void changePrior(Train ^key, int newprior);
	virtual void RePaint();
	virtual void Sort();
};

