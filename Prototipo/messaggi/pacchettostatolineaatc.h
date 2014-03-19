#pragma once
#include "utility.h"
#include "StateCDB.h"
#include "pacchettoBase.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;
using namespace System::Diagnostics::CodeAnalysis;

/*
Rappresenta le informazioni contenute nel pacchetto Stato linea che l'ATS riceve dal ATC, con le informazioni sullo stato dei CDB, nel messaggio di stato della linea 
**pacchetto cambiato classe inutilizzata
*/


[ExcludeFromCodeCoverage]
public ref class pacchettostatolineaatc : pacchettoBase
{
	int L_PACKET ;
	int NID_OPERATIONAL ;
	
	int N_ITER ;
	List< StateCDB^> ^pstato;
public:
	pacchettostatolineaatc();

	virtual int getSize() override;
	virtual void serialize(array<Byte>^buff, int offset) override;
	virtual void deserialize(array<Byte>^buff, int offset) override;
	
	void setNID_PACKET(int NID){NID_PACKET = NID;};
	int getNID_PACKET(){return NID_PACKET;};
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	void setNID_OPERATIONAL(int NID){NID_OPERATIONAL = NID;};
	int getNID_OPERATIONAL(){return NID_OPERATIONAL;};

	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};

	void setCDB(List< StateCDB^> ^all){pstato=all;};
	List< StateCDB^> ^getCDB(){return pstato;};

	void setCDB(StateCDB ^one){pstato->Add(one);};

	System::String^ toPrint();
};

