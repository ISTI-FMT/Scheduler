#include "Train.h"
#include "tabellaOrario\\Fermata.h"
#include "Train.h"



public interface class IListTrainModel
{
   void Add(Train^ train);
   System::Collections::Generic::List<Train^> ^getList();
 
	void NextIt(Train ^key);
	void changePrior(Train ^key, int newprior);
	 void Sort();
};