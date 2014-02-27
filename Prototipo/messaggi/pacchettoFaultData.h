#pragma once
#include "utility.h"
#include "Fault.h"
#include "pacchettoBase.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto Fault Data che l'ATS riceve dal IXL o ATO
nel messaggio di Fault Reporting, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/


/*-----------------------------------------------------------------------------------------------
questa classe rappresenta un Pacchetto Fault Data
L'ATS riceve dall'IXl messaggi di fault reporting con cui l'IXL comunica l'occorrenza di guasti
-------------------------------------------------------------------------------------------------*/

ref class pacchettoFaultData : pacchettoBase
{
	int L_PACKET ;
	Fault ^guasto;
	int N_ITER ;
	List<Fault^> ^vGuasto;
public:
	//Costruttore che accetta l'id del pacchetto.
	//FaultData può avere id diversi a seconda dell'utilizzo
	pacchettoFaultData(int ID_PACKET);
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;

	virtual System::String ^ToString() override;
};
