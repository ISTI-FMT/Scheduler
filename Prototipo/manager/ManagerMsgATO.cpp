#include "ManagerMsgATO.h"

ManagerMsgATO::ManagerMsgATO(void)
{
	tabellaTrain = gcnew Dictionary<int, physicalTrain^>;
	observers = gcnew List<IObserver<Event^>^>();
}

void ManagerMsgATO::addCheckAndSet(List<physicalTrain^> ^listatrain, String ^source)
{
	for each (physicalTrain ^train in listatrain)
	{
		if(!tabellaTrain->ContainsKey(train->getEngineNumber()))
		{
			tabellaTrain->Add(train->getEngineNumber(), train);
			// segnala l'evento!!!
			for each (IObserver<Event^>^ observer in observers)
			{
				observer->OnNext(gcnew Event(train->Clone(),source));
			}


		}
		else 
		{
			bool mod = tabellaTrain[train->getEngineNumber()]->Update(train);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(train->Clone(),source));
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
			for each (IObserver<Event^>^ observer in observers)
			{
				observer->OnNext(gcnew Event(onetrain->Clone(),source));
			}


		}
		else 
		{
			bool mod = tabellaTrain[onetrain->getEngineNumber()]->Update(onetrain);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(onetrain->Clone(),source));
				}
			}

		}
	
}

IDisposable ^ManagerMsgATO::Subscribe(IObserver<Event^> ^observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	return gcnew Unsubus(observers, observer);

}
