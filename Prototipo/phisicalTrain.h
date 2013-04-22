#pragma once
#include <iostream>
using namespace std;

class phisicalTrain
{
	int engineNumber;
	string ipAddress;
	int tcpPort;
public:
	phisicalTrain(void);
	void setEngineNumber(int N){engineNumber = N;};
	int getEngineNumber(){return engineNumber;};
	void setIpAddress(string IP){ipAddress = IP;};
	string getIpAddress(){return ipAddress;};
	void setTcpPort(int port){tcpPort = port;};
	int getTcpPort(){return tcpPort;};
	~phisicalTrain(void);
};

