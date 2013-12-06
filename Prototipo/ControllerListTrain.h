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
	virtual void OnSetTrainI(KeyListTrain ^key,List<Fermata^> ^list);
	virtual void OnSetTrain(KeyListTrain ^key,StateTrain state);
	virtual void OnSetTrain(KeyListTrain ^key,Train^ train);
	virtual void OnNextIt(KeyListTrain ^key);
	virtual  System::Collections::Generic::SortedList<KeyListTrain^, Train^> ^ getListTrain();
	virtual void OnDelete();
	virtual void changePrior(KeyListTrain ^key, int newprior);
	virtual void RePaint();
};

