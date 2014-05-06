#pragma once

/*
Rappresenta le informazioni sul profilo velocità del pacchetto MissionData da inviare all'ATO
*/
//using namespace System::Diagnostics::CodeAnalysis;

//[ExcludeFromCodeCoverage]
public ref class ProfiloVelocita
{
	int D_MISSION ;
	int V_MISSION ;
public:
	ProfiloVelocita(void);
	ProfiloVelocita(int D, int V){setD_MISSION(D);setV_MISSION(V);};
	void setD_MISSION(int D){ D_MISSION=D;};
	int getD_MISSION(){return D_MISSION;};
	void setV_MISSION(int V){V_MISSION=V;};
	int getV_MISSION(){return V_MISSION;};
	virtual System::String ^ToString() override;
};

