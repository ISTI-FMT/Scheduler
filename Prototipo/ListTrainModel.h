#pragma once
#include "Train.h"

public ref class ListTrainModel : public IObservable<List<Train^> ^>
{
	System::Collections::Generic::List<Train^> ^ListSortedTrains;
	 List<IObserver<List<Train^>^>^> ^observers;
public:
	ListTrainModel(void);
	 void Add(Train^ train);
	 System::Collections::Generic::List<Train^> ^getList();
	 void Sort();
	 void NextIt(Train ^key);
	 void changePrior(Train ^key, int newprior);
	 void changeOrari(Train ^key,  List<Fermata^> ^nuoviorari);
	 Train ^getTrain(String ^t);
	 virtual IDisposable ^Subscribe(IObserver<List<Train^>^> ^observer);
};

ref class UnsubModel : public  IDisposable
{
     List<IObserver<List<Train^>^>^>^_observers;
    IObserver<List<Train^>^> ^_observer;

public:
	UnsubModel(List<IObserver<List<Train^>^>^> ^observers, IObserver<List<Train^>^> ^observer)
   {
      _observers = observers;
      _observer = observer;
   };
private:
	 ~UnsubModel(){
      if ((_observer != nullptr)){
		  _observers->Remove(_observer);
	  }
   };
};

