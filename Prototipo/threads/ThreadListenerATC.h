#pragma once
#using <System.dll>
#include "..\\messaggi\\pacchettostatolineaatc.h"
using namespace System;

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS è in grado di ricevere messaggi riguardanti lo stato della linea da parte del sistema ATC
-------------------------------------------------------------------------------------------------*/

ref class ThreadListenerATC
{
public:
	ThreadListenerATC();

	static void UDP_Management_receive();
	static bool isMessageReceived;

    static void ReceiveCallback(IAsyncResult^ asyncResult);
};

