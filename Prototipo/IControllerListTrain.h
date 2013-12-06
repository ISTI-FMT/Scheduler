
#include "Train.h"
#include "tabellaOrario\\Fermata.h"


public interface class IControllerListTrain{

	void OnSetTrain(Train^ train);
	void OnNextIt(Train ^key);
	System::Collections::Generic::List<Train^> ^ getListTrain();
	void OnDelete();
	void changePrior(Train ^key, int newprior);
	void RePaint();
	 void Sort();
};