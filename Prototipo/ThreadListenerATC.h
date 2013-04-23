#pragma once
#include "pacchettostatolineaatc.h"
public class ThreadListenerATC
{
public:
	ThreadListenerATC();

	static void TCP_Management_receive();
	static void stampaBuffer(byte *buff, int nBit);
	
};

