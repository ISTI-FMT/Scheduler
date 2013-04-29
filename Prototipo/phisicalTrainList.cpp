#include "phisicalTrainList.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

phisicalTrainList::phisicalTrainList(void)
{
	treni = gcnew System::Collections::Generic::Dictionary<int,phisicalTrain^>();

}
//metodo momentaneo
phisicalTrain^ phisicalTrainList::getPrimo(){
	Monitor::Enter(treni);
	try{
		Dictionary<int,phisicalTrain^>::ValueCollection^ valueColl = treni->Values;
		for each (phisicalTrain ^var in valueColl)
		{
			return var;
		}
	}
	finally
	{
		// Ensure that the lock is released.
		Monitor::Exit(treni);
	}
	return nullptr;
}