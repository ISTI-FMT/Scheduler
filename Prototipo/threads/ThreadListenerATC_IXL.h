#pragma once
#using <System.dll>
#include "..\\messaggi\\pacchettostatolineaatc.h"
#include "..\\manager\\ManagerStatoLineaIXL.h"
#include "..\\manager\\ManagerStatoLineaATC.h"
#include "..\\ParalellMethod.h"

using namespace System;


/*Utilizzo questa classe per ascoltare in modo asincrono i messaggi UDP ricevuti sulla porta 23002
a secondo del tipo di messaggio ricevuto sarà trattato da ManagerStatoLineaATC o ManagerStatoLineaIXL*/


/*-----------------------------------------------------------------------------------------------
L'ATS è in grado di ricevere messaggi riguardanti lo stato della linea da parte del sistema ATC e IXL
-------------------------------------------------------------------------------------------------*/

public ref class ThreadListenerATC_IXL
{
	static ManagerStatoLineaIXL ^ManStatoLineaIXL;
	static ManagerStatoLineaATC ^ManStatoLineaATC;
	static int port;
	static bool isMessageReceived;
	static bool _shouldStop;
	static array<Byte>^ end_byte_old;
	static array<Byte>^ end_byte_old_ATC;
	
public:
	/*ThreadListenerATC_IXL();*/
	ThreadListenerATC_IXL(ManagerStatoLineaIXL ^MC, ManagerStatoLineaATC ^MA);

	void UDP_Management_receive();
	

    static void ReceiveCallback(IAsyncResult^ asyncResult);
	static void RequestStop();
	static bool ConfrontaArrayByte(array<Byte>^A,array<Byte>^B);
	/*delegate void SetCallback(Messaggi ^msg);
	SetCallback^ myDelegate;
	void SetManager(Messaggi ^msg);*/
};

