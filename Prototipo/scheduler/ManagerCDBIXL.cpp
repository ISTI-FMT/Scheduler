#include "ManagerCDBIXL.h"

ManagerCDBIXL::ManagerCDBIXL(void)
{
	tabella = gcnew Dictionary<int, stateCDB^>;
	observers = gcnew List<IObserver<Event^>^>();
}

void ManagerCDBIXL::addCheckAndSetCDB(List<stateCDB^> ^listaCDB)
{
	for each (stateCDB ^cdb in listaCDB)
	{
		if(!tabella->ContainsKey(cdb->getNID_CDB()))
		{
			tabella->Add(cdb->getNID_CDB(), cdb);
			// segnala l'evento!!!
			for each (IObserver<Event^>^ observer in observers)
			{
				observer->OnNext(gcnew Event(cdb->Clone()));
			}


		}
		else 
		{
			bool mod = tabella[cdb->getNID_CDB()]->Update(cdb);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(cdb->Clone()));
				}
			}

		}
	}
}

void ManagerCDBIXL::addCheckAndSetCDB(stateCDB ^oneCDB)
{
	
		if(!tabella->ContainsKey(oneCDB->getNID_CDB()))
		{
			tabella->Add(oneCDB->getNID_CDB(), oneCDB);
			// segnala l'evento!!!
			for each (IObserver<Event^>^ observer in observers)
			{
				observer->OnNext(gcnew Event(oneCDB->Clone()));
			}


		}
		else 
		{
			bool mod = tabella[oneCDB->getNID_CDB()]->Update(oneCDB);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(oneCDB->Clone()));
				}
			}

		}
	
}

IDisposable ^ManagerCDBIXL::Subscribe(IObserver<Event^> ^observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	return gcnew Unsubscriber(observers, observer);

}