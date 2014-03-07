#include "ListTrainModel.h"
#using <System.dll>
using namespace System;

using namespace System::Collections::Generic;


ListTrainModel::ListTrainModel(void)
{
	ListSortedTrains = gcnew System::Collections::Generic::List< Train^>();
	observers = gcnew List<IObserver<List<Train^>^>^>();
	observersTrain = gcnew List<IObserver<Train^>^>();
}

bool ListTrainModel::RemoveElement(Train^ train){
	for each (Train^ treno  in ListSortedTrains)
	{
		if(treno->getPhysicalTrain()->getEngineNumber()==train->getPhysicalTrain()->getEngineNumber()){
			ListSortedTrains->Remove(treno);
			return true;
		}
	}

	return false;
}
bool ListTrainModel::Contains(Train^ train){
	for each (Train^ treno  in ListSortedTrains)
	{
		if(treno->getPhysicalTrain()->getEngineNumber()==train->getPhysicalTrain()->getEngineNumber()){
			return true;
		}
	}

	return false;
}

void ListTrainModel::Add(Train^ train){
	try{

		ListSortedTrains->Add(train);
		Sort();
	}catch(ArgumentException ^e){
		Console::WriteLine("Attenzione: tenti di aggiungere una chiave già esistente");
		Console::WriteLine("########################");
		Console::WriteLine("Exception ",e->ToString());
		Console::WriteLine("########################");
	}
}

List<Train^> ^ListTrainModel::getList(){
	return ListSortedTrains;
}

IDisposable ^ListTrainModel::Subscribe(IObserver<Train^> ^observer){
	if (! observersTrain->Contains(observer)) 
		observersTrain->Add(observer);
	return gcnew Unsubscriber<Train^>(observersTrain, observer);

}

IDisposable ^ListTrainModel::Subscribe(IObserver<List<Train^>^> ^observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	return gcnew Unsubscriber<List<Train^>^>(observers, observer);

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
	for each (IObserver<Train^>^ observer in observersTrain)
	{
		observer->OnNext(key);
	}
}

void ListTrainModel::changePrior(Train ^key, int newprior){
	if(ListSortedTrains->Contains(key)){


		key->setPriorita(newprior);
		Sort();
	}

}
 void   ListTrainModel::changeState(Train ^key,  StateTrain state){
	 if(ListSortedTrains->Contains(key)){
		 key->setStatoTreno(state);
	 }
	 for each (IObserver<Train^>^ observer in observersTrain)
	{
		
		observer->OnNext(key);
	}

 }
void  ListTrainModel::changeOrari(Train ^key,  List<Fermata^> ^nuoviorari){
	if(ListSortedTrains->Contains(key)){

		
		key->changeOrari(nuoviorari);
		Sort();
	}


}