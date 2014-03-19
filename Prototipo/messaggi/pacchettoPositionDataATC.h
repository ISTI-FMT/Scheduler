#pragma once
#include "utility.h"
#include "StateCDB.h"
#include "pacchettoBase.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;


/*
Rappresenta le informazioni contenute nel pacchetto Position Data che l'ATS riceve dal ATC nel messaggio di stato della linea
*/

public ref class pacchettoPositionDataATC : pacchettoBase
{
	int L_PACKET;	
	int N_ITER;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	List< StateCDB^> ^ListPostionData;
public:
	pacchettoPositionDataATC();
	virtual int getSize() override;
	virtual void serialize(array<Byte>^buff, int offset) override;
	virtual void deserialize(array<Byte>^buff, int offset) override;
	
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};

	void setCDB(List< StateCDB^> ^all){ListPostionData=all;};
	List< StateCDB^> ^getListCDB(){return ListPostionData;};

	void setCDB(StateCDB ^one){ListPostionData->Add(one);};

	System::String^ toPrint();
};

