#pragma once
#using <System.dll>
using namespace System;

ref class phisicalTrain
{
	int engineNumber;
	String ^ipAddress;
	int tcpPort;
public:
	
	phisicalTrain(void);
	phisicalTrain(int e, String^ip, int t){engineNumber=e;ipAddress=ip;tcpPort=t;};
	void setEngineNumber(int N){engineNumber = N;};
	int getEngineNumber(){return engineNumber;};
	void setIpAddress(String ^IP){ipAddress = IP;};
	String^ getIpAddress(){return ipAddress;};
	void setTcpPort(int port){tcpPort = port;};
	int getTcpPort(){return tcpPort;};
	bool Update(phisicalTrain ^t);
	phisicalTrain ^Clone();
	~phisicalTrain(void);
	virtual System::String ^ToString() override;
};

