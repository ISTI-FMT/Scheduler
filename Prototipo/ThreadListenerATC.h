#pragma once
#include "pacchettostatolineaatc.h"
ref class ThreadListenerATC
{
public:
	ThreadListenerATC();

	static void UDP_Management_receive();
	static void stampaBuffer(byte *buff, int nBit);
	
};

