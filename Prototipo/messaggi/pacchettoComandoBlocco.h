#pragma once
#include "utility.h"


/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto comando blocco che l'ATS invia dal IXL
nel messaggio di Comando Direzione del Blocco, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/


/*-----------------------------------------------------------------------------------------------
questa classe rappresenta un Pacchetto per eseguire dei comandi sui blocchi
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

	// funzione che restituisce la dimensione 
	int getSize();
	void serialize(array<Byte>^buffer);
	void deserialize(array<Byte>^buffer);

	~pacchettoComandoBlocco(void);

	virtual System::String ^ToString() override;
};

