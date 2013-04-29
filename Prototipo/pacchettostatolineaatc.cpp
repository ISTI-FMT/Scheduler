#include "pacchettostatolineaatc.h"
#include "utility.h"

pacchettostatolineaatc::pacchettostatolineaatc(void)
{
	

	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.NID_OPERATIONAL = 0;
	data.pstato.NID_CDB = 0;
	data.pstato.Q_STATOCDB = 0;
	data.pstato.Q_DEVIATIOIO = 0;
	data.pstato1 = NULL;
}


int pacchettostatolineaatc::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;
	
	// 94 per la parte fissa del pacchetto 
	size += 94;
	// 36 bit per ogni N_ITER
	if( data.N_ITER || data.N_ITER==0   ){

		size += 36 * data.N_ITER;
	}else{
		size += 36 *128;
	}
	// ritorno il numero di byte occupato dalla struttura dati
	return size;
}

System::String^ pacchettostatolineaatc::toPrint(){
	String ^out;

	out = out+"NID_PACKET: "+data.NID_PACKET+";";
	out = out+"L_PACKET: "+data.L_PACKET+";";
	out = out+"NID_OPERATIONAL: "+data.NID_OPERATIONAL+";";

	out = out+"NID_CDB: "+data.pstato.NID_CDB+";";
	out = out+"Q_STATOCDB: "+data.pstato.Q_STATOCDB+";";
	out = out+"Q_DEVIATIOIO: "+data.pstato.Q_DEVIATIOIO+";";
	out = out+"N_ITER: "+data.N_ITER+";";
	if(data.pstato1){
		for(unsigned int i = 0; i < data.N_ITER; ++i)
		{
			out = out+"NID_CDB: "+data.pstato1[i].NID_CDB+";";

			out = out+"Q_STATOCDB: "+data.pstato1[i].Q_STATOCDB+";";

			out = out+"Q_DEVIATIOIO: "+data.pstato1[i].Q_DEVIATIOIO+";";

		}
	}
	return out;
}

// funzione che sette N_ITER1
void pacchettostatolineaatc::setN_ITER(int N)
{
	data.N_ITER = N;
	data.pstato1 = new pstatolineastruct[N];
}

void pacchettostatolineaatc::setNID_CDB(int index, int D)
{
	if(index == 0)
		data.pstato.NID_CDB = D;
	else
		data.pstato1[index - 1].NID_CDB  = D;
}

int pacchettostatolineaatc::getNID_CDB(int index)
{
	if(index == 0)
		return data.pstato.NID_CDB;
	else
		return data.pstato1[index - 1].NID_CDB;
}

void pacchettostatolineaatc::setQ_STATOCDB(int index, int D)
{
	if(index == 0)
		data.pstato.Q_STATOCDB = D;
	else
		data.pstato1[index - 1].Q_STATOCDB  = D;
}

int pacchettostatolineaatc::getQ_STATOCDB(int index)
{
	if(index == 0)
		return data.pstato.Q_STATOCDB;
	else
		return data.pstato1[index - 1].Q_STATOCDB;
}

void pacchettostatolineaatc::setQ_DEVIATIOIO(int index, int D)
{
	if(index == 0)
		data.pstato.Q_DEVIATIOIO = D;
	else
		data.pstato1[index - 1].Q_DEVIATIOIO  = D;
}

int pacchettostatolineaatc::getQ_DEVIATIOIO(int index)
{
	if(index == 0)
		return data.pstato.Q_DEVIATIOIO;
	else
		return data.pstato1[index - 1].Q_DEVIATIOIO;
}


void pacchettostatolineaatc::serialize(byte *buffer)
{

	push(buffer, data.NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, 59);
	push(buffer, data.NID_OPERATIONAL, 32, 72);
	push(buffer, data.pstato.NID_CDB, 32, 104);
	push(buffer, data.pstato.Q_STATOCDB, 2, 136);
	push(buffer, data.pstato.Q_DEVIATIOIO, 2, 138);
	push(buffer, data.N_ITER, 5, 140);
	//data.pstato1 = new pstatolineastruct[data.N_ITER];
	int offset = 145;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		push(buffer, data.pstato1[i].NID_CDB, 32, offset);
		offset += 32;
		push(buffer, data.pstato1[i].Q_STATOCDB, 2, offset);
		offset += 2;
		push(buffer, data.pstato1[i].Q_DEVIATIOIO, 2, offset);
		offset += 2;
	}

}

void pacchettostatolineaatc::deserialize(byte *buffer)
{

	data.NID_PACKET=pop(buffer,  8, 51);
	data.L_PACKET=pop(buffer, 13, 59);
	data.NID_OPERATIONAL=pop(buffer, 32, 72);
	data.pstato.NID_CDB=pop(buffer, 32, 104);
	data.pstato.Q_STATOCDB=pop(buffer, 2, 136);
	data.pstato.Q_DEVIATIOIO=pop(buffer, 2, 138);
	setN_ITER(pop(buffer, 5, 140));
	int offset = 145;
	if(data.pstato1){
		for(unsigned int i = 0; i < data.N_ITER; ++i)
		{
			data.pstato1[i].NID_CDB=pop(buffer, 15, offset);
			offset += 32;
			data.pstato1[i].Q_STATOCDB=pop(buffer, 2, offset);
			offset += 2;
			data.pstato1[i].Q_STATOCDB=pop(buffer, 2, offset);
			offset += 2;
		}

	}
}