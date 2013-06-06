#include "ManagerStatoLineaIXL.h"

ManagerStatoLineaIXL::ManagerStatoLineaIXL(void)
{
	tabellaCDB = gcnew Dictionary<int, StateCDB^>;
	tabellaItin = gcnew Dictionary<int, StateItinerario^>;
	observers = gcnew List<IObserver<Event^>^>();
}

void ManagerStatoLineaIXL::addCheckAndSet(List<StateCDB^> ^listaCDB, String ^source)
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

void ManagerStatoLineaIXL::addCheckAndSet(StateCDB ^oneCDB, String ^source)
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

IDisposable ^ManagerStatoLineaIXL::Subscribe(IObserver<Event^> ^observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	return gcnew Unsubscriber(observers, observer);

}

void ManagerStatoLineaIXL::addCheckAndSet(List<StateItinerario^> ^listaItin, String ^source)
{
	for each (StateItinerario ^itin in listaItin)
	{
		if(!tabellaItin->ContainsKey(itin->getNID_ITIN()))
		{
			tabellaItin->Add(itin->getNID_ITIN(), itin);
			// segnala l'evento!!!
			for each (IObserver<Event^>^ observer in observers)
			{
				observer->OnNext(gcnew Event(itin->Clone(),source));
			}
		}
		else 
		{
			bool mod = tabellaItin[itin->getNID_ITIN()]->Update(itin);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(itin->Clone(),source));
				}
			}

		}
	}
}

void ManagerStatoLineaIXL::addCheckAndSet(StateItinerario ^oneItinerario, String ^source)
{

	if(!tabellaItin->ContainsKey(oneItinerario->getNID_ITIN()))
	{
		tabellaItin->Add(oneItinerario->getNID_ITIN(), oneItinerario);
		// segnala l'evento!!!
		for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(oneItinerario->Clone(),source));
				}
	}
	else 
	{
		bool mod = tabellaItin[oneItinerario->getNID_ITIN()]->Update(oneItinerario);
		if(mod)
		{
			for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(oneItinerario->Clone(),source));
				}

			// segnala evento!!!
		}

	}

}