#include "pacchettoMissionPlan.h"
#include <iostream>
using namespace std;


pacchettoMissionPlan::pacchettoMissionPlan()
{
	data.head.NID_MESSAGE = 0;
	data.head.L_MESSAGE = 0;
	data.head.T_TRAIN = 0;
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

void pacchettoMissionPlan::serializeStructuredHeader(byte *buff, structuredHeader &h, int &index)
{

}

pacchettoMissionPlan::~pacchettoMissionPlan(void)
{
	delete data.mS1_vect;
	delete data.mS2_vect;
}