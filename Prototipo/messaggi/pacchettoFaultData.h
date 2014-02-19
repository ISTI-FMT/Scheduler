#pragma once
#include "utility.h"
#include "Fault.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto Fault Data che l'ATS riceve dal IXL o ATO
nel messaggio di Fault Reporting, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/


/*-----------------------------------------------------------------------------------------------
questa classe rappresenta un Pacchetto Fault Data
L'ATS riceve dall'IXl messaggi di fault reporting con cui l'IXL comunica l'occorrenza di guasti
-------------------------------------------------------------------------------------------------*/

ref class pacchettoFaultData
{
	int NID_PACKET ;
	int L_PACKET ;
	Fault ^guasto;
	int N_ITER ;
	List<Fault^> ^vGuasto;
public:
	pacchettoFaultData(void);
	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};
	

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sar� chiamata da chi vorr� serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(array<Byte>^buffer);
	void deserialize(array<Byte>^buffer);

	virtual System::String ^ToString() override;
};
