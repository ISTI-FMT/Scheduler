#pragma once
#using <System.dll>
#include "..\\messaggi\\pacchettostatolineaatc.h"
using namespace System;
ref class ThreadListenerATC
{
public:
	ThreadListenerATC();

	static void UDP_Management_receive();
	static bool isMessageReceived;

    static void ReceiveCallback(IAsyncResult^ asyncResult);
};

