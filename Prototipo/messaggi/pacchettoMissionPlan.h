#pragma once
#include "struttureDatiMessaggi.h"

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS manda una missione al treno la missione da eseguire specificandola all'interno di un messaggio 
mission plan
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
	
	System::String ^ ToString(){


		System::String ^out;

		out = out+"NID_PACKET: "+data.missionHead.NID_PACKET+";";
		out = out+"L_PACKET: "+data.missionHead.L_PACKET+";";
		out = out+"Q_SCALE: "+data.missionHead.Q_SCALE+";";
		out = out+"Q_SCALE: "+data.mS1.D_MISSION+";";
		out = out+"V_MISSION: "+data.mS1.V_MISSION+";";
		out = out+"N_ITER1: "+data.N_ITER1+";";
		if(data.mS1_vect){
			for(unsigned int i=0;i<data.N_ITER1;i++){
				out = out+"Q_SCALE: "+data.mS1_vect[i].D_MISSION+";";
				out = out+"V_MISSION: "+data.mS1_vect[i].V_MISSION+";";

			}
		}
		out = out+"T_START_TIME: "+data.mS2.T_START_TIME+";";
		out = out+"NID_LRGB: "+data.mS2.NID_LRGB+";";
		out = out+"D_STOP: "+data.mS2.D_STOP+";";
		out = out+"Q_DOORS: "+data.mS2.Q_DOORS+";";
		out = out+"T_DOORS_TIME: "+data.mS2.T_DOORS_TIME+";";

		out = out+"N_ITER2: "+data.N_ITER2+";";
		if(data.mS2_vect){
			for(unsigned int i=0;i<data.N_ITER2;i++){
				out = out+"T_START_TIME: "+data.mS2_vect[i].T_START_TIME+";";
				out = out+"NID_LRGB: "+data.mS2_vect[i].NID_LRGB+";";
				out = out+"D_STOP: "+data.mS2_vect[i].D_STOP+";";
				out = out+"Q_DOORS: "+data.mS2_vect[i].Q_DOORS+";";
				out = out+"T_DOORS_TIME: "+data.mS2_vect[i].T_DOORS_TIME+";";
			}
		}

		return out;
	};
};

