#include "ListTrainView.h"
using namespace System;
using namespace System::Collections;

void Prototipo::ListTrainView::AddModel(ListTrainModel ^c){
	this->model=c;
}
void Prototipo::ListTrainView::ViewNewTrain(List<Train^>^ trains){

	//setNewTrain(key,train);
	this->Invoke(myDelegateNewTrain,trains);

}

void Prototipo::ListTrainView::setNewTrain(List<Train^>^ trains){
	int numtab = tableLayoutPanel1->Controls->Count;
	int numlist = trains->Count;
	if(numlist<=numtab){
		int i=0;
		for each (Button^ var in tableLayoutPanel1->Controls)
		{
			String ^Namel =  trains[i]->getPhysicalTrain()->getEngineNumber().ToString();
			if(var->Name!=Namel){
				var->Name =  Namel;
				var->Text =  Namel;
			}
			i++;
		}
	}else{
		int xi =0;
		for each (Button^ var in tableLayoutPanel1->Controls)
		{
			String ^Namel =  trains[xi]->getPhysicalTrain()->getEngineNumber().ToString();
			if(var->Name!=Namel){
				var->Name =  Namel;
				var->Text =  Namel;
			}
			xi++;
		}
		for (int i = xi; i < numlist; i++)
		{
			Button ^b = gcnew Button();
			b->Click += gcnew System::EventHandler(this, &Prototipo::ListTrainView::B_Click);
			b->Name =  trains[i]->getPhysicalTrain()->getEngineNumber().ToString();
			b->Text =  trains[i]->getPhysicalTrain()->getEngineNumber().ToString();

			tableLayoutPanel1->Controls->Add(b);	
		}
	}
	/*if(tableLayoutPanel1->Controls->Count==0){
	//SingleTrainInfoForm ^trainView = gcnew SingleTrainInfoForm(train,controller,tabItinerari);
	Button ^b = gcnew Button();
	b->Click += gcnew System::EventHandler(this, &Prototipo::ListTrainView::B_Click);
	b->Name =  train->getPhysicalTrain()->getEngineNumber().ToString();
	b->Text =  train->getPhysicalTrain()->getEngineNumber().ToString();

	tableLayoutPanel1->Controls->Add(b);
	}else{
	String ^Name =  train->getPhysicalTrain()->getEngineNumber().ToString();
	bool addnew=false;
	for each (Button^ var in tableLayoutPanel1->Controls)
	{
	if(var->Name==Name){
	addnew=true;
	break;
	}
	}
	if(!addnew){
	Button ^b = gcnew Button();
	b->Click += gcnew System::EventHandler(this, &Prototipo::ListTrainView::B_Click);
	b->Name =  train->getPhysicalTrain()->getEngineNumber().ToString();
	b->Text =  train->getPhysicalTrain()->getEngineNumber().ToString();

	tableLayoutPanel1->Controls->Add(b);
	}

	}*/

}


Void  Prototipo::ListTrainView::B_Click(System::Object^  sender, System::EventArgs^  e){
	Button ^b = (Button^) sender;
	if(dictionaryTrainsInfoForm->ContainsKey(b->Name)){
		SingleTrainInfoForm ^trainView = dictionaryTrainsInfoForm[b->Name];
		trainView->UpdateInfo();
		trainView->Visible=true;
		trainView->Activate();
	}else{

		Train ^train = model->getTrain(b->Name);
		SingleTrainInfoForm ^trainView = gcnew SingleTrainInfoForm(train,model,tabItinerari);
		trainView->Subscribe(EQueueCambioOrario);
		dictionaryTrainsInfoForm->Add(b->Name,trainView );
		trainView->Visible=true;
	}
}
void Prototipo::ListTrainView::DeleteList(){

	tableLayoutPanel1->Controls->Clear();

}

void Prototipo::ListTrainView::RePaintList(){
	/*if(tableLayoutPanel1->Controls->Count>0){
	array<SingleTrainInfoForm^>^controlArray = gcnew array<SingleTrainInfoForm^>(25);
	tableLayoutPanel1->Controls->CopyTo(controlArray,0);
	tableLayoutPanel1->Controls->Clear();
	Array::Sort(controlArray);

	tableLayoutPanel1->Controls->AddRange(controlArray);
	}*/
}

void Prototipo::ListTrainView::ViewDeleteList(){

	this->Invoke(myDelegateDeleteList);
}

void Prototipo::ListTrainView::PaintTrain(){

	this->Invoke(myDelegatePaint);
	//RePaintList();
}


void  Prototipo::ListTrainView::Subscribe(IObservable<List<Train^>^> ^provider)
{
	if (provider != nullptr) 
		unsubscriber = provider->Subscribe(this);
}

void  Prototipo::ListTrainView::OnCompleted()
{
	Console::WriteLine("The Location Tracker has completed transmitting data to");
	Unsubscribe();
}

void  Prototipo::ListTrainView::OnError(Exception ^e)
{
	Console::WriteLine(" The location cannot be determined.");
}

void  Prototipo::ListTrainView::OnNext(List<Train^>^ value)
{

	ViewNewTrain(value);


}



void  Prototipo::ListTrainView::Unsubscribe()
{
	delete unsubscriber;
}