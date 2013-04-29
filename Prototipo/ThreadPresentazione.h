#pragma once
#include "phisicalTrainList.h"
#include "struttureDatiMessaggi.h"
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
	static void stampaBuffer(byte *buff, int nBit);
};
