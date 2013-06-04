#pragma once
#using <System.dll>
#include "..\\messaggi\\pacchettostatolineaatc.h"
#include "..\\scheduler\\ManagerStatoLineaIXL.h"


using namespace System;

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS è in grado di ricevere messaggi riguardanti lo stato della linea da parte del sistema ATC
-------------------------------------------------------------------------------------------------*/

ref class ThreadListenerATC_IXL
{
	static ManagerStatoLineaIXL ^ManStatoLineaIXL;
	
	static bool isMessageReceived;
public:
	/*ThreadListenerATC_IXL();*/
	ThreadListenerATC_IXL(ManagerStatoLineaIXL ^MC);

	void UDP_Management_receive();
	

    static void ReceiveCallback(IAsyncResult^ asyncResult);
	/*delegate void SetCallback(Messaggi ^msg);
	SetCallback^ myDelegate;
	void SetManager(Messaggi ^msg);*/
};

