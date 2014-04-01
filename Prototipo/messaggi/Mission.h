#pragma once
#include "..\FermataType.h"

/*
Questa classe rappresenta le informazioni sulla missione da affidare ad un treno
*/

public ref class Mission
{
	 int T_START_TIME;
	 int NID_LRGB;
	 int D_LRGB;
	 int D_STOP;
	 int Q_DOORS;
	 int T_DOORS_TIME ;
public:
	
	Mission(void);
	Mission( int T,int DD,  int NID,int D, int Q, int TD){T_START_TIME=T;D_LRGB=DD; NID_LRGB=NID;D_STOP=D;Q_DOORS=Q;T_DOORS_TIME=TD;};
	
	void setT_START_TIME( int T){ T_START_TIME=T;};
	int getT_START_TIME(){return T_START_TIME;};
	void setNID_LRGB( int NID){ NID_LRGB=NID;};
	int getNID_LRGB(){return NID_LRGB;};
	void setD_LRGB( int D){ D_LRGB=D;};
	int getD_LRGB(){return D_LRGB;};
	void setD_STOP(int D){ D_STOP=D;};
	int getD_STOP(){return D_STOP;};
	void setQ_DOORS( FermataType Q){ Q_DOORS=(int)Q;};
	int getQ_DOORS(){return Q_DOORS;};
	void setT_DOORS_TIME( int T){ T_DOORS_TIME=T;};
	int getT_DOORS_TIME(){return T_DOORS_TIME;};
	virtual System::String ^ToString() override;
};

