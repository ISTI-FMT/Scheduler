#pragma once
#include "StateObject.h"
#using <System.dll>

using namespace System;

/*Utilizzo questa classe per serializzare le informazioni di presentazione inviate all'ATS dagli ATO*/

//questa classe contiene le informazioni di presentazione del treno
public ref class physicalTrain : public IEquatable<physicalTrain^>
{
	int engineNumber;
	String ^ipAddress;
	int tcpPort;
	int cdblastpos;
	StateObject ^stateobj;
public:
	
	physicalTrain(void);
	physicalTrain(int e, String^ip, int t){	setEngineNumber(e);setIpAddress(ip);setTcpPort(t);setCDBLastPos (0);};
	void setEngineNumber(int N){engineNumber = N;};
	int getEngineNumber(){return engineNumber;};
	void setStateObject(StateObject ^st){stateobj=st;};
	StateObject ^getStateObject(){return stateobj;};
	void setIpAddress(String ^IP){ipAddress = IP;};
	String^ getIpAddress(){return ipAddress;};
	void setTcpPort(int port){tcpPort = port;};
	int getTcpPort(){return tcpPort;};
	int getCDBLastPos(){return cdblastpos;};
	void setCDBLastPos(int c){cdblastpos = c;};
	bool Update(physicalTrain ^t);
	physicalTrain ^Clone();
	virtual System::String ^ToString() override;
	virtual bool Equals(physicalTrain ^t2);
};

