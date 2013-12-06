#include "ControllerListTrain.h"


ControllerListTrain::ControllerListTrain(IListTrainView ^v, IListTrainModel ^m)
{
	this->model = m;
	this->view  = v;
	this->view->AddListener(this);

}




void ControllerListTrain::OnSetTrain(Train^ train){
	model->Add(train);
	view->ViewNewTrain(train);
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
	view->PaintTrain();
	/*for each (Train^ var in model->getList())
	{
		view->ViewNewTrain(var);
	}*/
}

void ControllerListTrain::Sort(){
	model->Sort();
	RePaint();
}