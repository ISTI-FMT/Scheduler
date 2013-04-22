#pragma once
ref class ThreadListenerATC
{
public:
	ThreadListenerATC();

	static void TCP_Management_receive();
	static void stampaBuffer(byte *buff, int nBit);
};

