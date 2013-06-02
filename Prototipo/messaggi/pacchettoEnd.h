#pragma once
#include "utility.h"

ref class pacchettoEnd
{
	unsigned int NID_PACKET ;
public:
	pacchettoEnd(void);
	void setNID_PACKET(int N){NID_PACKET = N;};
	int get_NID_PACKET(){return NID_PACKET;};
	void serialize(byte *buffer, int offset);
	void deserialize(byte *buffer, int offset);
	int getSize(){return 8;};
	~pacchettoEnd(void);
	virtual System::String ^ToString() override;
};

