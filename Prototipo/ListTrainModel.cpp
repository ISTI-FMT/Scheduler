#include "ListTrainModel.h"
#using <System.dll>
using namespace System;

using namespace System::Collections::Generic;


ListTrainModel::ListTrainModel(void)
{
	ListSortedTrains = gcnew System::Collections::Generic::SortedList<KeyListTrain^, Train^>();
}


void ListTrainModel::Add(KeyListTrain ^key,Train^ train){
	try{

		ListSortedTrains->Add(key,train);
	}catch(ArgumentException ^e){
		Console::WriteLine("Attenzione: tenti di aggiungere una chiave già esistente");
	}
}

SortedList<KeyListTrain^, Train^> ^ListTrainModel::getList(){
	return ListSortedTrains;
}

void ListTrainModel::set(KeyListTrain ^key,List<Fermata^> ^list){
	if(ListSortedTrains->ContainsKey(key)){
		Train ^t = ListSortedTrains[key];
		t->setListaItineari(list);

	}
}

void ListTrainModel::set(KeyListTrain ^key,StateTrain state){
	if(ListSortedTrains->ContainsKey(key)){
		Train ^t = ListSortedTrains[key];
		t->setStatoTreno(state);

	}
}

void ListTrainModel::NextIt(KeyListTrain ^key){
	if(ListSortedTrains->ContainsKey(key)){
		ListSortedTrains[key]->goNextItinerario();

	}
}
