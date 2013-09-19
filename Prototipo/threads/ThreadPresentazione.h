#pragma once
#include "..\\phisicalTrainList.h"
#include "..\\manager\\ManagerMsgATO.h"

#using <System.dll>
using namespace System;

/*Utilizzo questa classe per ascoltare in modo asincrono i messaggi TCP ricevuti sulla porta 13000, i messaggi di presentazione degli ATO,
il messaggio ricevuto sarà trattato da ManagerMsgATO*/



/*-----------------------------------------------------------------------------------------------
L'ATS è in grado di ricevere messaggi di presentazione da parte di sistemi ATO
-------------------------------------------------------------------------------------------------*/

ref class ThreadPresentazione
{
private:
	 phisicalTrainList ^listaTreni;
	 ManagerMsgATO ^ManaMsgATO;
	 Int32 port;
public:
	
	ThreadPresentazione();
	ThreadPresentazione(phisicalTrainList ^lt, ManagerMsgATO ^MA);
	void TCP_Management_receive();
	
};
