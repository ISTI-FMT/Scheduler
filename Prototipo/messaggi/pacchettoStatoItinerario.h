#pragma once
#include "utility.h"
#include "StateItinerario.h"
#include "pacchettoBase.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections;

/*
Rappresenta le informazioni contenute nel pacchetto di stato dell'itinerario che l'ATS riceve dal IXL nel messaggio di stato della linea
*/
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
public ref class pacchettoStatoItinerario : pacchettoBase
{
	int L_PACKET ;
	int N_ITER ;
	List<StateItinerario^> ^vStatoItinerario;
public:
	pacchettoStatoItinerario(void);

	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	// metodo che setta N_ITER
	void setN_ITER(int N);
	int getN_ITER(){return N_ITER;};
	

	void setItinerario(List< StateItinerario^> ^all){vStatoItinerario=all;};
	List< StateItinerario^> ^getItinerario(){return vStatoItinerario;};

	
	void setItinerario( StateItinerario ^one){vStatoItinerario->Add(one);};

	virtual int getSize() override;
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;

	virtual System::String ^ToString() override;
};

