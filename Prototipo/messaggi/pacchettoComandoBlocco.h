#pragma once
#include "utility.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS invia all'IXl messaggi contenenti comandi sui blocchi
-------------------------------------------------------------------------------------------------*/
enum  typeCmdBlocco { direzionelegale = 1, direzioneillegale = 0};

ref class pacchettoComandoBlocco
{
	unsigned int NID_PACKET ;
	unsigned int L_PACKET ;
	unsigned int NID_BLOCCO ;
	unsigned int Q_CMDBLOCCO ;
public:
	pacchettoComandoBlocco(void);

	void setNID_PACKET(int N){NID_PACKET = N;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setNID_BLOCCO(int N){NID_BLOCCO = N;};
	int getNID_BLOCCO(){return NID_BLOCCO;};
	void setQ_CMDBLOCCO(int Q){Q_CMDBLOCCO = Q;};
	int getQ_CMDBLOCCO(){return Q_CMDBLOCCO;};

	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serialize(byte *buffer);
	void deserialize(byte *buffer);

	~pacchettoComandoBlocco(void);

	virtual System::String ^ToString() override;
};

