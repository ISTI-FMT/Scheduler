#pragma once
using namespace System;
using namespace System::Collections::Generic;

/*Utilizzo questa classe per serializzare le informazioni del file di configurazione MapTreni.xml 
in particolare per ogni idtrenofisico c'è una lista di idlogici che gli possono essere assegnati ed infine il CDB
in cui si trova il treno*/


//rappresenta le informazioni che mappano ad ogni treno fisico una lista di trenilogici e la loro ultima posizione
public ref class TrenoFisicoLogico
{
	int idtrenofisico;
	List<int> ^ListidTreniLogici;
	int cdblastposition;

public:
	TrenoFisicoLogico(void);
	TrenoFisicoLogico(int idtrenoF, int idtrenoL, int cdblpos);
	TrenoFisicoLogico(int idtrenoF, List<int> ^idltrenoL, int cdblpos);

	int getIdTrenoFisico(){return idtrenofisico;};
	void setIdTrenoFisico(int id){idtrenofisico=id;};

	List<int> ^getIdTrenoListTreniLogici(){return ListidTreniLogici;};
	int getIdTrenoLogico(int i);
	void setIdTrenoLogico(int id){ListidTreniLogici->Add(id);};

	int getCDBLastPosition(){return cdblastposition;};
	void setCDBLastPosition(int pos){cdblastposition=pos;};


	virtual String ^ToString() override;


};

