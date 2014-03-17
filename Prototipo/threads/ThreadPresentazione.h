#pragma once
/*#include "..\\phisicalTrainList.h"*/
#include "..\\manager\\ManagerMsgATO.h"

#using <System.dll>
using namespace System;

/*Utilizzo questa classe per ascoltare in modo asincrono i messaggi TCP ricevuti sulla porta 13000, i messaggi di presentazione degli ATO,
il messaggio ricevuto sar� trattato da ManagerMsgATO*/



/*-----------------------------------------------------------------------------------------------
L'ATS � in grado di ricevere messaggi di presentazione da parte di sistemi ATO
-------------------------------------------------------------------------------------------------*/

public ref class ThreadPresentazione
{
private:
	/* phisicalTrainList ^listaTreni;*/
	 ManagerMsgATO ^ManaMsgATO;
	 Int32 port;
	 bool _shouldStop;
public:
	
	/*ThreadPresentazione();*/
	ThreadPresentazione(/*phisicalTrainList ^lt,*/ ManagerMsgATO ^MA);
	void TCP_Management_receive();
	void RequestStop();
	
};
