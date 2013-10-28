#pragma once
#include "utility.h"

/*Utilizzo questa classe per rappresentare le informazioni contenute nel pacchetto End che l'ATS invia dal IXL in vari
messaggi, sono presenti anche i metodi per serializzare e deserializzare il contenuto della classe*/


//questa classe rappresenta un Pacchetto END

ref class pacchettoEnd
{
	unsigned int NID_PACKET ;
public:
	pacchettoEnd(void);
	void setNID_PACKET(int N){NID_PACKET = N;};
	int get_NID_PACKET(){return NID_PACKET;};
	void serialize(array<Byte>^buffer, int offset);
	void deserialize(array<Byte>^buffer, int offset);
	int getSize(){return 8;};
	
	virtual System::String ^ToString() override;
};

