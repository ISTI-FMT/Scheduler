#include "ListTrainView.h"
using namespace System;
using namespace System::Collections;

void Prototipo::ListTrainView::AddListener(IControllerListTrain ^c){
	this->controller=c;
}
void Prototipo::ListTrainView::ViewNewTrain(Train^ train){

	//setNewTrain(key,train);
	this->Invoke(myDelegateNewTrain,train);

}

void Prototipo::ListTrainView::setNewTrain(Train^ train){


	SingleTrainInfoForm ^trainView = gcnew SingleTrainInfoForm(train,controller,tabItinerari);

	tableLayoutPanel1->Controls->Add(trainView);

}


Void  Prototipo::ListTrainView::B_Click(System::Object^  sender, System::EventArgs^  e){


}
void Prototipo::ListTrainView::DeleteList(){

	tableLayoutPanel1->Controls->Clear();
	
}

void Prototipo::ListTrainView::RePaintList(){
	if(tableLayoutPanel1->Controls->Count>0){
		array<SingleTrainInfoForm^>^controlArray = gcnew array<SingleTrainInfoForm^>(25);
	tableLayoutPanel1->Controls->CopyTo(controlArray,0);
	tableLayoutPanel1->Controls->Clear();
	 Array::Sort(controlArray);
	  
	 tableLayoutPanel1->Controls->AddRange(controlArray);
	}
}

void Prototipo::ListTrainView::ViewDeleteList(){

	this->Invoke(myDelegateDeleteList);
}

void Prototipo::ListTrainView::PaintTrain(){

	this->Invoke(myDelegatePaint);
	//RePaintList();
}
