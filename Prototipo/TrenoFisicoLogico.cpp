#include "TrenoFisicoLogico.h"


TrenoFisicoLogico::TrenoFisicoLogico(void)
{
	setIdTrenoFisico(0);
	ListidTreniLogici = gcnew List<int>();
	setCDBLastPosition(0);
}



TrenoFisicoLogico::TrenoFisicoLogico(int idtrenoF, int idtrenoL, int cdblpos){
	setIdTrenoFisico(idtrenoF);
	ListidTreniLogici  = gcnew List<int>();
	setIdTrenoLogico(idtrenoL);
	setCDBLastPosition(cdblpos);
}

TrenoFisicoLogico::TrenoFisicoLogico(int idtrenoF, List<int> ^idltrenoL, int cdblpos){
	setIdTrenoFisico(idtrenoF);
	ListidTreniLogici = idltrenoL;
	setCDBLastPosition(cdblpos);
}

String ^TrenoFisicoLogico::ToString(){
	System::String ^out ="";


	out+=" Idtrenofisico: "+getIdTrenoFisico()+";";
	for each (int var in ListidTreniLogici)
	{
		out+=" IdTrenoTrenoLogico: "+var+";";

	}

	out+=" CDBLastPosition: "+getCDBLastPosition()+";";

	return out;


}

int TrenoFisicoLogico::getIdTrenoLogico(int i){
	if(ListidTreniLogici->Count>=i){
		return ListidTreniLogici[i];

	}
	return -1;
};