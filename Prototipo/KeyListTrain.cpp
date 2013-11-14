#include "KeyListTrain.h"


KeyListTrain::KeyListTrain(int p, int trn, int tpn)
{
	Priorita=p;
	TrainPhisicalNumber=tpn;
	TrainRunningNumber=trn;
}

KeyListTrain::KeyListTrain(int p,  int tpn)
{
	Priorita=p;
	TrainPhisicalNumber=tpn;
	TrainRunningNumber=0;
}


Int32 KeyListTrain::CompareTo(KeyListTrain^otherKey){

	if (otherKey == nullptr) return 1;


	if(getPriorita() ==otherKey->getPriorita()){
		return 0;
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
	String ^out=  String::Format("Priorità: {0} TRN: {1} TPN: {2} TimeNextEvent: {3}",getPriorita(),getTRN(),getTPN(),time);

	return out;

}

