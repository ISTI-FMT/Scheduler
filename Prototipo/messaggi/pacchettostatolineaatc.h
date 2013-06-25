#pragma once
#include "utility.h"
#include "StateCDB.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;


ref class pacchettostatolineaatc
{
	unsigned int NID_PACKET;
	unsigned int L_PACKET ;
	unsigned int NID_OPERATIONAL ;
	
	unsigned int N_ITER ;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	List< StateCDB^> ^pstato;
public:
	pacchettostatolineaatc();
	
	
	
public:
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buff);
	void deserialize(byte *buff);
	
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	

	void setNID_PACKET(int NID){NID_PACKET = NID;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	void setNID_OPERATIONAL(int NID){NID_OPERATIONAL = NID;};
	int getNID_OPERATIONAL(){return NID_OPERATIONAL;};

	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};

	

	void setCDB(List< StateCDB^> ^all){pstato=all;};
	List< StateCDB^> ^getCDB(){return pstato;};

	void setCDB(StateCDB ^one){pstato->Add(one);};



	/*void setNID_CDB(int index, int NID);
	int getNID_CDB(int index);
	void setQ_DEVIATIOIO(int index, int Q);
	int getQ_DEVIATIOIO(int index);
	void setQ_STATOCDB(int index, int Q);
	int getQ_STATOCDB(int index);*/

	System::String^ toPrint();

};

