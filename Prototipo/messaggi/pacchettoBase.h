#pragma once
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/* Questa classe astratta contiene metodi e informazioni comuni a tutti i pacchetti inviati e ricevuti dall'ATS.
E' implementata da ogni classe pacchetto, che aggiunge le informazioni aggiuntive e gestisce la loro serializzazione/deserializzazione */

ref class pacchettoBase abstract
{
protected:
	pacchettoBase();
	//ID univoco di pacchetto
	int NID_PACKET;
	void setNID_PACKET(int id)
	{
		NID_PACKET = id;
	};
public:
	int get_NID_PACKET()
	{
		return NID_PACKET;
	};

	//serializza i campi del pacchetto in un buffer.
	//il buffer di byte deve essere stato precedentemente correttamente allocato.
	virtual void serialize(array<Byte>^buff, int offset) abstract;

	//popola i campi del pacchetto a partire dai dati serializzati
	//il buffer di byte deve essere stato precedentemente correttamente allocato.
	virtual void deserialize(array<Byte>^buff, int offset) abstract;

	// funzione che restituisce la dimensione in bit (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	virtual int getSize() abstract;
	
};

