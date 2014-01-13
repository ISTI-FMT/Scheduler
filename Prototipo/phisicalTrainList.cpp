#include "phisicalTrainList.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

phisicalTrainList::phisicalTrainList(void)
{
	treni = gcnew ConcurrentDictionary<int,physicalTrain^>();
}

//metodo momentaneo
physicalTrain^ phisicalTrainList::getPrimo(){
	
	for each (physicalTrain ^var in treni->Values)
		{
			return var;
		}
	
		
	/*	for each (KeyValuePair<int,physicalTrain^> ^var in treni)
		{
			return var->Value;
		}*/
	
	
	return nullptr;
}