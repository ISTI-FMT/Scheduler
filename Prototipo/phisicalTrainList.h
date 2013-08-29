#pragma once
#include "phisicalTrain.h"

using namespace System::Collections::Generic;
using namespace System::Threading;
using namespace System::Collections::Concurrent;


/*Utilizzo questa classe per raccogliere in una mappa le informazioni di presentazione inviate all'ATS dagli ATO*/

//rappresenta una lista di treni che si sono presentati
ref class phisicalTrainList
{
	ConcurrentDictionary<int,phisicalTrain^> ^treni;
public:
	phisicalTrainList(void);
	void setMapTreni( phisicalTrain^ treno ){
		
			int key = treno->getEngineNumber();
			//treni->AddOrUpdate(key,treno, gcnew Func<int,phisicalTrain^,phisicalTrain^>(&phisicalTrainList::result ));
			if(!treni->ContainsKey(key)){
				
				treni->GetOrAdd(key,treno);

			}else{
				treni[key]=treno;
			}
		
	}
	/*static phisicalTrain^ result(int k ,phisicalTrain^ o){
		return o;
	}*/
	ConcurrentDictionary<int,phisicalTrain^> ^ getMapTreni(){
		return treni;
		
	}
	phisicalTrain^ phisicalTrainList::getPrimo();

	bool  phisicalTrainList::is_Empthy(){
		
			if( treni->Count>0)
			return false;
		
		return true;
	}
};

