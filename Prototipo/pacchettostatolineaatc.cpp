#include "pacchettostatolineaatc.h"
#include "pacchettoAcknowledgement.h"
#include "utility.h"

pacchettostatolineaatc::pacchettostatolineaatc(void)
{
	data.head.NID_MESSAGE = 0;
	data.head.L_MESSAGE = 0;
	data.head.T_TRAIN = 0;

	data.pkg.NID_PACKET = 0;
	data.pkg.L_PACKET = 0;
	data.pkg.NID_OPERATIONAL = 0;
	data.pkg.pstato.NID_CDB = 0;
	data.pkg.pstato.Q_STATOCDB = 0;
	data.pkg.pstato.Q_DEVIATIOIO = 0;
	data.pkg.pstato1 = NULL;
}


int pacchettostatolineaatc::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;
	// 51 bit per l'header
	size += 51;
	// 94 per la parte fissa del pacchetto 
	size += 94;
	// 36 bit per ogni N_ITER
	if( data.pkg.N_ITER!=NULL){

		size += 36 * data.pkg.N_ITER;
	}else{
		size += 36 *128;
	}
	// ritorno il numero di byte occupato dalla struttura dati
	return (size / 8) + 1;
}

// funzione che sette N_ITER1
void pacchettostatolineaatc::setN_ITER(int N)
{
	data.pkg.N_ITER = N;
	data.pkg.pstato1 = new pstatolineastruct[N];
}

void pacchettostatolineaatc::setNID_CDB(int index, int D)
{
	if(index == 0)
		data.pkg.pstato.NID_CDB = D;
	else
		data.pkg.pstato1[index - 1].NID_CDB  = D;
}

int pacchettostatolineaatc::getNID_CDB(int index)
{
	if(index == 0)
		return data.pkg.pstato.NID_CDB;
	else
		return data.pkg.pstato1[index - 1].NID_CDB;
}

void pacchettostatolineaatc::setQ_STATOCDB(int index, int D)
{
	if(index == 0)
		data.pkg.pstato.Q_STATOCDB = D;
	else
		data.pkg.pstato1[index - 1].Q_STATOCDB  = D;
}

int pacchettostatolineaatc::getQ_STATOCDB(int index)
{
	if(index == 0)
		return data.pkg.pstato.Q_STATOCDB;
	else
		return data.pkg.pstato1[index - 1].Q_STATOCDB;
}

void pacchettostatolineaatc::setQ_DEVIATIOIO(int index, int D)
{
	if(index == 0)
		data.pkg.pstato.Q_DEVIATIOIO = D;
	else
		data.pkg.pstato1[index - 1].Q_DEVIATIOIO  = D;
}

int pacchettostatolineaatc::getQ_DEVIATIOIO(int index)
{
	if(index == 0)
		return data.pkg.pstato.Q_DEVIATIOIO;
	else
		return data.pkg.pstato1[index - 1].Q_DEVIATIOIO;
}


void pacchettostatolineaatc::serialize(byte *buffer)
{
	push(buffer, data.head.NID_MESSAGE, 8, 0);
	push(buffer, data.head.L_MESSAGE, 11, 8);
	push(buffer, data.head.T_TRAIN, 32, 19);
	push(buffer, data.pkg.NID_PACKET, 8, 51);
	push(buffer, data.pkg.L_PACKET, 13, 59);
	push(buffer, data.pkg.NID_OPERATIONAL, 32, 91);
	push(buffer, data.pkg.pstato.NID_CDB, 32, 123);
	push(buffer, data.pkg.pstato.Q_STATOCDB, 2, 155);
	push(buffer, data.pkg.pstato.Q_DEVIATIOIO, 2, 157);
	push(buffer, data.pkg.N_ITER, 5, 162);
	int offset = 167;
	for(unsigned int i = 0; i < data.pkg.N_ITER; ++i)
	{
		push(buffer, data.pkg.pstato1[i].NID_CDB, 32, offset);
		offset += 32;
		push(buffer, data.pkg.pstato1[i].Q_STATOCDB, 2, offset);
		offset += 2;
		push(buffer, data.pkg.pstato1[i].Q_DEVIATIOIO, 2, offset);
		offset += 2;
	}

}

void pacchettostatolineaatc::deserialize(byte *buffer)
{
	data.head.NID_MESSAGE=pop(buffer, 8, 0);
	data.head.L_MESSAGE=pop(buffer, 11, 8);
	data.head.T_TRAIN=pop(buffer, 32, 19);
	data.pkg.NID_PACKET=pop(buffer,  8, 51);
	data.pkg.L_PACKET=pop(buffer, 13, 59);
	data.pkg.NID_OPERATIONAL=pop(buffer, 32, 91);
	data.pkg.pstato.NID_CDB=pop(buffer, 32, 123);
	data.pkg.pstato.Q_STATOCDB=pop(buffer, 2, 155);
	data.pkg.pstato.Q_DEVIATIOIO=pop(buffer, 2, 157);
	data.pkg.N_ITER=pop(buffer, 5, 162);
	int offset = 167;
	for(unsigned int i = 0; i < data.pkg.N_ITER; ++i)
	{
		data.pkg.pstato1[i].NID_CDB=pop(buffer, 15, offset);
		offset += 32;
		data.pkg.pstato1[i].Q_STATOCDB=pop(buffer, 2, offset);
		offset += 2;
		data.pkg.pstato1[i].Q_STATOCDB=pop(buffer, 2, offset);
		offset += 2;
	}


}