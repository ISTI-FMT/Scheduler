#include "pacchettoMissionPlan.h"
#include "utility.h"
#include <iostream>
using namespace std;
#include "Mission.h"


pacchettoMissionPlan::pacchettoMissionPlan()
{

	NID_PACKET = 0;
	L_PACKET = 0;
	Q_SCALE = 0;

	mS1 = gcnew ProfiloVelocita();
	N_ITER1 = 0;
	mS1_vect = gcnew List<ProfiloVelocita^>();
	mS2= gcnew Mission();
	mS2_vect = gcnew List<Mission^>();
}

// funzione che sette N_ITER1
void pacchettoMissionPlan::setN_ITER1(int N)
{
	N_ITER1 = N;

}

// funzione che sette N_ITER2
void pacchettoMissionPlan::setN_ITER2(int N)
{
	N_ITER2 = N;


}

void pacchettoMissionPlan::serializeMissionPlanPkt(byte *buffer)
{

	push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, L_PACKET, 13, 59);
	push(buffer, Q_SCALE, 2, 72);
	push(buffer, mS1->getD_MISSION(), 15, 74);
	push(buffer, mS1->getV_MISSION(), 7, 89);
	push(buffer, N_ITER1, 5, 96);
	//mS1_vect = new missionStruct1[N_ITER1];
	int offset = 101;
	for each (ProfiloVelocita ^var in mS1_vect)
	{
		push(buffer, var->getD_MISSION(), 15, offset);
		offset += 15;
		push(buffer, var->getV_MISSION(), 7, offset);
		offset += 7;

	}
	push(buffer, mS2->getT_START_TIME(), 12, offset);
	offset += 12;
	push(buffer, mS2->getNID_LRGB(), 24, offset);
	offset += 24;
	push(buffer, mS2->getD_STOP(), 15, offset);
	offset += 15;
	push(buffer, mS2->getQ_DOORS(), 4, offset);
	offset += 4;
	push(buffer, mS2->getT_DOORS_TIME(), 12, offset);
	offset += 12;
	push(buffer, N_ITER2, 5, offset);
	offset += 5;
	//mS2_vect = new missionStruct2[N_ITER2];
	for each (Mission ^var in mS2_vect)
	{
		push(buffer, var->getT_START_TIME(), 12, offset);
		offset += 12;
		push(buffer, var->getNID_LRGB(), 24, offset);
		offset += 24;
		push(buffer, var->getD_STOP(), 15, offset);
		offset += 15;
		push(buffer, var->getQ_DOORS(), 4, offset);
		offset += 4;
		push(buffer, var->getT_DOORS_TIME(), 12, offset);
		offset += 12;
	}

}

void pacchettoMissionPlan::deserializeMissionPlanPkt(byte *buffer)
{

	NID_PACKET=pop(buffer,  8, 51);
	L_PACKET=pop(buffer, 13, 59);
	Q_SCALE=pop(buffer, 2, 72);
	mS1->setD_MISSION(pop(buffer, 15, 74));
	mS1->setV_MISSION(pop(buffer, 7, 89));
	setN_ITER1(pop(buffer, 5, 96));
	int offset = 101;
	for(unsigned int i = 0; i < N_ITER1; ++i)
	{
		int D_MISSION=pop(buffer, 15, offset);
		offset += 15;
		int V_MISSION=pop(buffer, 7, offset);
		offset += 7;
		mS1_vect->Add(gcnew ProfiloVelocita(D_MISSION,V_MISSION));
	}
	mS2->setT_START_TIME(pop(buffer, 12, offset));
	offset += 12;
	mS2->setNID_LRGB(pop(buffer, 24, offset));
	offset += 24;
	mS2->setD_STOP(pop(buffer, 15, offset));
	offset += 15;
	mS2->setQ_DOORS(pop(buffer, 4, offset));
	offset += 4;
	mS2->setT_DOORS_TIME(pop(buffer, 12, offset));
	offset += 12;
	setN_ITER2(pop(buffer, 5, offset));
	offset += 5;
	for(unsigned int i = 0; i < N_ITER2; ++i)
	{
		int T_START_TIME=pop(buffer, 12, offset);
		offset += 12;
		int NID_LRGB=pop(buffer, 24, offset);
		offset += 24;
		int D_STOP=pop(buffer, 15, offset);
		offset += 15;
		int Q_DOORS=pop(buffer, 4, offset);
		offset += 4;
		int T_DOORS_TIME=pop(buffer, 12, offset);
		offset += 12;
		mS2_vect->Add(gcnew Mission(T_START_TIME,NID_LRGB,D_STOP,Q_DOORS,T_DOORS_TIME));
	}
}




// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoMissionPlan::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;

	// 122 per la parte fissa del mission data (considerando 2 volte N_ITER
	size += 122;
	// 22 bit per ogni N_ITER
	size += 22 * N_ITER1;
	// 22 bit per ogni N_ITER
	size += 67 * N_ITER2;
	// ritorno il numero di bit occupato dalla struttura dati
	return size;
}

System::String ^ pacchettoMissionPlan::ToString(){


	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+"Q_SCALE: "+Q_SCALE+";";
	out = out+mS1->ToString();
	out = out+"N_ITER1: "+N_ITER1+";";
	if(mS1_vect){
		for each (ProfiloVelocita^ var in mS1_vect)
		{
			out = out+var->ToString();


		}
	}
	out = out+mS2->ToString();

	out = out+"N_ITER2: "+N_ITER2+";";
	if(mS2_vect){
		for each (Mission ^var in mS2_vect)
		{
			out = out+var->ToString();
		}
	}

	return out;
};