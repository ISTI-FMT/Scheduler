#include "phisicalTrain.h"


phisicalTrain::phisicalTrain(void)
{
	engineNumber = 0;
	ipAddress = "";
	tcpPort = 0;
}

phisicalTrain::~phisicalTrain(void)
{
}

bool phisicalTrain::Update(phisicalTrain ^t){
	bool ret = false;
	if(engineNumber==t->getEngineNumber()){
		if(t->getIpAddress()!=ipAddress){
			ipAddress=t->getIpAddress();
			ret=true;
		}
		if(t->getTcpPort()!=tcpPort){
			tcpPort = t->getTcpPort();
			ret=true;
		}
	}
	return ret;
}

phisicalTrain ^phisicalTrain::Clone(){


	return gcnew phisicalTrain(engineNumber,ipAddress,tcpPort);

}

System::String ^phisicalTrain::ToString() {
	System::String ^out="";
	out += " EngineNumber: "+engineNumber+" ";
	out += " ipAddress: "+ipAddress+" ";
	out += " tcpPort: "+tcpPort+" ";



	return out;
}