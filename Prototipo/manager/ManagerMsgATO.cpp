#include "ManagerMsgATO.h"

ManagerMsgATO::ManagerMsgATO(void)
{
	tabellaTrain = gcnew Dictionary<int, physicalTrain^>;
	observers = gcnew List<IObserver<Event<physicalTrain^>^>^>();
}

void ManagerMsgATO::addCheckAndSet(List<physicalTrain^> ^listatrain, String ^source)
{
	for each (physicalTrain ^train in listatrain)
	{
		if(!tabellaTrain->ContainsKey(train->getEngineNumber()))
		{
			tabellaTrain->Add(train->getEngineNumber(), train);
			// segnala l'evento!!!
			for each (IObserver<Event<physicalTrain^>^>^ observer in observers)
			{
			
				 Event<physicalTrain^> ^evento = gcnew Event<physicalTrain^>(train->Clone());
				 
				observer->OnNext(evento);
			}


		}
		else 
		{
			bool mod = tabellaTrain[train->getEngineNumber()]->Update(train);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event<physicalTrain^>^>^ observer in observers)
				{
					Event<physicalTrain^> ^evento = gcnew Event<physicalTrain^>(train->Clone());
				
					observer->OnNext(evento);
				}
			}

		}
	}
}

void ManagerMsgATO::addCheckAndSet(physicalTrain ^onetrain, String ^source)
{
	
		if(!tabellaTrain->ContainsKey(onetrain->getEngineNumber()))
		{
			tabellaTrain->Add(onetrain->getEngineNumber(), onetrain);
			// segnala l'evento!!!
			for each (IObserver<Event<physicalTrain^>^>^ observer in observers)
			{
				Event<physicalTrain^> ^evento = gcnew Event<physicalTrain^>(onetrain->Clone());
					observer->OnNext(evento);
			
			}


		}
		else 
		{
			bool mod = tabellaTrain[onetrain->getEngineNumber()]->Update(onetrain);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event<physicalTrain^>^>^ observer in observers)
				{
					Event<physicalTrain^> ^evento = gcnew Event<physicalTrain^>(onetrain->Clone());
					observer->OnNext(evento);
				}
			}

		}
	
}

IDisposable ^ManagerMsgATO::Subscribe(IObserver<Event<physicalTrain^>^> ^observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	return gcnew Unsubscriber<Event<physicalTrain^>^>(observers, observer);

}
