#pragma once
#include "utility.h"
#include "pacchettoBase.h"

/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto End che l'ATS invia dal IXL in vari
messaggi, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/


//questa classe rappresenta un Pacchetto END

ref class pacchettoEnd : pacchettoBase
{
public:
	pacchettoEnd(void);
	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buffer, int offset) override;
	virtual int getSize() override {return 8;};
	
	virtual System::String ^ToString() override;
};

