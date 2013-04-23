#pragma once
#include "pacchettostatolineaatc.h"
#include "pacchettoAcknowledgement.h"
#include "pacchettoCommandData1.h"
#include "pacchettopresentazione.h"

ref class proveSerializzazione
{
public:
	proveSerializzazione(void);
	void provaSerializePacchettostatolineaatc(pacchettostatolineaatc &pkt, int index);
	void provaSerializePacchettoPresentazione(pacchettopresentazione &pkt);
	void provaSerializePacchettoack(pacchettoAcknowledgement &pkt);
	void provaSerializePacchettoCommandData1(pacchettoCommandData1 &pkt);



};

