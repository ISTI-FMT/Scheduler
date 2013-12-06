#include "ListTrainView.h"

void Prototipo::ListTrainView::AddListener(IControllerListTrain ^c){
	this->controller=c;
}
void Prototipo::ListTrainView::ViewNewTrain(KeyListTrain ^key,Train^ train){

	//setNewTrain(key,train);
	this->Invoke(myDelegateNewTrain,key,train);

}

void Prototipo::ListTrainView::setNewTrain(KeyListTrain ^key,Train^ train){


	SingleTrainInfoForm ^trainView = gcnew SingleTrainInfoForm(train,key,controller,tabItinerari);

	tableLayoutPanel1->Controls->Add(trainView);

}
void Prototipo::ListTrainView::ViewChangeTrain(KeyListTrain ^key,StateTrain state){

}
void Prototipo::ListTrainView::ViewChangeTrain(KeyListTrain ^key,List<Fermata^>^ train){

}

Void  Prototipo::ListTrainView::B_Click(System::Object^  sender, System::EventArgs^  e){


}
void Prototipo::ListTrainView::DeleteList(){

	tableLayoutPanel1->Controls->Clear();
}

void Prototipo::ListTrainView::ViewDeleteList(){

	this->Invoke(myDelegateDeleteList);
}