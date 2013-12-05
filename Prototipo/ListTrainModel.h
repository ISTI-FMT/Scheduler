#pragma once
#include "ilisttrainmodel.h"

public ref class ListTrainModel : public IListTrainModel
{
	System::Collections::Generic::SortedList<KeyListTrain^, Train^> ^ListSortedTrains;
public:
	ListTrainModel(void);
	virtual void Add(KeyListTrain ^key,Train^ train);
	virtual System::Collections::Generic::SortedList<KeyListTrain^, Train^> ^getList();
    virtual void set(KeyListTrain ^key,List<Fermata^> ^list);
	virtual void set(KeyListTrain ^key,StateTrain state);
	virtual void NextIt(KeyListTrain ^key);
	virtual void changePrior(KeyListTrain ^key, int newprior);
};

