#include "pacchettoMissionPlan.h"
#include <iostream>
using namespace std;


pacchettoMissionPlan::pacchettoMissionPlan()
{
	data.head.NID_MESSAGE = 0;
	data.head.L_MESSAGE = 0;
	data.head.T_TRAIN = 0;
	data.missionHead.structuredData.NID_PACKET = 0;
	data.missionHead.structuredData.L_PACKET = 0;
	data.missionHead.structuredData.Q_SCALE = 0;
	for(int i = 0; i < 3; ++i)
		data.mS1.flatData[i] = 0;
	data.N_ITER1 = 0;
	data.mS1_vect = NULL;
	for(int i = 0; i < 9; ++i)
		data.mS2.flatData[i] = 0;
	data.N_ITER2 = 0;
	data.mS2_vect = NULL;
}

// funzione che sette N_ITER
void pacchettoMissionPlan::setN_ITER(int N)
{
	data.N_ITER1 = N;
	data.N_ITER2 = N;
	data.mS1_vect = new missionStruct1[N];
	data.mS2_vect = new missionStruct2[N];
}

void pacchettoMissionPlan::setD_MISSION(int index, int D)
{
	if(index == 0)
		data.mS1.structuredData.D_MISSION = D;
	else
		data.mS1_vect[index - 1].structuredData.D_MISSION = D;
}

int pacchettoMissionPlan::getD_MISSION(int index)
{
	if(index == 0)
		return data.mS1.structuredData.D_MISSION;
	else
		return data.mS1_vect[index - 1].structuredData.D_MISSION;
}

void pacchettoMissionPlan::setV_MISSION(int index, int V)
{
	if(index == 0)
		data.mS1.structuredData.V_MISSION = V;
	else
		data.mS1_vect[index - 1].structuredData.V_MISSION = V;
}

int pacchettoMissionPlan::getV_MISSION(int index)
{
	if(index == 0)
		return data.mS1.structuredData.V_MISSION;
	else
		return data.mS1_vect[index - 1].structuredData.V_MISSION;
}

void pacchettoMissionPlan::setT_START_TIME(int index, int T)
{
	if(index == 0)
		data.mS2.structuredData.T_START_TIME = T;
	else
		data.mS2_vect[index - 1].structuredData.T_START_TIME = T;
}

int pacchettoMissionPlan::getT_START_TIME(int index)
{
	if(index == 0)
		return data.mS2.structuredData.T_START_TIME;
	else
		return data.mS2_vect[index - 1].structuredData.T_START_TIME;
}

void pacchettoMissionPlan::setNID_LRGB(int index, int NID)
{
	if(index == 0)
		data.mS2.structuredData.NID_LRGB = NID;
	else
		data.mS2_vect[index - 1].structuredData.NID_LRGB = NID;
}

int pacchettoMissionPlan::getNID_LRGB(int index)
{
	if(index == 0)
		return data.mS2.structuredData.NID_LRGB;
	else
		return data.mS2_vect[index - 1].structuredData.NID_LRGB;
}

void pacchettoMissionPlan::setD_STOP(int index, int D)
{
	if(index == 0)
		data.mS2.structuredData.D_STOP = D;
	else
		data.mS2_vect[index - 1].structuredData.D_STOP = D;
}

int pacchettoMissionPlan::getD_STOP(int index)
{
	if(index == 0)
		return data.mS2.structuredData.D_STOP;
	else
		return data.mS2_vect[index - 1].structuredData.D_STOP;
}

void pacchettoMissionPlan::setQ_DOORS(int index, int Q)
{
	if(index == 0)
		data.mS2.structuredData.Q_DOORS = Q;
	else
		data.mS2_vect[index - 1].structuredData.Q_DOORS = Q;
}

int pacchettoMissionPlan::getQ_DOORS(int index)
{
	if(index == 0)
		return data.mS2.structuredData.Q_DOORS;
	else
		return data.mS2_vect[index - 1].structuredData.Q_DOORS;
}

void pacchettoMissionPlan::setT_DOORS_TIME(int index, int T)
{
	if(index == 0)
		data.mS2.structuredData.T_DOORS_TIME = T;
	else
		data.mS2_vect[index - 1].structuredData.T_DOORS_TIME = T;
}

int pacchettoMissionPlan::getT_DOORS_TIME(int index)
{
	if(index == 0)
		return data.mS2.structuredData.T_DOORS_TIME;
	else
		return data.mS2_vect[index - 1].structuredData.T_DOORS_TIME;
}

void pacchettoMissionPlan::serializeStructuredHeader(byte *buff, structuredHeader &h, int &index)
{
	byte mask;
	// serializzo NID_MESSAGE (che è esattamente un byte)
	buff[index/8] = h.NID_MESSAGE;
	index += 8;
	// serializzo i primi 8 bit di L_MESSAGE
	//while(index < 16)
	//{
		// con (1 << (index - 8)) costruisco una maschera con tutti 0 e un 1 
		// nella posizione desiderata
		// poi devo sciftare a destra per riportare il byte che voglio serializzare
		// nella posizione meno significativa
		//mask = (h.L_MESSAGE >> (8)) & (1 << (index - 8));
		mask = h.L_MESSAGE >> 3;
		// con l'or bit a bit modifico il contenuto del buffer
		buff[(index/8)] |= mask;
		index += 8;
	//}
	// serializzo i rimanenti 3 bit di L_MESSAGE
	//while(index < 19)
	//{
		// con (1 << (index - 8)) costruisco una maschera con tutti 0 e un 1 
		// nella posizione desiderata
		// poi devo sciftare a destra per riportare il byte che voglio serializzare
		// nella posizione meno significativa
		//mask = (h.L_MESSAGE & (1 << (index - 16))) << (5 + (index%8));
		mask = h.L_MESSAGE << 1;
		// con l'or bit a bit modifico il contenuto del buffer
		buff[(index/8)] |= mask;
		index += 3;
	//}
	/*
	// serializzo T_TRAIN
	for(int i = 3; i >= 0; --i)
	{
		for(int j = 0; j < 8; ++j)
		{
			// con (1 << (index - 19)) costruisco una maschera con tutti 0 e un 1 
			// nella posizione desiderata
			// poi devo sciftare a destra per riportare il byte che voglio serializzare
			// nella posizione meno significativa
			mask = (h.T_TRAIN & (1 << (index - 19))) >> (i*8);
			// con l'or bit a bit modifico il contenuto del buffer
			buff[index/8] |= mask;
			++index;
		}
	}
	*/


	/*
	// serializzo i primi 5 bit di T_TRAIN
	while(index < 24)
	{
		// con (1 << (index - 19)) costruisco una maschera con tutti 0 e un 1 
		// nella posizione desiderata
		// poi devo sciftare a destra per riportare il byte che voglio serializzare
		// nella posizione meno significativa
		mask = (h.T_TRAIN & (1 << (index - 19))) >> (0);
		// con l'or bit a bit modifico il contenuto del buffer
		buff[2] |= mask;
		++index;
	}
	// serializzo i tre byte "centrali" di T_TRAIN
	for(int i = 3; i < 6; ++i)
	{
		//while(index < 24)
		for(int j = 0; j < 8; ++j)
		{
			// con (1 << (index - 19)) costruisco una maschera con tutti 0 e un 1 
			// nella posizione desiderata
			// poi devo sciftare a destra per riportare il byte che voglio serializzare
			// nella posizione meno significativa
			int offset;
			if()
			mask = (h.T_TRAIN & (1 << j)) >> (0);
			buff[i] |= mask;
			++index;
		}
	}
	// serializzo gli ultimi 3 bit di T_TRAIN
	while(index < 51)
	{
		mask = h.T_TRAIN & (1 << (index - 19));
		buff[6] |= mask;
		++index;
	}
	*/
}

pacchettoMissionPlan::~pacchettoMissionPlan(void)
{
	delete data.mS1_vect;
	delete data.mS2_vect;
}