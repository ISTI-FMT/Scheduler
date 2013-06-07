#pragma once
#include "Fermata.h"
#include "..\\messaggi\\pacchettoMissionPlan.h"
#include "..\\Itinerari\\tabellaItinerari.h"

#using <System.dll>
using namespace System::Collections::Generic;

/*---------------------------------------------------------------------------------------------
Alessio:
L'ATS legge il contenuto della tabella orario da un file di configurazione e memorizza queste informazioni
in apposite strutture dati.
-------------------------------------------------------------------------------------------------*/

// Questa classe è utilizzata per gestire la tabella orario dell'ATS attraverso una lista di oggetti di tipo TrenoFermate
ref class TabellaOrario
{
	Dictionary<int, List<Fermata^>^> ^tabella;
	String ^schemaxsd;
	tabellaItinerari ^tabItinerari;
	
	// funzione che converte una System::String in un std::string
	// string convertiString2string(System::String ^StringValue);
	//friend ostream& operator<<(ostream &out, TabellaOrario &tabella);
public:
	TabellaOrario(void);
	TabellaOrario(tabellaItinerari ^T);
	Dictionary<int, List<Fermata^>^> ^ get_TabellaOrario(){return tabella;};
	// funzione che restituisce un qualsiasi TRN nella tabella orario (di fatto il primo)
	int getFirstTRN();
	// questa funzione legge il file di configurazione contenente la descrizione della tabella orario
	void leggiTabellaOrario(String ^nomeFile);
	// funzione che prende in ingresso un TRN ed un messaggio di tipo missionPlan, e riempie i campi del messaggio con i dati relativi
	// alla missione associata al TRN in questione
	void setMissionPlanMessage(int TRN, pacchettoMissionPlan ^pkt);
	
	List<Fermata^>^getItinerariFor(int TRN);

	//TrenoFermate^ getTrenoFermate(int TRN);
	virtual System::String^ ToString() override;
};

