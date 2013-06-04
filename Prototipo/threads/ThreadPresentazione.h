#pragma once
#include "..\\phisicalTrainList.h"
#include "..\\messaggi\\struttureDatiMessaggi.h"
#include "..\\scheduler\\ManagerMsgATO.h"

#using <System.dll>
using namespace System;

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS � in grado di ricevere messaggi di presentazione da parte di sistemi ATO
-------------------------------------------------------------------------------------------------*/

ref class ThreadPresentazione
{
private:
	 phisicalTrainList ^listaTreni;
	 ManagerMsgATO ^ManaMsgATO;
public:
	
	ThreadPresentazione();
	ThreadPresentazione(phisicalTrainList ^lt, ManagerMsgATO ^MA);
	void TCP_Management_receive();
	
};
