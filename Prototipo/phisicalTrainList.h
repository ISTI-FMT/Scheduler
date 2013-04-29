#pragma once
#include "phisicalTrain.h"

using namespace System::Collections::Generic;
using namespace System::Threading;
using namespace System::Collections::Concurrent;

ref class phisicalTrainList
{
	ConcurrentDictionary<int,phisicalTrain^> ^treni;
public:
	phisicalTrainList(void);
	void setMapTreni( phisicalTrain^ treno ){
		
			int key = treno->getEngineNumber();
			if(!treni->ContainsKey(key)){
				
				treni->GetOrAdd(key,treno);

				//treni->Add(newvalue);
			}else{
				treni[key]=treno;
			}
		
	}
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

