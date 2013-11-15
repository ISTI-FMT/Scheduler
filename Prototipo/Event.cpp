#include "Event.h"


Event::Event(void)
{
	sCDB=nullptr;
	sITI=nullptr;
	lTrain=nullptr;
	source="";
}



System::String ^Event::ToString() {
	System::String ^out="";
	out += " Source: "+source+" ";
	if(sCDB){
		out += sCDB->ToString();
	}
	if(sITI){
		out+= sITI->ToString();
	}
	if(lTrain){
		out+= lTrain->ToString();
	}
	return out;
}

StateItinerario ^Event::getEventStateItinerario(){
	//if(sITI!=nullptr){
		return sITI;}
	//else {
	//	return gcnew StateItinerario();}};
StateCDB ^Event::getEventStateCDB(){
	//if(sCDB!=nullptr){
		return sCDB;}
	//else {
	//	return gcnew StateCDB();}};
physicalTrain ^Event::getEventPresentTrain(){
	//if(lTrain!=nullptr){
		return lTrain;}
	//else{
	//	return gcnew physicalTrain();}};
