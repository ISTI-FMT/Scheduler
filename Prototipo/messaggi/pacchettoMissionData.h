#pragma once
#include "utility.h"
#include "ProfiloVelocita.h"
#include "Mission.h"
#include "pacchettoBase.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto MissionData che l'ATS invia dal ATO
nel messaggio di MissionPlan, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/



/*-----------------------------------------------------------------------------------------------
questa classe rappresenta un Pacchetto di Mission Data
L'ATS manda una missione al treno la missione da eseguire specificandola all'interno di un messaggio 
mission plan
-------------------------------------------------------------------------------------------------*/

ref class pacchettoMissionData : pacchettoBase
{
	int L_PACKET;
	int Q_SCALE ;
	
	int N_ITER1;
	// questo vettore verr� allocato con la new quando sar� noto il valore di N_ITER
	List<ProfiloVelocita^>^mS1_vect;

	int N_ITER2;
	// questo vettore verr� allocato con la new quando sar� noto il valore di N_ITER
	List<Mission^>^mS2_vect;
public:
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sar� chiamata da chi vorr� serializzare il messaggio, per poter allocare il buffer
	virtual int getSize() override;
	virtual void serialize(array<Byte>^buff, int offset) override;
	virtual void deserialize(array<Byte>^buff, int offset) override;
	pacchettoMissionData();
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setQ_SCALE(int Q){Q_SCALE = Q;};
	int getQ_SCALE(){return Q_SCALE;};
	// metodo che setta N_ITER1 ed alloca conseguentemente il vettore mS1_vect
	void setN_ITER1(int N);
	int getN_ITER1(){return N_ITER1;};
	// metodo che setta N_ITER2 ed alloca conseguentemente il vettore mS2_vect
	void setN_ITER2(int N);
	int getN_ITER2(){return N_ITER2;};
	
	

	void setPV(List< ProfiloVelocita^> ^all){mS1_vect=all;};
	List< ProfiloVelocita^> ^getPV(){return mS1_vect;};

	void setPV( ProfiloVelocita^ one){mS1_vect->Add(one);};
	
	

	void setMission(List< Mission^> ^all){mS2_vect=all;};
	List< Mission^> ^getlistMission(){return mS2_vect;};

	void setMission( Mission^ one){mS2_vect->Add(one);};
	
		virtual System::String ^ToString() override;
};

