#pragma once
#include "phisicalTrain.h"

using namespace System::Collections::Generic;
using namespace System::Threading;

ref class phisicalTrainList
{
	Dictionary<int,phisicalTrain^> ^treni;
public:
	phisicalTrainList(void);
	void setMapTreni( phisicalTrain^ treno ){
		Monitor::Enter(treni);
		try{
			int key = treno->getEngineNumber();
			if(!treni->ContainsKey(key)){
				treni->Add(key,treno);
			}else{
				treni[key]=treno;
			}
		}
		finally
		{
			// Ensure that the lock is released.
			Monitor::Exit(treni);
		}

	}
	Dictionary<int,phisicalTrain^> ^ getMapTreni(){
		return treni;
	}

	phisicalTrain^ phisicalTrainList::getPrimo();

	bool  phisicalTrainList::is_Empthy(){
		Monitor::Enter(treni);
		try{
			if( treni->Count>0)
			return false;
		}
		finally
		{
			// Ensure that the lock is released.
			Monitor::Exit(treni);
		}
		return true;
	}
};

