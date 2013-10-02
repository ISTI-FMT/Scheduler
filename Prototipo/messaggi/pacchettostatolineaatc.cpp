#include "pacchettostatolineaatc.h"
#include "utility.h"

pacchettostatolineaatc::pacchettostatolineaatc(void)
{


	NID_PACKET = 0;
	L_PACKET = 0;
	NID_OPERATIONAL = 0;
	pstato = gcnew StateCDB();
}


int pacchettostatolineaatc::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;

	// 94 per la parte fissa del pacchetto 
	size += 94+32;
	// 36 bit per ogni N_ITER
	

	// ritorno il numero di byte occupato dalla struttura dati
	return size;
}

System::String^ pacchettostatolineaatc::toPrint(){
	String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+"NID_OPERATIONAL: "+NID_OPERATIONAL+";";

	out = out+pstato->ToString();
	

	return out;
}

// funzione che sette N_ITER1




void pacchettostatolineaatc::serialize(array<Byte>^buffer)
{

	utility::push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, 59);
	utility::push(buffer, NID_OPERATIONAL, 32, 72);
	utility::push(buffer, pstato->getNID_CDB(), 32, 104);
	utility::push(buffer, pstato->getQ_STATOCDB(), 2, 136);
	utility::push(buffer, pstato->getQ_DEVIATOIO(), 2, 138);
	
	//pstato1 = new pstatolineastruct[N_ITER];
	int offset = 145;
	

}

void pacchettostatolineaatc::deserialize(array<Byte>^buffer)
{

	NID_PACKET=utility::pop(buffer,  8, 51);
	L_PACKET=utility::pop(buffer, 13, 59);
	NID_OPERATIONAL=utility::pop(buffer, 32, 72);
	
	int tNID_CDB =utility::pop(buffer, 32, 104);
	//int tQ_STATOCDB =utility::pop(buffer, 2, 136);
	//int tQ_DEVIATOIO =utility::pop(buffer, 2, 138);
	
	pstato =gcnew StateCDB(tNID_CDB,typeStateCDB::cdbOccupato,1,NID_OPERATIONAL);
	


}