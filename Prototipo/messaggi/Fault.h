#pragma once

/*
Rappresenta le informazioni contenute nel messaggio di fault
*/
public ref class Fault
{
	int NID_COMPONENT ;
	int M_FAULT ;
public:
	Fault(void);
	Fault(int N, int M){NID_COMPONENT=N;M_FAULT=M;};
	int Size(){return 12;}
	void setNID_COMPONENT(int N){NID_COMPONENT=N;};
	int getNID_COMPONENT(){ return NID_COMPONENT;};
	void setM_FAULT(int M){M_FAULT=M;};
	int getM_FAULT(){return M_FAULT;};

	virtual System::String ^ToString() override;
};

