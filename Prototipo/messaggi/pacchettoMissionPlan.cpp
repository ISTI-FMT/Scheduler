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

	
	N_ITER1 = 0;
	mS1_vect = gcnew List<ProfiloVelocita^>();
	
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

	utility::push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, 59);
	utility::push(buffer, Q_SCALE, 2, 72);
	utility::push(buffer, mS1_vect[0]->getD_MISSION(), 15, 74);
	utility::push(buffer, mS1_vect[0]->getV_MISSION(), 7, 89);
	utility::push(buffer, N_ITER1, 5, 96);
	//mS1_vect = new missionStruct1[N_ITER1];
	int offset = 101;
	for( int i=1;i<mS1_vect->Count;i++)
	{
		utility::push(buffer, mS1_vect[i]->getD_MISSION(), 15, offset);
		offset += 15;
		utility::push(buffer, mS1_vect[i]->getV_MISSION(), 7, offset);
		offset += 7;

	}
	utility::push(buffer, mS2_vect[0]->getT_START_TIME(), 12, offset);
	offset += 12;
	utility::push(buffer,  mS2_vect[0]->getNID_LRGB(), 24, offset);
	offset += 24;
	utility::push(buffer,  mS2_vect[0]->getD_STOP(), 15, offset);
	offset += 15;
	utility::push(buffer,  mS2_vect[0]->getQ_DOORS(), 4, offset);
	offset += 4;
	utility::push(buffer,  mS2_vect[0]->getT_DOORS_TIME(), 12, offset);
	offset += 12;
	utility::push(buffer, N_ITER2, 5, offset);
	offset += 5;
	//mS2_vect = new missionStruct2[N_ITER2];
	for( int i=1;i<mS2_vect->Count;i++)
	{
		utility::push(buffer,  mS2_vect[i]->getT_START_TIME(), 12, offset);
		offset += 12;
		utility::push(buffer,  mS2_vect[i]->getNID_LRGB(), 24, offset);
		offset += 24;
		utility::push(buffer,  mS2_vect[i]->getD_STOP(), 15, offset);
		offset += 15;
		utility::push(buffer,  mS2_vect[i]->getQ_DOORS(), 4, offset);
		offset += 4;
		utility::push(buffer,  mS2_vect[i]->getT_DOORS_TIME(), 12, offset);
		offset += 12;
	}

}

void pacchettoMissionPlan::deserializeMissionPlanPkt(byte *buffer)
{

	NID_PACKET=utility::pop(buffer,  8, 51);
	L_PACKET=utility::pop(buffer, 13, 59);
	Q_SCALE=utility::pop(buffer, 2, 72);
	int tD_MISSION =utility::pop(buffer, 15, 74);
	int tV_MISSION =utility::pop(buffer, 7, 89);
	mS1_vect->Add(gcnew ProfiloVelocita(tD_MISSION,tV_MISSION));
	setN_ITER1(utility::pop(buffer, 5, 96));
	int offset = 101;
	for(unsigned int i = 0; i < N_ITER1; ++i)
	{
		int D_MISSION=utility::pop(buffer, 15, offset);
		offset += 15;
		int V_MISSION=utility::pop(buffer, 7, offset);
		offset += 7;
		mS1_vect->Add(gcnew ProfiloVelocita(D_MISSION,V_MISSION));
	}
	int tT_START_TIME=utility::pop(buffer, 12, offset);
	offset += 12;
	int tNID_LRGB=utility::pop(buffer, 24, offset);
	offset += 24;
	int tD_STOP=utility::pop(buffer, 15, offset);
	offset += 15;
	int tQ_DOORS=utility::pop(buffer, 4, offset);
	offset += 4;
	int tT_DOORS_TIME=utility::pop(buffer, 12, offset);
	mS2_vect->Add(gcnew Mission(tT_START_TIME,tNID_LRGB,tD_STOP,tQ_DOORS,tT_DOORS_TIME));

	offset += 12;
	setN_ITER2(utility::pop(buffer, 5, offset));
	offset += 5;
	for(unsigned int i = 0; i < N_ITER2; ++i)
	{
		int T_START_TIME=utility::pop(buffer, 12, offset);
		offset += 12;
		int NID_LRGB=utility::pop(buffer, 24, offset);
		offset += 24;
		int D_STOP=utility::pop(buffer, 15, offset);
		offset += 15;
		int Q_DOORS=utility::pop(buffer, 4, offset);
		offset += 4;
		int T_DOORS_TIME=utility::pop(buffer, 12, offset);
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
	out = out+mS1_vect[0]->ToString();
	out = out+"N_ITER1: "+N_ITER1+";";
	
		for( int i=1;i<mS1_vect->Count;i++)
		{
			out = out+mS1_vect[i]->ToString();


		}
	
	out = out+ mS2_vect[0]->ToString();

	out = out+"N_ITER2: "+N_ITER2+";";
	
		for( int i=1;i<mS2_vect->Count;i++)
		{
			out = out+ mS2_vect[i]->ToString();
		}
	

	return out;
};