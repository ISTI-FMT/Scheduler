#pragma once
#include "utility.h"
#include "StateBlocco.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;
/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS riceve dall'IXl messaggi contenenti informazioni relative allo stato dei blocchi
-------------------------------------------------------------------------------------------------*/

ref class pacchettoStatoBlocco
{
	unsigned int NID_PACKET ;
	unsigned int L_PACKET ;
	unsigned int N_ITER ;
	List<StateBlocco^> ^vStatoBlocco;
public:
	pacchettoStatoBlocco(void);

	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};

	

	void setStatoBlocco(List< StateBlocco^> ^all){vStatoBlocco=all;};
	List< StateBlocco^> ^getStatoBlocco(){return vStatoBlocco;};

	void setStatoBlocco( StateBlocco^ one){vStatoBlocco->Add(one);};

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buffer, int offset);
	void deserialize(byte *buffer, int offset);

	virtual System::String ^ToString() override;
};

