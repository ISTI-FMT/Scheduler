#include "ControllerListTrain.h"


ControllerListTrain::ControllerListTrain(ListTrainModel ^m)
{
	this->model = m;


}




void ControllerListTrain::OnSetTrain(Train^ train){
	model->Add(train);
	
}
void ControllerListTrain::OnDelete(){
}

System::Collections::Generic::List<Train^> ^ControllerListTrain::getListTrain(){

	return model->getList();
}

void ControllerListTrain::OnNextIt(Train ^key){

	model->NextIt(key);
	
}

void ControllerListTrain::changePrior(Train ^key, int newprior){

	model->changePrior(key,newprior);
	
}

void ControllerListTrain::RePaint(){
	//view->ViewDeleteList();
	//view->PaintTrain();
	/*for each (Train^ var in model->getList())
	{
		view->ViewNewTrain(var);
	}*/
}

void ControllerListTrain::Sort(){
	model->Sort();
	//RePaint();
}