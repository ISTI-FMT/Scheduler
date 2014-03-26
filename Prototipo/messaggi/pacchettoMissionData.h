#pragma once
#include "utility.h"
#include "ProfiloVelocita.h"
#include "Mission.h"
#include "pacchettoBase.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

public enum class QSCALEMissionData { CM = 0 , M = 1 , DC=2};

/*
Rappresenta le informazioni contenute nel pacchetto MissionData che l'ATS invia dal ATO nel messaggio di MissionPlan
*/

public ref class pacchettoMissionData : pacchettoBase
{
	int L_PACKET;
	int Q_SCALE ;
	
	int N_ITER1;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	List<ProfiloVelocita^>^mS1_vect;

	int N_ITER2;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	List<Mission^>^mS2_vect;
public:

	virtual int getSize() override;
	virtual void serialize(array<Byte>^buff, int offset) override;
	virtual void deserialize(array<Byte>^buff, int offset) override;
	pacchettoMissionData();
	
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};
	void setQ_SCALE(QSCALEMissionData Q){Q_SCALE =(int) Q;};
	int getQ_SCALE(){return Q_SCALE;};
	// metodo che setta N_ITER1 ed alloca conseguentemente il vettore mS1_vect
	void setN_ITER1(int N);
	int getN_ITER1(){return N_ITER1;};
	// metodo che setta N_ITER2 ed alloca conseguentemente il vettore mS2_vect
	void setN_ITER2(int N);
	int getN_ITER2(){return N_ITER2;};
	
	void setPV( ProfiloVelocita^ one){mS1_vect->Add(one);};
	void setPV(List< ProfiloVelocita^> ^all){mS1_vect=all;};
	List< ProfiloVelocita^> ^getPV(){return mS1_vect;};

	void setMission(List< Mission^> ^all){mS2_vect=all;};
	void setMission( Mission^ one){mS2_vect->Add(one);};
	List< Mission^> ^getlistMission(){return mS2_vect;};
		
	virtual System::String ^ToString() override;
};

