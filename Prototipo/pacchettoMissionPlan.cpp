#include "pacchettoMissionPlan.h"
#include "utility.h"
#include <iostream>
using namespace std;


pacchettoMissionPlan::pacchettoMissionPlan()
{
	
	data.missionHead.NID_PACKET = 0;
	data.missionHead.L_PACKET = 0;
	data.missionHead.Q_SCALE = 0;
	data.mS1.D_MISSION = 0;
	data.mS1.V_MISSION = 0;
	data.N_ITER1 = 0;
	data.mS1_vect = NULL;
	data.mS2.T_START_TIME = 0;
	data.mS2.NID_LRGB = 0;
	data.mS2.D_STOP = 0;
	data.mS2.Q_DOORS = 0;
	data.mS2.T_DOORS_TIME = 0;
	data.N_ITER2 = 0;
	data.mS2_vect = NULL;
}

// funzione che sette N_ITER1
void pacchettoMissionPlan::setN_ITER1(int N)
{
	data.N_ITER1 = N;
	data.mS1_vect = new missionStruct1[N];
}

// funzione che sette N_ITER2
void pacchettoMissionPlan::setN_ITER2(int N)
{
	data.N_ITER2 = N;
	data.mS2_vect = new missionStruct2[N];
}

void pacchettoMissionPlan::setD_MISSION(int index, int D)
{
	if(index == 0)
		data.mS1.D_MISSION = D;
	else
		data.mS1_vect[index - 1].D_MISSION = D;
}

int pacchettoMissionPlan::getD_MISSION(int index)
{
	if(index == 0)
		return data.mS1.D_MISSION;
	else
		return data.mS1_vect[index - 1].D_MISSION;
}

void pacchettoMissionPlan::setV_MISSION(int index, int V)
{
	if(index == 0)
		data.mS1.V_MISSION = V;
	else
		data.mS1_vect[index - 1].V_MISSION = V;
}

int pacchettoMissionPlan::getV_MISSION(int index)
{
	if(index == 0)
		return data.mS1.V_MISSION;
	else
		return data.mS1_vect[index - 1].V_MISSION;
}

void pacchettoMissionPlan::setT_START_TIME(int index, int T)
{
	if(index == 0)
		data.mS2.T_START_TIME = T;
	else
		data.mS2_vect[index - 1].T_START_TIME = T;
}

int pacchettoMissionPlan::getT_START_TIME(int index)
{
	if(index == 0)
		return data.mS2.T_START_TIME;
	else
		return data.mS2_vect[index - 1].T_START_TIME;
}

void pacchettoMissionPlan::setNID_LRGB(int index, int NID)
{
	if(index == 0)
		data.mS2.NID_LRGB = NID;
	else
		data.mS2_vect[index - 1].NID_LRGB = NID;
}

int pacchettoMissionPlan::getNID_LRGB(int index)
{
	if(index == 0)
		return data.mS2.NID_LRGB;
	else
		return data.mS2_vect[index - 1].NID_LRGB;
}

void pacchettoMissionPlan::setD_STOP(int index, int D)
{
	if(index == 0)
		data.mS2.D_STOP = D;
	else
		data.mS2_vect[index - 1].D_STOP = D;
}

int pacchettoMissionPlan::getD_STOP(int index)
{
	if(index == 0)
		return data.mS2.D_STOP;
	else
		return data.mS2_vect[index - 1].D_STOP;
}

void pacchettoMissionPlan::setQ_DOORS(int index, int Q)
{
	if(index == 0)
		data.mS2.Q_DOORS = Q;
	else
		data.mS2_vect[index - 1].Q_DOORS = Q;
}

int pacchettoMissionPlan::getQ_DOORS(int index)
{
	if(index == 0)
		return data.mS2.Q_DOORS;
	else
		return data.mS2_vect[index - 1].Q_DOORS;
}

void pacchettoMissionPlan::setT_DOORS_TIME(int index, int T)
{
	if(index == 0)
		data.mS2.T_DOORS_TIME = T;
	else
		data.mS2_vect[index - 1].T_DOORS_TIME = T;
}

int pacchettoMissionPlan::getT_DOORS_TIME(int index)
{
	if(index == 0)
		return data.mS2.T_DOORS_TIME;
	else
		return data.mS2_vect[index - 1].T_DOORS_TIME;
}

void pacchettoMissionPlan::serializeMissionPlanPkt(byte *buffer)
{
	
	push(buffer, data.missionHead.NID_PACKET, 8, 51);
	push(buffer, data.missionHead.L_PACKET, 13, 59);
	push(buffer, data.missionHead.Q_SCALE, 2, 72);
	push(buffer, data.mS1.D_MISSION, 15, 74);
	push(buffer, data.mS1.V_MISSION, 7, 89);
	push(buffer, data.N_ITER1, 5, 96);
	//data.mS1_vect = new missionStruct1[data.N_ITER1];
	int offset = 101;
	for(unsigned int i = 0; i < data.N_ITER1; ++i)
	{
		push(buffer, data.mS1_vect[i].D_MISSION, 15, offset);
		offset += 15;
		push(buffer, data.mS1_vect[i].V_MISSION, 7, offset);
		offset += 7;
	}
	push(buffer, data.mS2.T_START_TIME, 12, offset);
	offset += 12;
	push(buffer, data.mS2.NID_LRGB, 24, offset);
	offset += 24;
	push(buffer, data.mS2.D_STOP, 15, offset);
	offset += 15;
	push(buffer, data.mS2.Q_DOORS, 4, offset);
	offset += 4;
	push(buffer, data.mS2.T_DOORS_TIME, 12, offset);
	offset += 12;
	push(buffer, data.N_ITER2, 5, offset);
	offset += 5;
	//data.mS2_vect = new missionStruct2[data.N_ITER2];
	for(unsigned int i = 0; i < data.N_ITER2; ++i)
	{
		push(buffer, data.mS2_vect[i].T_START_TIME, 12, offset);
		offset += 12;
		push(buffer, data.mS2_vect[i].NID_LRGB, 24, offset);
		offset += 24;
		push(buffer, data.mS2_vect[i].D_STOP, 15, offset);
		offset += 15;
		push(buffer, data.mS2_vect[i].Q_DOORS, 4, offset);
		offset += 4;
		push(buffer, data.mS2_vect[i].T_DOORS_TIME, 12, offset);
		offset += 12;
	}
}

void pacchettoMissionPlan::deserializeMissionPlanPkt(byte *buffer)
{
	
	data.missionHead.NID_PACKET=pop(buffer,  8, 51);
	data.missionHead.L_PACKET=pop(buffer, 13, 59);
	data.missionHead.Q_SCALE=pop(buffer, 2, 72);
	data.mS1.D_MISSION=pop(buffer, 15, 74);
	data.mS1.V_MISSION=pop(buffer, 7, 89);
	setN_ITER1(pop(buffer, 5, 96));
	int offset = 101;
	for(unsigned int i = 0; i < data.N_ITER1; ++i)
	{
		data.mS1_vect[i].D_MISSION=pop(buffer, 15, offset);
		offset += 15;
		data.mS1_vect[i].V_MISSION=pop(buffer, 7, offset);
		offset += 7;
	}
	data.mS2.T_START_TIME=pop(buffer, 12, offset);
	offset += 12;
	data.mS2.NID_LRGB=pop(buffer, 24, offset);
	offset += 24;
	data.mS2.D_STOP=pop(buffer, 15, offset);
	offset += 15;
	data.mS2.Q_DOORS=pop(buffer, 4, offset);
	offset += 4;
	data.mS2.T_DOORS_TIME=pop(buffer, 12, offset);
	offset += 12;
	setN_ITER2(pop(buffer, 5, offset));
	offset += 5;
	for(unsigned int i = 0; i < data.N_ITER2; ++i)
	{
		 data.mS2_vect[i].T_START_TIME=pop(buffer, 12, offset);
		offset += 12;
		data.mS2_vect[i].NID_LRGB=pop(buffer, 24, offset);
		offset += 24;
		data.mS2_vect[i].D_STOP=pop(buffer, 15, offset);
		offset += 15;
		data.mS2_vect[i].Q_DOORS=pop(buffer, 4, offset);
		offset += 4;
		data.mS2_vect[i].T_DOORS_TIME=pop(buffer, 12, offset);
		offset += 12;
	}
}


pacchettoMissionPlan::~pacchettoMissionPlan(void)
{
	delete data.mS1_vect;
	delete data.mS2_vect;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoMissionPlan::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;
	// 51 bit per l'header
	size += 51;
	// 122 per la parte fissa del mission data (considerando 2 volte N_ITER
	size += 122;
	// 89 bit per ogni N_ITER
	size += 89 * data.N_ITER1;
	// ritorno il numero di Byte occupato dalla struttura dati
	return (size / 8) + 1;
}