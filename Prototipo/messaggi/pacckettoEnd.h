#pragma once
#include "struttureDatiMessaggi.h"

class pacckettoEnd
{
	End data;
public:
	pacckettoEnd(void);
	void setNID_PACKET(int N){data.NID_PACKET = N;};
	int get_NID_PACKET(){return data.NID_PACKET;};
	void serialize(byte *buffer);
	void deserialize(byte *buffer);
	~pacckettoEnd(void);
};

