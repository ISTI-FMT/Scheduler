#pragma once
#include "utility.h"
#include "ProfiloVelocita.h"
#include "Mission.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS manda una missione al treno la missione da eseguire specificandola all'interno di un messaggio 
mission plan
-------------------------------------------------------------------------------------------------*/

ref class pacchettoMissionPlan
{
	unsigned int NID_PACKET ;
	unsigned int L_PACKET;
	unsigned int Q_SCALE ;
	ProfiloVelocita ^mS1;
	unsigned int N_ITER1;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	List<ProfiloVelocita^>^mS1_vect;
	Mission ^mS2;
	unsigned int N_ITER2;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	List<Mission^>^mS2_vect;
public:
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serializeMissionPlanPkt(byte *buff);
	void deserializeMissionPlanPkt(byte *buff);
	pacchettoMissionPlan();
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	
	void setNID_PACKET(int NID){NID_PACKET = NID;};
	int getNID_PACKET(){return NID_PACKET;};
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
	
	void setfirstPV(ProfiloVelocita ^PV){mS1=PV;};
	ProfiloVelocita ^getfirstPV(){return mS1;};

	void setlistPV(List< ProfiloVelocita^> ^all){mS1_vect=all;};
	List< ProfiloVelocita^> ^getlistPV(){return mS1_vect;};

	void setlistPV( ProfiloVelocita^ one){mS1_vect->Add(one);};
	
	void setfirstMission(Mission ^M){mS2=M;};
	Mission ^getfirstMission(){return mS2;};

	void setlistPV(List< Mission^> ^all){mS2_vect=all;};
	List< Mission^> ^getlistMission(){return mS2_vect;};

	void setlistMission( Mission^ one){mS2_vect->Add(one);};
	
		virtual System::String ^ToString() override;
};

