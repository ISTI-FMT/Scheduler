#pragma once
#include "utility.h"
#include "StateCDB.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;
/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS riceve dall'IXl messaggi contenenti informazioni relative allo stato della linea
-------------------------------------------------------------------------------------------------*/

ref class pacchettoStatoLineaIXL
{
	unsigned int NID_PACKET ;
	unsigned int L_PACKET ;
	StateCDB ^sCDB;
	unsigned int N_ITER;
	List<StateCDB^> ^vStatoCDB;
public:
	pacchettoStatoLineaIXL(void);

	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};
	
	void setfirstCDB(StateCDB ^scdb){sCDB=scdb;};
	StateCDB ^getfirstCDB(){return sCDB;};

	void setlastCDB(List< StateCDB^> ^all){vStatoCDB=all;};
	List< StateCDB^> ^getlastCDB(){return vStatoCDB;};

	void setlastCDB( StateCDB^ one){vStatoCDB->Add(one);};
	

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buffer);
	void deserialize(byte *buffer);

	/*int Size(){
		int sizecdb = statoCDB->Size();
		return 8+13+16+sizecdb+(sizecdb*N_ITER);}*/
	virtual System::String ^ToString() override;
};

