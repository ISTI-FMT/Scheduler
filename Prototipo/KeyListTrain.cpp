#include "KeyListTrain.h"

KeyListTrain::KeyListTrain(int p, int trn, int ptn)
{
	Priorita=p;
	PhysicalTrainNumber=ptn;
	TrainRunningNumber=trn;

}

KeyListTrain::KeyListTrain(int p, int trn, int ptn, double time)
{
	Priorita=p;
	PhysicalTrainNumber=ptn;
	TrainRunningNumber=trn;
	Double times = time*30;
	TimeSpan sinceMidnight = TimeSpan::FromSeconds(times);
	DateTime orarioSupporto = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
	TimeStampNextEvent= orarioSupporto+sinceMidnight;
	
}

KeyListTrain::KeyListTrain(int p,   int ptn)
{
	Priorita=p;
	PhysicalTrainNumber=ptn;
	TrainRunningNumber=0;
	
}


Int32 KeyListTrain::CompareTo(KeyListTrain^otherKey){

	if (otherKey == nullptr) return 1;

	
	if(getPriorita() ==otherKey->getPriorita()){

		if(getTimeNextEvent()!=nullptr & otherKey->getTimeNextEvent()!=nullptr ){
			DateTime ^time = getTimeNextEvent();
			DateTime ^timeNext = otherKey->getTimeNextEvent();
			if(time->CompareTo(timeNext)!=0){
				return time->CompareTo(timeNext);		
			}else{
				return getTRN().CompareTo(otherKey->getTRN());

			}


		}else{
			return 0;
		}
	}
	if(getPriorita() >otherKey->getPriorita()){
		return 1;
	}
	if(getPriorita() <otherKey->getPriorita()){
		return -1;
	}
	return 0;
}

String ^KeyListTrain::ToString(){
	String ^time = "null";
	if(getTimeNextEvent()!=nullptr){
		time = getTimeNextEvent()->ToString();
	}
	String ^out=  String::Format("Priorità: {0} TRN: {1} PT: {2} TimeNextEvent: {3}",getPriorita(),getTRN(),getPTN(),time);

	return out;

}

