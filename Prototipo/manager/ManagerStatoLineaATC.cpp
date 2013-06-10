#include "ManagerStatoLineaATC.h"

ManagerStatoLineaATC::ManagerStatoLineaATC(void)
{
	tabellaCDB = gcnew Dictionary<int, StateCDB^>;
	observers = gcnew List<IObserver<Event^>^>();
}

void ManagerStatoLineaATC::addCheckAndSet(List<StateCDB^> ^listaCDB, String ^source)
{
	for each (StateCDB ^cdb in listaCDB)
	{
		if(!tabellaCDB->ContainsKey(cdb->getNID_CDB()))
		{
			tabellaCDB->Add(cdb->getNID_CDB(), cdb);
			// segnala l'evento!!!
			for each (IObserver<Event^>^ observer in observers)
			{
				observer->OnNext(gcnew Event(cdb->Clone(),source));
			}


		}
		else 
		{
			bool mod = tabellaCDB[cdb->getNID_CDB()]->Update(cdb);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(cdb->Clone(),source));
				}
			}

		}
	}
}

void ManagerStatoLineaATC::addCheckAndSet(StateCDB ^oneCDB, String ^source)
{
	
		if(!tabellaCDB->ContainsKey(oneCDB->getNID_CDB()))
		{
			tabellaCDB->Add(oneCDB->getNID_CDB(), oneCDB);
			// segnala l'evento!!!
			for each (IObserver<Event^>^ observer in observers)
			{
				observer->OnNext(gcnew Event(oneCDB->Clone(),source));
			}


		}
		else 
		{
			bool mod = tabellaCDB[oneCDB->getNID_CDB()]->Update(oneCDB);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(oneCDB->Clone(),source));
				}
			}

		}
	
}

IDisposable ^ManagerStatoLineaATC::Subscribe(IObserver<Event^> ^observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	return gcnew Unsub(observers, observer);

}


StateCDB ^ManagerStatoLineaATC::getCDB(int idcdb){

	if(tabellaCDB->ContainsKey(idcdb)){

		return tabellaCDB[idcdb];
	}

	return gcnew StateCDB();
	
};