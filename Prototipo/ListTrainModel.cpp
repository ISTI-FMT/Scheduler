#include "ListTrainModel.h"
#using <System.dll>
using namespace System;

using namespace System::Collections::Generic;


ListTrainModel::ListTrainModel(void)
{
	ListSortedTrains = gcnew System::Collections::Generic::List< Train^>();
	observers = gcnew List<IObserver<List<Train^>^>^>();
}


void ListTrainModel::Add(Train^ train){
	try{

		ListSortedTrains->Add(train);
		Sort();
	}catch(ArgumentException ^e){
		Console::WriteLine("Attenzione: tenti di aggiungere una chiave già esistente");
	}
}

List<Train^> ^ListTrainModel::getList(){
	return ListSortedTrains;
}

IDisposable ^ListTrainModel::Subscribe(IObserver<List<Train^>^> ^observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	return gcnew UnsubModel(observers, observer);

}

 void ListTrainModel::Sort(){
	ListSortedTrains->Sort();
	//Console::WriteLine("");
	for each(  Train^ kvp in ListSortedTrains )
        {
            Console::WriteLine("Key = {0}",kvp);
        }
	for each (IObserver<List<Train^>^>^ observer in observers)
		{
			observer->OnNext(ListSortedTrains);
		}
}


Train ^ListTrainModel::getTrain(String ^t){
	for each (Train ^var in ListSortedTrains)
	{
		if(var->getPTN().ToString()==t){

			return var;
		}
	}
	return nullptr;
}

void ListTrainModel::NextIt(Train ^key){
	if(ListSortedTrains->Contains(key)){
		
		key->goNextItinerario();
		key->setTimeStampNextEvent(key->getOrarioPartenza());
	
	}
}

void ListTrainModel::changePrior(Train ^key, int newprior){
	if(ListSortedTrains->Contains(key)){
		
		
		key->setPriorita(newprior);
		Sort();
	}
	
}

 void  ListTrainModel::changeOrari(Train ^key,  List<Fermata^> ^nuoviorari){
	 if(ListSortedTrains->Contains(key)){
		
		
		key->changeOrari(nuoviorari);
		Sort();
	}


 }