#include "pacchettostatolineaatc.h"
#include "utility.h"

pacchettostatolineaatc::pacchettostatolineaatc(void)
{
	setNID_PACKET(PacchettoID::PositionDataATC);
	setL_PACKET(0);
	setNID_OPERATIONAL ( 0);
	setCDB( gcnew List<StateCDB^>());
}


int pacchettostatolineaatc::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;

	// 94 per la parte fissa del pacchetto 
	size += 94;
	// 36 bit per ogni N_ITER
	if( N_ITER || N_ITER==0   ){

		size += 36 * N_ITER;
	}else{
		size += 36 *138;
	}
	// ritorno il numero di byte occupato dalla struttura dati
	return size;
}

System::String^ pacchettostatolineaatc::toPrint(){
	String ^out;

	out = out+"NID_PACKET: "+get_NID_PACKET()+";";
	out = out+"L_PACKET: "+getL_PACKET()+";";
	out = out+"NID_OPERATIONAL: "+getNID_OPERATIONAL()+";";

	out = out+getCDB()[0]->ToString();
	out = out+"N_ITER: "+getN_ITER()+";";

	for( int i=1;i<getCDB()->Count;i++)
	{
		out = out+getCDB()[i]->ToString();

	}

	return out;
}

// funzione che sette N_ITER1
void pacchettostatolineaatc::setN_ITER(int N)
{
	N_ITER = N;

}

void pacchettostatolineaatc::serialize(array<Byte>^buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
	offset += 8;
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset);
	offset += 13;
	utility::push(buffer, NID_OPERATIONAL, 32, offset);
	offset += 32;
	utility::push(buffer, pstato[0]->getNID_CDB(), 32, offset);
	offset += 32;
	utility::push(buffer, pstato[0]->getQ_STATOCDB(), 2, offset);
	offset += 2;
	utility::push(buffer, pstato[0]->getQ_DEVIATOIO(), 2, offset);
	offset += 2;
	utility::push(buffer, N_ITER, 5, offset);
	offset += 5;
	for( int i=1;i<pstato->Count;i++)
	{
		utility::push(buffer, pstato[i]->getNID_CDB(), 32, offset);
		offset += 32;
		utility::push(buffer, pstato[i]->getQ_STATOCDB(), 2, offset);
		offset += 2;
		utility::push(buffer, pstato[i]->getQ_DEVIATOIO(), 2, offset);
		offset += 2;
	}

}

void pacchettostatolineaatc::deserialize(array<Byte>^buffer, int offset)
{
	NID_PACKET=utility::pop(buffer,  8, offset);
	offset += 8;
	L_PACKET=utility::pop(buffer, 13, offset);
	offset += 13;
	NID_OPERATIONAL=utility::pop(buffer, 32, offset);
	offset += 32;
	
	int tNID_CDB =utility::pop(buffer, 32, offset);
	offset += 32;
	int tQ_STATOCDB =utility::pop(buffer, 2, offset);
	offset += 2;
	int tQ_DEVIATOIO =utility::pop(buffer, 2, offset);
	offset += 2;
	
	setCDB(gcnew StateCDB(tNID_CDB,(QStateCDB)tQ_STATOCDB,(QStateDeviatoio)tQ_DEVIATOIO,NID_OPERATIONAL));
	setN_ITER(utility::pop(buffer, 5, offset));
	offset += 5;
	//int offset = 145;

	for(int i = 0; i < N_ITER; ++i)
	{
		int NID_CDB=utility::pop(buffer, 32, offset);
		offset += 32;
		int Q_STATOCDB=utility::pop(buffer, 2, offset);
		offset += 2;
		int Q_DEVIATOIO=utility::pop(buffer, 2, offset);
		offset += 2;

		setCDB(gcnew StateCDB(NID_CDB,(QStateCDB)Q_STATOCDB,(QStateDeviatoio)Q_DEVIATOIO,NID_OPERATIONAL));
	}
}