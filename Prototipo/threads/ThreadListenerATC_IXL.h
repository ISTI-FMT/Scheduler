#pragma once
#using <System.dll>
#include "..\\messaggi\\pacchettostatolineaatc.h"
#include "..\\scheduler\\ManagerCDBIXL.h"
#include "..\\scheduler\\ManagerItinerarioIXL.h"

using namespace System;

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS è in grado di ricevere messaggi riguardanti lo stato della linea da parte del sistema ATC
-------------------------------------------------------------------------------------------------*/

ref class ThreadListenerATC_IXL
{
	static ManagerCDBIXL ^ManCDB;
	static ManagerItinerarioIXL ^ManIT;
	static bool isMessageReceived;
public:
	/*ThreadListenerATC_IXL();*/
	ThreadListenerATC_IXL(ManagerCDBIXL ^MC, ManagerItinerarioIXL ^MI);

	void UDP_Management_receive();
	

    static void ReceiveCallback(IAsyncResult^ asyncResult);
	/*delegate void SetCallback(Messaggi ^msg);
	SetCallback^ myDelegate;
	void SetManager(Messaggi ^msg);*/
};

