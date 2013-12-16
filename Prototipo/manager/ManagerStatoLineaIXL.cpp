#include "ManagerStatoLineaIXL.h"

ManagerStatoLineaIXL::ManagerStatoLineaIXL(void)
{
	tabellaCDB = gcnew Dictionary<int, StateCDB^>;
	tabellaItin = gcnew Dictionary<int, StateItinerario^>;
	observers = gcnew List<IObserver<Event<StateCDB^>^>^>();
}

void ManagerStatoLineaIXL::addCheckAndSet(List<StateCDB^> ^listaCDB, String ^source)
{
	for each (StateCDB ^cdb in listaCDB)
	{
		addCheckAndSet(cdb,source);
		//if(!tabellaCDB->ContainsKey(cdb->getNID_CDB()))
		//{
		//	tabellaCDB->Add(cdb->getNID_CDB(), cdb);
		//	// segnala l'evento!!!
		//	for each (IObserver<Event^>^ observer in observers)
		//	{
		//		observer->OnNext(gcnew Event(cdb->Clone(),source));
		//	}


		//}
		//else 
		//{
		//	bool mod = tabellaCDB[cdb->getNID_CDB()]->Update(cdb);
		//	if(mod)
		//	{

		//		// segnala evento!!!
		//		for each (IObserver<Event^>^ observer in observers)
		//		{
		//			observer->OnNext(gcnew Event(cdb->Clone(),source));
		//		}
		//	}

		//}
	}
}

void ManagerStatoLineaIXL::addCheckAndSet(StateCDB ^oneCDB, String ^source)
{

	if(!tabellaCDB->ContainsKey(oneCDB->getNID_CDB()))
	{
		tabellaCDB->Add(oneCDB->getNID_CDB(), oneCDB);
		// segnala l'evento!!!
		for each (IObserver<Event<StateCDB^>^>^ observer in observers)
		{
			Event<StateCDB^> ^evento = gcnew Event<StateCDB^>(oneCDB->Clone());

			observer->OnNext(evento);

		}


	}
	else 
	{
		bool mod = tabellaCDB[oneCDB->getNID_CDB()]->Update(oneCDB);
		if(mod)
		{

			// segnala evento!!!
			for each (IObserver<Event<StateCDB^>^>^ observer in observers)
			{
				Event<StateCDB^> ^evento = gcnew Event<StateCDB^>(oneCDB->Clone());

				observer->OnNext(evento);
			}
		}

	}

}

IDisposable ^ManagerStatoLineaIXL::Subscribe(IObserver<Event<StateCDB^>^>^ observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	Unsubscriber<Event<StateCDB^>^> ^unsub = gcnew Unsubscriber<Event<StateCDB^>^>(observers, observer);
	return unsub;

}

void ManagerStatoLineaIXL::addCheckAndSet(List<StateItinerario^> ^listaItin, String ^source)
{
	for each (StateItinerario ^itin in listaItin)
	{
		if(!tabellaItin->ContainsKey(itin->getNID_ITIN()))
		{
			tabellaItin->Add(itin->getNID_ITIN(), itin);
			// segnala l'evento!!!
			for each (IObserver<Event<StateItinerario^>^>^ observer in observers)
			{
				Event<StateItinerario^> ^evento = gcnew Event<StateItinerario^>(itin->Clone());

				observer->OnNext(evento);

			}
		}
		else 
		{
			bool mod = tabellaItin[itin->getNID_ITIN()]->Update(itin);
			if(mod)
			{

				// segnala evento!!!
				for each (IObserver<Event<StateItinerario^>^>^ observer in observers)
				{
					Event<StateItinerario^> ^evento = gcnew Event<StateItinerario^>(itin->Clone());
					observer->OnNext(evento);
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
		for each (IObserver<Event<StateItinerario^>^>^ observer in observers)
		{
			Event<StateItinerario^> ^evento = gcnew Event<StateItinerario^>(oneItinerario->Clone());

			observer->OnNext(evento);

		}
	}
	else 
	{
		bool mod = tabellaItin[oneItinerario->getNID_ITIN()]->Update(oneItinerario);
		if(mod)
		{
			for each (IObserver<Event<StateItinerario^>^>^ observer in observers)
			{


				observer->OnNext(gcnew Event<StateItinerario^>(oneItinerario->Clone()));
			}

			// segnala evento!!!
		}

	}

}

StateItinerario ^ManagerStatoLineaIXL::getItinerario(int iditin){
	if(tabellaItin->ContainsKey(iditin)){
		return tabellaItin[iditin];

	}


	return gcnew StateItinerario();
}

StateCDB^ ManagerStatoLineaIXL::StatoCDB(int idcdb){
	if(tabellaCDB->ContainsKey(idcdb)){

		return	tabellaCDB[idcdb];

	}
	return nullptr;


}