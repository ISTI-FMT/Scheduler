#pragma once
#include "utility.h"
#include "StateSegnale.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto Stato Segnali che l'ATS riceve dal IXL
nel messaggio di stato della linea, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/


/*-----------------------------------------------------------------------------------------------
questa classe rappresenta un Pacchetto per ricevere informazioni sullo stato dei segnali
L'ATS riceve dall'IXL messaggi contenenti informazioni relative allo stato degi segnali
-------------------------------------------------------------------------------------------------*/

ref class pacchettoStatoSegnali
{
	unsigned int NID_PACKET ;
	unsigned int L_PACKET ;
	unsigned int N_ITER ;
	List<StateSegnale^> ^vStatoSegnale;
public:
	pacchettoStatoSegnali(void);

	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};



	void setstatoSegnale(List< StateSegnale^> ^all){vStatoSegnale=all;};
	List< StateSegnale^> ^getstatoSegnale(){return vStatoSegnale;};

	void setstatoSegnale( StateSegnale^ one){vStatoSegnale->Add(one);};
	

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(array<Byte>^buffer, int offset);
	void deserialize(array<Byte>^buffer, int offset);

	virtual System::String ^ToString() override;
};

