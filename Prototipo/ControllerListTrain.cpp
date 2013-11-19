#include "ControllerListTrain.h"


ControllerListTrain::ControllerListTrain(IListTrainView ^v, IListTrainModel ^m)
{
	this->model = m;
	this->view  = v;
	this->view->AddListener(this);

}



void ControllerListTrain::OnSetTrainI(KeyListTrain ^key,List<Fermata^> ^list){
	model->set(key,list);
	view->ViewChangeTrain(key,list);
}
void ControllerListTrain::OnSetTrain(KeyListTrain ^key,StateTrain state){
	model->set(key,state);
	view->ViewChangeTrain(key,state);
}
void ControllerListTrain::OnSetTrain(KeyListTrain ^key,Train^ train){
	model->Add(key,train);
	view->ViewNewTrain(key,train);
}
void ControllerListTrain::OnDelete(){
}

  System::Collections::Generic::SortedList<KeyListTrain^, Train^> ^ControllerListTrain::getListTrain(){

	return model->getList();
 }

  void ControllerListTrain::OnNextIt(KeyListTrain ^key){
	  
	  model->NextIt(key);
  }