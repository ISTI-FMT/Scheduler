#pragma once

/*
Rappresenta le informazioni sul profilo velocità del pacchetto MissionData da inviare all'ATO
*/

ref class ProfiloVelocita
{
	int D_MISSION ;
	int V_MISSION ;
public:
	ProfiloVelocita(void);
	ProfiloVelocita(int D, int V){D_MISSION=D;V_MISSION=V;};
	void setD_MISSION(int D){ D_MISSION=D;};
	int getD_MISSION(){return D_MISSION;};
	void setV_MISSION(int V){V_MISSION=V;};
	int getV_MISSION(){return V_MISSION;};
	int Size(){return 15+7;}
	virtual System::String ^ToString() override;
};

