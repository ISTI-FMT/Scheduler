#pragma once

/*Utilizzo questa classe per serializzare le informazioni della missione del pacchetto MissionData da inviare all'ATO*/


//questa classe rappresenta le informazioni sulla missione da affidare ad un treno
ref class Mission
{
	unsigned int T_START_TIME;
	unsigned int NID_LRGB;
	unsigned int D_STOP;
	unsigned int Q_DOORS;
	unsigned int T_DOORS_TIME ;
public:
	Mission(void);
	Mission( int T, int NID,int D, int Q, int TD){T_START_TIME=T;NID_LRGB=NID;D_STOP=D;Q_DOORS=Q;T_DOORS_TIME=TD;};
	int Size(){return 12+24+15+4+12;}
	void setT_START_TIME( int T){ T_START_TIME=T;};
	int getT_START_TIME(){return T_START_TIME;};
	void setNID_LRGB( int NID){ NID_LRGB=NID;};
	int getNID_LRGB(){return NID_LRGB;};
	void setD_STOP(int D){ D_STOP=D;};
	int getD_STOP(){return D_STOP;};
	void setQ_DOORS( int Q){ Q_DOORS=Q;};
	int getQ_DOORS(){return Q_DOORS;};
	void setT_DOORS_TIME( int T){ T_DOORS_TIME=T;};
	int getT_DOORS_TIME(){return T_DOORS_TIME;};
	virtual System::String ^ToString() override;
};

