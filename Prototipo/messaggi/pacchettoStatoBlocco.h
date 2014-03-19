#pragma once
#include "utility.h"
#include "StateBlocco.h"
#include "pacchettoBase.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*
Rappresenta le informazioni contenute nel pacchetto Stato Blocco che l'ATS riceve dal IXL nel messaggio di stato della linea
*/

public ref class pacchettoStatoBlocco : pacchettoBase
{
	int L_PACKET ;
	int N_ITER ;
	List<StateBlocco^> ^vStatoBlocco;
public:
	pacchettoStatoBlocco(void);

	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};

	void setStatoBlocco(List< StateBlocco^> ^all){vStatoBlocco=all;};
	List< StateBlocco^> ^getStatoBlocco(){return vStatoBlocco;};

	void setStatoBlocco( StateBlocco^ one){vStatoBlocco->Add(one);};

	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;

	virtual System::String ^ToString() override;
};

