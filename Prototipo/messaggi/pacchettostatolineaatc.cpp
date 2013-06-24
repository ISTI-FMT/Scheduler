#include "pacchettostatolineaatc.h"
#include "utility.h"

pacchettostatolineaatc::pacchettostatolineaatc(void)
{


	NID_PACKET = 0;
	L_PACKET = 0;
	NID_OPERATIONAL = 0;
	pstato = gcnew List<StateCDB^>();
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
		size += 36 *128;
	}
	// ritorno il numero di byte occupato dalla struttura dati
	return size;
}

System::String^ pacchettostatolineaatc::toPrint(){
	String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+"NID_OPERATIONAL: "+NID_OPERATIONAL+";";

	out = out+pstato[0]->ToString();
	out = out+"N_ITER: "+N_ITER+";";

	for(unsigned int i=1;i<N_ITER;i++)
	{
		out = out+pstato[i]->ToString();

	}

	return out;
}

// funzione che sette N_ITER1
void pacchettostatolineaatc::setN_ITER(int N)
{
	N_ITER = N;

}



void pacchettostatolineaatc::serialize(byte *buffer)
{

	utility::push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, 59);
	utility::push(buffer, NID_OPERATIONAL, 32, 72);
	utility::push(buffer, pstato[0]->getNID_CDB(), 32, 104);
	utility::push(buffer, pstato[0]->getQ_STATOCDB(), 2, 136);
	utility::push(buffer, pstato[0]->getQ_DEVIATOIO(), 2, 138);
	utility::push(buffer, N_ITER, 5, 140);
	//pstato1 = new pstatolineastruct[N_ITER];
	int offset = 145;
	for(unsigned int i=1;i<=N_ITER;i++)
	{

		utility::push(buffer, pstato[i]->getNID_CDB(), 32, offset);
		offset += 32;
		utility::push(buffer, pstato[i]->getQ_STATOCDB(), 2, offset);
		offset += 2;
		utility::push(buffer, pstato[i]->getQ_DEVIATOIO(), 2, offset);
		offset += 2;
	}

}

void pacchettostatolineaatc::deserialize(byte *buffer)
{

	NID_PACKET=utility::pop(buffer,  8, 51);
	L_PACKET=utility::pop(buffer, 13, 59);
	NID_OPERATIONAL=utility::pop(buffer, 32, 72);
	
	int tNID_CDB =utility::pop(buffer, 32, 104);
	int tQ_STATOCDB =utility::pop(buffer, 2, 136);
	int tQ_DEVIATOIO =utility::pop(buffer, 2, 138);
	
	pstato->Add(gcnew StateCDB(tNID_CDB,tQ_STATOCDB,tQ_DEVIATOIO,NID_OPERATIONAL));
	setN_ITER(utility::pop(buffer, 5, 140));
	int offset = 145;

	for(unsigned int i = 0; i < N_ITER; ++i)
	{
		int NID_CDB=utility::pop(buffer, 32, offset);
		offset += 32;
		int Q_STATOCDB=utility::pop(buffer, 2, offset);
		offset += 2;
		int Q_DEVIATOIO=utility::pop(buffer, 2, offset);
		offset += 2;

		pstato->Add(gcnew StateCDB(NID_CDB,Q_STATOCDB,Q_DEVIATOIO,NID_OPERATIONAL));
	}


}