#pragma once
#using <System.dll>
#include "..\\messaggi\\pacchettostatolineaatc.h"
#include "..\\manager\\ManagerStatoLineaIXL.h"
#include "..\\manager\\ManagerStatoLineaATC.h"
#include "..\\ParalellMethod.h"

using namespace System;

/*
Ascolta in modo asincrono i messaggi UDP dall'ATC e IXL
La porta di ascolto è letta dalla chiave di configurazione port_UDP_receive (default 4010)
*/

public ref class ThreadListenerUdp
{
	//Manager che gestisce i messaggi in arrivo dall'IXL
	static ManagerStatoLineaIXL ^ManStatoLineaIXL;
	//Manager che gestisce i messaggi in arrivo dall'ATC
	static ManagerStatoLineaATC ^ManStatoLineaATC;
	//Porta di ascolto. Default 4010
	static int port;
	static bool isMessageReceived;
	//TRUE se la chiusura del thread è pending
	static bool _shouldStop;
	static array<Byte>^ end_byte_old_IXL;
	static array<Byte>^ end_byte_old_ATC;
	
public:
	ThreadListenerUdp(ManagerStatoLineaIXL ^MC, ManagerStatoLineaATC ^MA);
	void UDP_Management_receive();
    static void ReceiveCallback(IAsyncResult^ asyncResult);
	static void RequestStop();
	static bool ConfrontaArrayByte( array<Byte>^A, array<Byte>^B);
};

