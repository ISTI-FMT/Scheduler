#pragma once
#include "struttureDatiMessaggi.h"

class pacchettoEnd
{
	End data;
public:
	pacchettoEnd(void);
	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int get_NID_PACKET(){return data.NID_PACKET;};
	void serialize(byte *buffer);
	void deserialize(byte *buffer);
	~pacchettoEnd(void);
};

