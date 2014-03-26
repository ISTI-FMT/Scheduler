#include "physicalTrain.h"


physicalTrain::physicalTrain(void)
{
	engineNumber = 0;
	ipAddress = "";
	tcpPort = 0;
	cdblastpos = 0;
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
		if(t->getCDBLastPos()!=getCDBLastPos()){
			cdblastpos = t->getCDBLastPos();
			ret=true;
		}
	}
	return ret;
}

physicalTrain ^physicalTrain::Clone(){


	return gcnew physicalTrain(engineNumber,ipAddress,tcpPort);

}

bool physicalTrain::Equals(physicalTrain ^t2) {
	if((engineNumber==t2->getEngineNumber()) & (getIpAddress()==t2->getIpAddress())){
		if((t2->getTcpPort()==getTcpPort()) &(t2->getCDBLastPos()==getCDBLastPos())){
			return true;
		}
	}
	return false;
}

System::String ^physicalTrain::ToString() {
	System::String ^out="";
	out += " EngineNumber: "+engineNumber+" ";
	out += " ipAddress: "+ipAddress+" ";
	out += " tcpPort: "+tcpPort+" ";



	return out;
}