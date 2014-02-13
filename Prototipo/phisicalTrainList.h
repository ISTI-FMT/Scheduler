#pragma once
#include "physicalTrain.h"

using namespace System::Collections::Generic;
using namespace System::Threading;
using namespace System::Collections::Concurrent;


/*Utilizzo questa classe per raccogliere in una mappa le informazioni di presentazione inviate all'ATS dagli ATO*/
/*DISMESSA*/
//rappresenta una lista di treni che si sono presentati
ref class phisicalTrainList
{
	ConcurrentDictionary<int,physicalTrain^> ^treni;
public:
	phisicalTrainList(void);
	void setMapTreni( physicalTrain^ treno ){
		
			int key = treno->getEngineNumber();
			//treni->AddOrUpdate(key,treno, gcnew Func<int,physicalTrain^,physicalTrain^>(&phisicalTrainList::result ));
			if(!treni->ContainsKey(key)){
				
				treni->GetOrAdd(key,treno);

			}else{
				treni[key]=treno;
			}
		
	}
	/*static physicalTrain^ result(int k ,physicalTrain^ o){
		return o;
	}*/
	ConcurrentDictionary<int,physicalTrain^> ^ getMapTreni(){
		return treni;
		
	}
	physicalTrain^ phisicalTrainList::getPrimo();

	bool  phisicalTrainList::is_Empthy(){
		
			if( treni->Count>0)
			return false;
		
		return true;
	}
};

