#pragma once
#include "..\\messaggi\\pacchettostatolineaatc.h"
ref class ThreadListenerATC
{
public:
	ThreadListenerATC();

	static void UDP_Management_receive();
	static void stampaBuffer(byte *buff, int nBit);
	
};

