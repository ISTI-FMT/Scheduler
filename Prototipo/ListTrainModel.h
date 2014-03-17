#pragma once
#include "Train.h"
#include "Unsubscriber.h"
/*rappresenta il modello dei dati nel patter mvc*/
public ref class ListTrainModel : public IObservable<List<Train^> ^>,IObservable<Train ^>
{
	System::Collections::Generic::List<Train^> ^ListSortedTrains;
	 List<IObserver<List<Train^>^>^> ^observers;
	  List<IObserver<Train^>^> ^observersTrain;
public:
	 

	ListTrainModel(void);
	 void Add(Train^ train);
	 System::Collections::Generic::List<Train^> ^getList();
	 void Sort();
	 bool Contains(Train^ train);
	 bool RemoveElement(Train^ train);
	 void NextIt(Train ^key);
	 void changePrior(Train ^key, int newprior);
	 void changeOrari(Train ^key,  List<Fermata^> ^nuoviorari);
	 void changeState(Train ^key,  StateTrain state);
	 Train ^getTrain(String ^t);
	 virtual IDisposable ^Subscribe(IObserver<List<Train^>^> ^observer);
	  virtual IDisposable ^Subscribe(IObserver<Train^> ^observer);
};


