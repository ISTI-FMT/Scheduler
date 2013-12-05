#include "KeyListTrain.h"
#include "Train.h"
#include "tabellaOrario\\Fermata.h"


public interface class IControllerListTrain{
 	void OnSetTrainI(KeyListTrain ^key,List<Fermata^> ^list);
	void OnSetTrain(KeyListTrain ^key,StateTrain state);
	void OnSetTrain(KeyListTrain ^key,Train^ train);
	void OnNextIt(KeyListTrain ^key);
	System::Collections::Generic::SortedList<KeyListTrain^, Train^> ^ getListTrain();
	void OnDelete();
	void changePrior(KeyListTrain ^key, int newprior);
};