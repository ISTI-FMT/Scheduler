#pragma once
#include "utility.h"
#include "StateCDB.h"
#include "pacchettoBase.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto Stato della Linea che l'ATS riceve dal IXL
nel messaggio di stato della linea, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/


/*-----------------------------------------------------------------------------------------------
questa classe rappresenta un Pacchetto per ricevere informazioni sullo stato dei CDB dall'IXL
L'ATS riceve dall'IXl messaggi contenenti informazioni relative allo stato della linea
-------------------------------------------------------------------------------------------------*/

ref class pacchettoStatoLineaIXL : pacchettoBase
{
	int L_PACKET ;
	
	int N_ITER;
	List<StateCDB^> ^vStatoCDB;
public:
	pacchettoStatoLineaIXL(void);

	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};
	
	

	void setCDB(List< StateCDB^> ^all){vStatoCDB=all;};
	List< StateCDB^> ^getCDB(){return vStatoCDB;};

	void setCDB( StateCDB ^one){vStatoCDB->Add(one);};
	

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;

	/*int Size(){
		int sizecdb = statoCDB->Size();
		return 8+13+16+sizecdb+(sizecdb*N_ITER);}*/
	virtual System::String ^ToString() override;
};

