#pragma once
#include "utility.h"
#include "StateCDB.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;


/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto Position Data che l'ATS riceve dal ATC
nel messaggio di stato della linea, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/


//questa classe rappresenta un Pacchetto per ricevere informazioni sullo stato dei CDB dall'ATC

ref class pacchettoPositionDataATC
{
	unsigned int NID_PACKET;
	unsigned int L_PACKET ;
	
	unsigned int N_ITER ;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	List< StateCDB^> ^ListPostionData;
public:
	pacchettoPositionDataATC();
	
	
	
public:
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(array<Byte>^buff);
	void deserialize(array<Byte>^buff);
	
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	

	void setNID_PACKET(int NID){NID_PACKET = NID;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};



	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};

	

	void setCDB(List< StateCDB^> ^all){ListPostionData=all;};
	List< StateCDB^> ^getListCDB(){return ListPostionData;};

	void setCDB(StateCDB ^one){ListPostionData->Add(one);};



	/*void setNID_CDB(int index, int NID);
	int getNID_CDB(int index);
	void setQ_DEVIATIOIO(int index, int Q);
	int getQ_DEVIATIOIO(int index);
	void setQ_STATOCDB(int index, int Q);
	int getQ_STATOCDB(int index);*/

	System::String^ toPrint();

};

