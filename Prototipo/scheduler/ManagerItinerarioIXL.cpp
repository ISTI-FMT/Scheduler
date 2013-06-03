#include "ManagerItinerarioIXL.h"

ManagerItinerarioIXL::ManagerItinerarioIXL(void)
{
	tabella = gcnew Dictionary<int, stateItinerario^>;
	observers = gcnew List<IObserver<Event^>^>();
}

void ManagerItinerarioIXL::addCheckAndSetItinerario(List<stateItinerario^> ^listaItin)
{
	for each (stateItinerario ^itin in listaItin)
	{
		if(!tabella->ContainsKey(itin->getNID_ITIN()))
		{
			tabella->Add(itin->getNID_ITIN(), itin);
			// segnala l'evento!!!
			for each (IObserver<Event^>^ observer in observers)
			{
				observer->OnNext(gcnew Event(itin->Clone()));
			}
		}
		else 
		{
			bool mod = tabella[itin->getNID_ITIN()]->Update(itin);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(itin->Clone()));
				}
			}

		}
	}
}

void ManagerItinerarioIXL::addCheckAndSetItinerario(stateItinerario ^oneItinerario)
{

	if(!tabella->ContainsKey(oneItinerario->getNID_ITIN()))
	{
		tabella->Add(oneItinerario->getNID_ITIN(), oneItinerario);
		// segnala l'evento!!!
		for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(oneItinerario->Clone()));
				}
	}
	else 
	{
		bool mod = tabella[oneItinerario->getNID_ITIN()]->Update(oneItinerario);
		if(mod)
		{
			for each (IObserver<Event^>^ observer in observers)
				{
					observer->OnNext(gcnew Event(oneItinerario->Clone()));
				}

			// segnala evento!!!
		}

	}

}

IDisposable ^ManagerItinerarioIXL::Subscribe(IObserver<Event^> ^observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	return gcnew Unsub(observers, observer);

}