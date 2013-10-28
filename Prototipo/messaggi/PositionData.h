#include "utility.h"
using namespace System;
#pragma once

/*Utilizzo questa classe per serializzare le informazioni del pacchetto PositionData*/

//rappresenta le informazioni contenute nel pacchetto di PositionData
ref class PositionData
{
	unsigned int NID_OPERATIONAL;
	unsigned int NID_ENGINE;
	unsigned int NID_CDB; 
public:
	PositionData(void);
	PositionData(int O, int E, int C){NID_OPERATIONAL=O;NID_ENGINE=E;NID_CDB=C;};
	int Size(){return 12;}
	void seNID_OPERATIONAL(int N){NID_OPERATIONAL=N;};
	int getNID_OPERATIONAL(){ return NID_OPERATIONAL;};
	void setNID_ENGINE(int N){NID_ENGINE=N;};
	int getNID_ENGINE(){ return NID_ENGINE;};
	void setNID_CDB(int M){NID_CDB=M;};
	int getNID_CDB(){return NID_CDB;};

	void serialize(array<Byte>^buffer, int offset);
	void deserialize(array<Byte>^buffer, int offset);

	virtual System::String ^ToString() override;
};

