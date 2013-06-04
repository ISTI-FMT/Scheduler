#pragma once
#include "utility.h"


/*-----------------------------------------------------------------------------------------------
L'ATS riceve dal treno dei messaggi di 
-------------------------------------------------------------------------------------------------*/

ref class pacchettopresentazione
{
	unsigned int NID_PACKET;
	unsigned int L_PACKET;
	unsigned int M_PORT;
public:
	pacchettopresentazione(void);
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize(){return 53;};
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto


	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setM_PORT(int Q){M_PORT = Q;};
	int getM_PORT(){return M_PORT;};
	// metodi per la serializzazione e deserializzazione del messaggio
	// il buffer di byte deve essere stato precedentemente correttamente allocato.
	void serialize(byte *buff);
	void deserialize(byte *buff);
	

	virtual System::String ^ToString() override;
};

