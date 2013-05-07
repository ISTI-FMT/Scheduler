#pragma once
#include "..\\phisicalTrainList.h"
#include "..\\messaggi\\struttureDatiMessaggi.h"
#include "..\\logger\\LogClass.h"
#using <System.dll>
using namespace System;

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS è in grado di ricevere messaggi di presentazione da parte di sistemi ATO
-------------------------------------------------------------------------------------------------*/

ref class ThreadPresentazione
{
private:
	 phisicalTrainList ^listaTreni;
public:
	
	ThreadPresentazione();
	ThreadPresentazione(phisicalTrainList ^lt);
	void TCP_Management_receive();
	
};
