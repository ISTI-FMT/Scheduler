#pragma once
using namespace System;
using namespace System::Collections::Generic;
//rappresenta le informazioni che mappano ad ogni treno fisico una lista di trenilogici e la loro ultima posizione
ref class TrenoFisicoLogico
{
	unsigned int idtrenofisico;
	List<int> ^ListidTreniLogici;
	unsigned int cdblastposition;

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

