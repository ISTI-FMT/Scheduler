#include "ManagerStatoLineaATC.h"

ManagerStatoLineaATC::ManagerStatoLineaATC(void)
{
	tabellaCDB = gcnew Dictionary<int, StateCDB^>;
	observers = gcnew List<IObserver<Event^>^>();
	tabellaTRenoListCDB = gcnew Dictionary<int,List<StateCDB^>^>();
}

void ManagerStatoLineaATC::addCheckAndSet(List<StateCDB^> ^listaCDB, String ^source)
{
	List<StateCDB^> ^listcdb=nullptr ;
	int idtreno = listaCDB[0]->getNID_OPERATIONAL();
	if(idtreno>0){
		if(tabellaTRenoListCDB->ContainsKey(idtreno)){

			listcdb = tabellaTRenoListCDB[idtreno];
		}else{
			tabellaTRenoListCDB->Add(idtreno, listaCDB);
			listcdb=listaCDB;
		}
	}

	for each (StateCDB ^cdb in listaCDB)
	{
		addCheckAndSet(cdb, source);
		if(listcdb!=nullptr){
			if(listcdb->Contains(cdb)){
				int g = listcdb->IndexOf(cdb);
				listcdb[g]->Update(cdb);

			}else{
				listcdb->Add(cdb);
			}

		}

	}
	if(listcdb!=listaCDB){
		for(int i=0;i<listcdb->Count;i++)
		{
			if(!listaCDB->Contains(listcdb[i])){

				StateCDB ^cdbdel = listcdb[i];
				listcdb->Remove(cdbdel);
				StateCDB ^ncdbdel = cdbdel->Clone();
				ncdbdel->setQ_STATOCDB(typeStateCDB::cdbLibero);
				addCheckAndSet(ncdbdel,"me");
				
			}
		}
	}
}

void ManagerStatoLineaATC::addCheckAndSet(StateCDB ^oneCDB, String ^source)
{


	/*
	if(oneCDB->getNID_OPERATIONAL()>0 & oneCDB->getQ_STATOCDB()!=typeStateCDB::cdbLibero){
	if(tabellaTRenoListCDB->ContainsKey(oneCDB->getNID_OPERATIONAL())){

	List<StateCDB^> ^listcdb = tabellaTRenoListCDB[oneCDB->getNID_OPERATIONAL()];
	if(listcdb->Contains(oneCDB)){
	int g = listcdb->IndexOf(oneCDB);
	listcdb[g]->Update(oneCDB);

	}else{
	listcdb->Add(oneCDB);
	}

	if(listcdb->Count>=4){
	if(listcdb[0]->getQ_STATOCDB()==typeStateCDB::cdbOccupato &
	listcdb[1]->getQ_STATOCDB()==typeStateCDB::cdbOccupato &
	listcdb[2]->getQ_STATOCDB()==typeStateCDB::cdbOccupato 
	){
	StateCDB ^cdbdel = listcdb[0];
	listcdb->Remove(cdbdel);
	cdbdel->setQ_STATOCDB(typeStateCDB::cdbLibero);
	addCheckAndSet(cdbdel,"me");
	}

	}

	}else{
	List<StateCDB^> ^listcdb = gcnew List<StateCDB^>();
	listcdb->Add(oneCDB);
	tabellaTRenoListCDB->Add(oneCDB->getNID_OPERATIONAL(), listcdb);
	}
	}
	*/

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