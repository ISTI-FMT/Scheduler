#pragma once
#using <System.dll>
#include "..\\messaggi\\pacchettostatolineaatc.h"
#include "..\\manager\\ManagerStatoLineaIXL.h"
#include "..\\manager\\ManagerStatoLineaATC.h"


using namespace System;


/*Utilizzo questa classe per ascoltare in modo asincrono i messaggi UDP ricevuti sulla porta 23002
a secondo del tipo di messaggio ricevuto sarà trattato da ManagerStatoLineaATC o ManagerStatoLineaIXL*/


/*-----------------------------------------------------------------------------------------------
L'ATS è in grado di ricevere messaggi riguardanti lo stato della linea da parte del sistema ATC e IXL
-------------------------------------------------------------------------------------------------*/

ref class ThreadListenerATC_IXL
{
	static ManagerStatoLineaIXL ^ManStatoLineaIXL;
	static ManagerStatoLineaATC ^ManStatoLineaATC;
	static int port;
	static bool isMessageReceived;
public:
	/*ThreadListenerATC_IXL();*/
	ThreadListenerATC_IXL(ManagerStatoLineaIXL ^MC, ManagerStatoLineaATC ^MA);

	void UDP_Management_receive();
	

    static void ReceiveCallback(IAsyncResult^ asyncResult);
	/*delegate void SetCallback(Messaggi ^msg);
	SetCallback^ myDelegate;
	void SetManager(Messaggi ^msg);*/
};

