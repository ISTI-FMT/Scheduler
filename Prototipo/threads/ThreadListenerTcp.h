#pragma once
#include "..\\manager\\ManagerMsgATO.h"

#using <System.dll>
using namespace System;

/*
Ascolta in modo asincrono i messaggi TCP di presentazione degli ATO.
La porta di ascolto è letta dalla chiave di configurazione port_TCP_receive (default 13000)
*/

public ref class ThreadListenerTcp
{
private:
	 //Manager che gestisce i messaggi in arrivo dall'ATO
	 static ManagerMsgATO ^ManaMsgATO;
	 //Porta di ascolto. Default 13000
	 Int32 port;
	 //TRUE se la chiusura del thread è pending
	 bool _shouldStop;
public:
	ThreadListenerTcp(ManagerMsgATO^ MA);
	void TCP_Management_receive();
	void RequestStop();
	static void ReceiveCallback(IAsyncResult^ asyncResult);
	
};
