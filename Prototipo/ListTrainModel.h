#pragma once
#include "ilisttrainmodel.h"

public ref class ListTrainModel : public IListTrainModel
{
	System::Collections::Generic::List<Train^> ^ListSortedTrains;
public:
	ListTrainModel(void);
	virtual void Add(Train^ train);
	virtual System::Collections::Generic::List<Train^> ^getList();
	virtual void Sort();
	virtual void NextIt(Train ^key);
	virtual void changePrior(Train ^key, int newprior);
};

