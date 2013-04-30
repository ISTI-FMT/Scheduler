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
	 LogClass ^logMSG;
public:
	
	ThreadPresentazione();
	ThreadPresentazione(phisicalTrainList ^lt,LogClass ^log );
	void TCP_Management_receive();
	static void stampaBuffer(byte *buff, int nBit);
};
