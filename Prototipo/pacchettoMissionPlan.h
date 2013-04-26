#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
L'ATS manda una missione al treno
-------------------------------------------------------------------------------------------------*/

class pacchettoMissionPlan
{
	missionData data;
public:
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serializeMissionPlanPkt(byte *buff);
	void deserializeMissionPlanPkt(byte *buff);
	pacchettoMissionPlan();
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	
	void setNID_PACKET(int NID){data.missionHead.NID_PACKET = NID;};
	int getNID_PACKET(){return data.missionHead.NID_PACKET;};
	void setL_PACKET(int L){data.missionHead.L_PACKET = L;};
	int getL_PACKET(){return data.missionHead.L_PACKET;};
	void setQ_SCALE(int Q){data.missionHead.Q_SCALE = Q;};
	int getQ_SCALE(){return data.missionHead.Q_SCALE;};
	// metodo che setta N_ITER1 ed alloca conseguentemente il vettore mS1_vect
	void setN_ITER1(int N);
	int getN_ITER1(){return data.N_ITER1;};
	// metodo che setta N_ITER2 ed alloca conseguentemente il vettore mS2_vect
	void setN_ITER2(int N);
	int getN_ITER2(){return data.N_ITER2;};
	// in questi metodi index rappresenta l'indice della fermata di cui si vogliono leggere/scrivere le caratteristiche
	// se index è 0, il metodo modificherà i dati relativi alla stazioen di partenza, altrimenti modificherà i dati 
	// relativi alle altre fermate.
	void setD_MISSION(int index, int D);
	int getD_MISSION(int index);
	void setV_MISSION(int index, int V);
	int getV_MISSION(int index);
	void setT_START_TIME(int index, int T);
	int getT_START_TIME(int index);
	void setNID_LRGB(int index, int NID);
	int getNID_LRGB(int index);
	void setD_STOP(int index, int D);
	int getD_STOP(int index);
	void setQ_DOORS(int index, int Q);
	int getQ_DOORS(int index);
	void setT_DOORS_TIME(int index, int T);
	int getT_DOORS_TIME(int index);
	// funzione che serializza il messaggio....il buffer deve contenere tutti 0 prima di invoca il metodo.
	~pacchettoMissionPlan(void);
};

