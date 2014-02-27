#pragma once
#include "utility.h"
#include "StateBlocco.h"
#include "pacchettoBase.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto Stato Blocco che l'ATS riceve dal IXL
nel messaggio di stato della linea, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/


/*-----------------------------------------------------------------------------------------------
questa classe rappresenta un Pacchetto per ricevere informazioni sullo stato del blocco
L'ATS riceve dall'IXl messaggi contenenti informazioni relative allo stato dei blocchi
-------------------------------------------------------------------------------------------------*/

ref class pacchettoStatoBlocco : pacchettoBase
{
	int L_PACKET ;
	int N_ITER ;
	List<StateBlocco^> ^vStatoBlocco;
public:
	pacchettoStatoBlocco(void);

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
	// questa funzione sar� chiamata da chi vorr� serializzare il messaggio, per poter allocare il buffer
	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;

	virtual System::String ^ToString() override;
};

