#include "physicalTrain.h"


physicalTrain::physicalTrain(void)
{
	engineNumber = 0;
	ipAddress = "";
	tcpPort = 0;
}

physicalTrain::~physicalTrain(void)
{
}

bool physicalTrain::Update(physicalTrain ^t){
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

physicalTrain ^physicalTrain::Clone(){


	return gcnew physicalTrain(engineNumber,ipAddress,tcpPort);

}

System::String ^physicalTrain::ToString() {
	System::String ^out="";
	out += " EngineNumber: "+engineNumber+" ";
	out += " ipAddress: "+ipAddress+" ";
	out += " tcpPort: "+tcpPort+" ";



	return out;
}