#pragma once
#include "struttureDatiMessaggi.h"

class pacchettoMissionPlan
{
	missionData data;
	// funzioni di supporto alla serializzazione del messaggio in un buffer di byte
	// ogni funzione serializza un pezzo del messaggio
	// ogni funzione prende in ingresso un buffer precedentemente correttamente allocato,
	// l'oggetto da serializzare ed il numero di bit gi� precedentemente serializzati nel buffer. 
	// All'uscita dalla funzione tale indice sar� incrementato del numero di bit derializzato dalla
	// funzione stessa.
	void serializeStructuredHeader(byte *buff, structuredHeader &h, int &index);
	void serializeMissionStruct1(byte *buff, missionStruct1 &ms, int &index);
	void serializeMissionStruct2(byte *buff, missionStruct2 &ms, int &index);
public:
	// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
	// fatti dal compilatore) in byte del messaggio tenendo anche in conto l'eventuale padding
	// questa funzione sar� chiamata da chi vorr� serializzare il messaggio, per poter allocare il buffer
	int getSize();
	void serializeStructuredHeader(byte *buff, int &index){serializeStructuredHeader(buff, data.head, index);};
	pacchettoMissionPlan();
	// funzioni di interfaccia set e get per ogni campo dati del pacchetto
	void setNID_MESSAGE(int N){data.head.NID_MESSAGE = N;};
	int getNID_MESSAGE(){return data.head.NID_MESSAGE;};
	void setL_MESSAGE(int N){data.head.L_MESSAGE = N;};
	int getL_MESSAGE(){return data.head.L_MESSAGE;};
	void setT_TRAIN(int N){data.head.T_TRAIN = N;};
	int getT_TRAIN(){return data.head.T_TRAIN;};
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
	// se index � 0, il metodo modificher� i dati relativi alla stazioen di partenza, altrimenti modificher� i dati 
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

