#include "phisicalTrainList.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

phisicalTrainList::phisicalTrainList(void)
{
	treni = gcnew ConcurrentDictionary<int,phisicalTrain^>();

}
//metodo momentaneo
phisicalTrain^ phisicalTrainList::getPrimo(){
	
	for each (phisicalTrain ^var in treni->Values)
		{
			return var;
		}
	
		
	/*	for each (KeyValuePair<int,phisicalTrain^> ^var in treni)
		{
			return var->Value;
		}*/
	
	
	return nullptr;
}