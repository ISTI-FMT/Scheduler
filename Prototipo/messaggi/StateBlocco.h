#pragma once
enum  typeStatoBlocco {  illegale = 0, legale = 1};

/*Utilizzo questa classe per serializzare le informazioni dello stato del blocco del pacchetto StatoBlocco da inviare all'IXL*/


//questa classe rappresenta lo stato del blocco
ref class StateBlocco
{
	unsigned int NID_BLOCCO ;
	unsigned int Q_STATOBLOCCO;
public:
	StateBlocco(void);
	StateBlocco(int N, int Q){NID_BLOCCO=N;Q_STATOBLOCCO=Q;};
	int Size(){return 34;}
	void setNID_BLOCCO(int N){NID_BLOCCO=N;};
	int getNID_BLOCCO(){return NID_BLOCCO;};
	void setQ_STATOBLOCCO( int Q){Q_STATOBLOCCO=Q;};
	int getQ_STATOBLOCCO(){return Q_STATOBLOCCO;};
	virtual System::String ^ToString() override;
};

