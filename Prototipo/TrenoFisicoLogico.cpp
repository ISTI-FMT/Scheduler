#include "TrenoFisicoLogico.h"


TrenoFisicoLogico::TrenoFisicoLogico(void)
{
	idtrenofisico=0;
	ListidTreniLogici = gcnew List<int>();
	cdblastposition=0;
}



TrenoFisicoLogico::TrenoFisicoLogico(int idtrenoF, int idtrenoL, int cdblpos){
	idtrenofisico=idtrenoF;
	ListidTreniLogici  = gcnew List<int>();
	ListidTreniLogici->Add(idtrenoL);
	cdblastposition=cdblpos;
}

TrenoFisicoLogico::TrenoFisicoLogico(int idtrenoF, List<int> ^idltrenoL, int cdblpos){
	idtrenofisico=idtrenoF;
	ListidTreniLogici = idltrenoL;
	cdblastposition=cdblpos;
}

String ^TrenoFisicoLogico::ToString(){
	System::String ^out ="";


	out+=" Idtrenofisico: "+idtrenofisico+";";
	for each (int var in ListidTreniLogici)
	{
		out+=" IdTrenoTrenoLogico: "+var+";";

	}

	out+=" CDBLastPosition: "+idtrenofisico+";";

	return out;


}

int TrenoFisicoLogico::getIdTrenoLogico(int i){
	if(ListidTreniLogici->Count>=i){
		return ListidTreniLogici[i];

	}
	return -1;
};