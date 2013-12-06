#include "ListTrainModel.h"
#using <System.dll>
using namespace System;

using namespace System::Collections::Generic;


ListTrainModel::ListTrainModel(void)
{
	ListSortedTrains = gcnew System::Collections::Generic::List< Train^>();
}


void ListTrainModel::Add(Train^ train){
	try{

		ListSortedTrains->Add(train);
		//ListSortedTrains->Sort();
	}catch(ArgumentException ^e){
		Console::WriteLine("Attenzione: tenti di aggiungere una chiave già esistente");
	}
}

List<Train^> ^ListTrainModel::getList(){
	return ListSortedTrains;
}


 void ListTrainModel::Sort(){
	ListSortedTrains->Sort();
	//Console::WriteLine("");
	for each(  Train^ kvp in ListSortedTrains )
        {
            Console::WriteLine("Key = {0}",kvp);
        }
}


void ListTrainModel::NextIt(Train ^key){
	if(ListSortedTrains->Contains(key)){
		
		key->goNextItinerario();
		//ListSortedTrains->Remove(key);
		key->setTimeStampNextEvent(key->getOrarioPartenza());
	//	ListSortedTrains->Sort();
		//ListSortedTrains->Add(key,t);
	}
}

void ListTrainModel::changePrior(Train ^key, int newprior){
	if(ListSortedTrains->Contains(key)){
		
		
		key->setPriorita(newprior);
	//	ListSortedTrains->Sort();
	}
	
}
