#include "pacchettostatolineaatc.h"
#include "utility.h"

pacchettostatolineaatc::pacchettostatolineaatc(void)
{


	NID_PACKET = 0;
	L_PACKET = 0;
	NID_OPERATIONAL = 0;
	pstato = gcnew StateCDB();
	pstato1 = gcnew List<StateCDB^>();
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

	out = out+pstato->ToString();
	out = out+"N_ITER: "+N_ITER+";";
	if(pstato1){
		for each (StateCDB ^var in pstato1)
		{
			out = out+var->ToString();

		}
	}
	return out;
}

// funzione che sette N_ITER1
void pacchettostatolineaatc::setN_ITER(int N)
{
	N_ITER = N;
	
}

/*void pacchettostatolineaatc::setNID_CDB(int index, int D)
{
	if(index == 0)
		pstato->setNID_CDB ( D);
	else
		pstato1[index - 1]->setNID_CDB ( D);
}

int pacchettostatolineaatc::getNID_CDB(int index)
{
	if(index == 0)
		return pstato->getNID_CDB();
	else
		return pstato1[index - 1].NID_CDB;
}

void pacchettostatolineaatc::setQ_STATOCDB(int index, int D)
{
	if(index == 0)
		pstato->setQ_STATOCDB ( D);
	else
		pstato1[index - 1].Q_STATOCDB  = D;
}

int pacchettostatolineaatc::getQ_STATOCDB(int index)
{
	if(index == 0)
		return pstato->getQ_STATOCDB();
	else
		return pstato1[index - 1].Q_STATOCDB;
}

void pacchettostatolineaatc::setQ_DEVIATIOIO(int index, int D)
{
	if(index == 0)
		pstato->setQ_DEVIATOIO ( D);
	else
		pstato1[index - 1].Q_DEVIATOIO  = D;
}

int pacchettostatolineaatc::getQ_DEVIATIOIO(int index)
{
	if(index == 0)
		return pstato->getQ_DEVIATOIO();
	else
		return pstato1[index - 1].Q_DEVIATOIO;
}
*/

void pacchettostatolineaatc::serialize(byte *buffer)
{

	utility::push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, 59);
	utility::push(buffer, NID_OPERATIONAL, 32, 72);
	utility::push(buffer, pstato->getNID_CDB(), 32, 104);
	utility::push(buffer, pstato->getQ_STATOCDB(), 2, 136);
	utility::push(buffer, pstato->getQ_DEVIATOIO(), 2, 138);
	utility::push(buffer, N_ITER, 5, 140);
	//pstato1 = new pstatolineastruct[N_ITER];
	int offset = 145;
	for each (StateCDB ^var in pstato1)
	{

		utility::push(buffer, var->getNID_CDB(), 32, offset);
		offset += 32;
		utility::push(buffer, var->getQ_STATOCDB(), 2, offset);
		offset += 2;
		utility::push(buffer, var->getQ_DEVIATOIO(), 2, offset);
		offset += 2;
	}

}

void pacchettostatolineaatc::deserialize(byte *buffer)
{

	NID_PACKET=utility::pop(buffer,  8, 51);
	L_PACKET=utility::pop(buffer, 13, 59);
	NID_OPERATIONAL=utility::pop(buffer, 32, 72);
	pstato->setNID_CDB(utility::pop(buffer, 32, 104));
	pstato->setQ_STATOCDB(utility::pop(buffer, 2, 136));
	pstato->setQ_DEVIATOIO(utility::pop(buffer, 2, 138));
	pstato->setNID_OPERATIONAL(NID_OPERATIONAL);
	setN_ITER(utility::pop(buffer, 5, 140));
	int offset = 145;
	if(pstato1){
		for(unsigned int i = 0; i < N_ITER; ++i)
		{
			int NID_CDB=utility::pop(buffer, 15, offset);
			offset += 32;
			int Q_STATOCDB=utility::pop(buffer, 2, offset);
			offset += 2;
			int Q_DEVIATOIO=utility::pop(buffer, 2, offset);
			offset += 2;
			
			pstato1->Add(gcnew StateCDB(NID_CDB,Q_STATOCDB,Q_DEVIATOIO,NID_OPERATIONAL));
		}

	}
}