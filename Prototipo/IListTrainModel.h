#include "KeyListTrain.h"
#include "Train.h"
#include "tabellaOrario\\Fermata.h"
#include "Train.h"



public interface class IListTrainModel
{
   void Add(KeyListTrain ^key,Train^ train);
   System::Collections::Generic::SortedList<KeyListTrain^, Train^> ^getList();
   void set(KeyListTrain ^key,List<Fermata^> ^list);
	void set(KeyListTrain ^key,StateTrain state);
	void NextIt(KeyListTrain ^key);
	void changePrior(KeyListTrain ^key, int newprior);
	
};