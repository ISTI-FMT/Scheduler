#pragma once
//#include "IControllerListTrain.h"
#include "ListTrainModel.h"
#include "ListTrainView.h"


ref class ControllerListTrain : public IControllerListTrain
{
	IListTrainView ^view;
	IListTrainModel ^model;
public:
	ControllerListTrain(IListTrainView ^v, IListTrainModel ^m);

	virtual void OnSetTrain(Train^ train);
	virtual void OnNextIt(Train ^key);
	virtual  System::Collections::Generic::List< Train^> ^ getListTrain();
	virtual void OnDelete();
	virtual void changePrior(Train ^key, int newprior);
	virtual void RePaint();
	virtual void Sort();
};

