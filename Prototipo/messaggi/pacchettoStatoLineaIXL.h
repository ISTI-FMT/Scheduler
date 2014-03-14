#pragma once
#include "utility.h"
#include "StateCDB.h"
#include "pacchettoBase.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*
Rappresenta le informazioni contenute nel pacchetto Stato della Linea che l'ATS riceve dal IXL nel messaggio di stato della linea
*/

public ref class pacchettoStatoLineaIXL : pacchettoBase
{
	int L_PACKET ;
	int N_ITER;
	List<StateCDB^> ^vStatoCDB;
public:
	pacchettoStatoLineaIXL(void);

	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};

	void setCDB(List< StateCDB^> ^all){vStatoCDB=all;};
	List< StateCDB^> ^getCDB(){return vStatoCDB;};

	void setCDB( StateCDB ^one){vStatoCDB->Add(one);};
	
	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;

	virtual System::String ^ToString() override;
};

