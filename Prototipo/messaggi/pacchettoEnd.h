#pragma once
#include "utility.h"
#include "pacchettoBase.h"

/*
Rappresenta le informazioni contenute nel pacchetto End che l'ATS invia dal IXL in vari messaggi
*/

public ref class pacchettoEnd : pacchettoBase
{
public:
	pacchettoEnd(void);
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;
	virtual int getSize() override {return 8;};
	
	virtual System::String ^ToString() override;
};

