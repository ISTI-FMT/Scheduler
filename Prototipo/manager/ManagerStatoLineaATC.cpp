#include "ManagerStatoLineaATC.h"

ManagerStatoLineaATC::ManagerStatoLineaATC(void)
{
	tabellaCDB = gcnew Dictionary<int, StateCDB^>;
	observers = gcnew List<IObserver<Event^>^>();
	tabellaTRenoListCDB = gcnew Dictionary<int,List<StateCDB^>^>();
}

void ManagerStatoLineaATC::addCheckAndSet(List<StateCDB^> ^listaCDB, String ^source)
{

	for each (StateCDB ^CDB in listaCDB)
	{
		if(CDB->getNID_CDB()>0){
			Console::WriteLine("CDB {0}",CDB->getNID_CDB());
			int idltreno = CDB->getNID_OPERATIONAL();
			int idftreno = CDB->getNID_ENGINE();
			if(idltreno>0){
				addCheckAndSet(CDB,source);
				if(!tabellaTRenoListCDB->ContainsKey(idltreno)){
					List<StateCDB^> ^listatempcdb = gcnew List<StateCDB^>();
					listatempcdb->Add(CDB);
					tabellaTRenoListCDB->Add(idltreno,listatempcdb);
					//addCheckAndSet(CDB,source);
				}else{

					if(!tabellaTRenoListCDB[idltreno]->Contains(CDB)){
						tabellaTRenoListCDB[idltreno]->Add(CDB);
						addCheckAndSet(CDB,source);
					}else{
						List<StateCDB^> ^listatempcdb = tabellaTRenoListCDB[idltreno];
						int g = listatempcdb->IndexOf(CDB);
						if (listatempcdb[g]->Update(CDB)){
							addCheckAndSet(CDB,source);
						}

					}

				}

			}
		}
	}
	Dictionary<int,List<StateCDB^>^>::ValueCollection^ valuestab =tabellaTRenoListCDB->Values;
	/*for each (List<StateCDB^>^listcdbetmpo in valuestab )
	{


		if(listcdbetmpo!=nullptr){

			for(int i=0;i<listcdbetmpo->Count;i++)
			{
				if(!listaCDB->Contains(listcdbetmpo[i])){

					StateCDB ^cdbdel = listcdbetmpo[i];
					listcdbetmpo->Remove(cdbdel);
					StateCDB ^ncdbdel = cdbdel->Clone();
					ncdbdel->setQ_STATOCDB(typeStateCDB::cdbLibero);
					ncdbdel->setNID_ENGINE(0);
					ncdbdel->setNID_OPERATIONAL(0);
					addCheckAndSet(ncdbdel,"me");
					i--;


				}
			}

		}
	}*/
	/*List<StateCDB^> ^listcdb=nullptr ;
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
	}*/
}


/*void ManagerStatoLineaATC::Notify(StateCDB ^oneCDB, String ^source)
{

// segnala l'evento!!!
for each (IObserver<Event^>^ observer in observers)
{
observer->OnNext(gcnew Event(oneCDB->Clone(),source));
}


}*/

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