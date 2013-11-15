#pragma once
#using <System.dll>
using namespace System;

/*Utilizzo questa classe per serializzare le informazioni di presentazione inviate all'ATS dagli ATO*/

//questa classe contiene le informazioni di presentazione del treno
ref class physicalTrain
{
	int engineNumber;
	String ^ipAddress;
	int tcpPort;
	int cdblastpos;
public:
	
	physicalTrain(void);
	physicalTrain(int e, String^ip, int t){engineNumber=e;ipAddress=ip;tcpPort=t;};
	void setEngineNumber(int N){engineNumber = N;};
	int getEngineNumber(){return engineNumber;};
	void setIpAddress(String ^IP){ipAddress = IP;};
	String^ getIpAddress(){return ipAddress;};
	void setTcpPort(int port){tcpPort = port;};
	int getTcpPort(){return tcpPort;};
	bool Update(physicalTrain ^t);
	physicalTrain ^Clone();
	~physicalTrain(void);
	virtual System::String ^ToString() override;
};

