#pragma once
#include "Fermata.h"
#include "..\\messaggi\\pacchettoMissionData.h"
#include "..\\Itinerari\\TabellaStazioni.h"

#using <System.dll>
using namespace System::Collections::Generic;

/*Utilizzo questa classe per serializzare le informazioni della tabella orario, 
la liste delle fermate viene inserita in una mappa la cui chiave è l'id della fermata.
La classe contiene anche un riferimento alle informazioni presenti in Configurazioneitinerari
per creare la missione per l'ATO
*/

public ref class TabellaOrario
{
	Dictionary<int, List<Fermata^>^> ^tabella;
	String ^schemaxsd;
	TabellaStazioni ^tabItinerari;
	
	
public:
	TabellaOrario(void);
	TabellaOrario(TabellaStazioni ^T);
	Dictionary<int, List<Fermata^>^> ^ get_TabellaOrario(){return tabella;};
	// funzione che restituisce un qualsiasi TRN nella tabella orario (di fatto il primo)
	int getFirstTRN();
	// questa funzione legge il file di configurazione contenente la descrizione della tabella orario
	void leggiTabellaOrario();
	void ScriviTabellaOrario();
	// funzione che prende in ingresso un TRN ed un messaggio di tipo missionPlan le informazioni sui profili velocità, e riempie i campi del messaggio con i dati relativi
	// al profilo missione associato al TRN passato
	void setMissionPlanMessage(int TRN, pacchettoMissionData ^pkt, List<ProfiloVelocita^>^pvel);
	// funzione che prende in ingresso un TRN ed un messaggio di tipo missionPlan le informazioni sui profili velocità e la lista della fermate, e crea
	// il profilo missione per l'ato
	void createMissionPlanMsg(int TRN, pacchettoMissionData ^pkt, List<ProfiloVelocita^>^pvel, List<Fermata^> ^stops);
	List<Fermata^>^getItinerariFor(int TRN);
	List<Fermata^>^getFermateFor(int TRN);

	
	virtual System::String^ ToString() override;
};

