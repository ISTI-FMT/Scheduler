#pragma once
#include "..\\phisicalTrainList.h"
#include "..\\messaggi\\struttureDatiMessaggi.h"
#include "..\\logger\\LogClass.h"
#using <System.dll>

using namespace System;

ref class ThreadPresentazione
{
private:
	 phisicalTrainList ^listaTreni;
public:
	
	ThreadPresentazione();
	ThreadPresentazione(phisicalTrainList ^lt);
	void TCP_Management_receive();
	
};
