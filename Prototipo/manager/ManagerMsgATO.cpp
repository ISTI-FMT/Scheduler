#include "ManagerMsgATO.h"

ManagerMsgATO::ManagerMsgATO(void)
{
	tabellaTrain = gcnew Dictionary<int, physicalTrain^>;
	observers = gcnew List<IObserver<Event<physicalTrain^>^>^>();
}

void ManagerMsgATO::addCheckAndSet(List<physicalTrain^> ^listatrain, String ^source)
{
	for each (physicalTrain ^onetrain in listatrain)
	{
		addCheckAndSet(onetrain,source);
	}
}

void ManagerMsgATO::addCheckAndSet(physicalTrain ^onetrain, String ^source)
{

	if(!tabellaTrain->ContainsKey(onetrain->getEngineNumber()))
	{
		tabellaTrain->Add(onetrain->getEngineNumber(), onetrain);
		// segnala l'evento!!!
		Notify(onetrain);


	}
	else 
	{
		bool mod = tabellaTrain[onetrain->getEngineNumber()]->Update(onetrain);
		if(mod)
		{

			// segnala evento!!!
			Notify(onetrain);
		}else{
			// se ri presentato il treno
			// lo segnalo

			Notify(onetrain);
		}

	}

}

void ManagerMsgATO::Notify(physicalTrain ^onetrain){

	for each (IObserver<Event<physicalTrain^>^>^ observer in observers)
	{
		Event<physicalTrain^> ^evento = gcnew Event<physicalTrain^>(onetrain->Clone());
		observer->OnNext(evento);
	}
}

IDisposable ^ManagerMsgATO::Subscribe(IObserver<Event<physicalTrain^>^> ^observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	return gcnew Unsubscriber<Event<physicalTrain^>^>(observers, observer);

}
