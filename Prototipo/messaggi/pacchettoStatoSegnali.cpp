#include "pacchettoStatoSegnali.h"
#include "..\\utility.h"

pacchettoStatoSegnali::pacchettoStatoSegnali(void)
{
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.statoSegnale.NID_SEGN = 0;
	data.statoSegnale.Q_STATOSEGN = 0;
	data.N_ITER = 0;
	data.vStatoSegnale = nullptr;
}

// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
void pacchettoStatoSegnali::setN_ITER(int N)
{
	data.N_ITER = N;
	data.vStatoSegnale = new segnale[N];
	for(int i = 0; i < N; ++i)
	{
		data.vStatoSegnale[i].NID_SEGN = 0;
		data.vStatoSegnale[i].Q_STATOSEGN = 0;
	}
}

// in questi metodi index rappresenta l'indice del segnale di cui si vogliono leggere/scrivere le caratteristiche
// se index è 0, il metodo modificherà i dati relativi al primo segnale, altrimenti modificherà i dati 
// relativi agli altri segnali.
void pacchettoStatoSegnali::setNID_SEGN(int index, int N)
{
	if(index == 0)
		data.statoSegnale.NID_SEGN = N;
	else
		data.vStatoSegnale[index - 1].NID_SEGN = N;
}

int pacchettoStatoSegnali::getNID_SEGN(int index)
{
	if(index == 0)
		return data.statoSegnale.NID_SEGN;
	else
		return data.vStatoSegnale[index - 1].NID_SEGN;
}

void pacchettoStatoSegnali::setQSTATO_SEGN(int index, int Q)
{
	if(index == 0)
		data.statoSegnale.Q_STATOSEGN = Q;
	else
		data.vStatoSegnale[index - 1].Q_STATOSEGN = Q;
}

int pacchettoStatoSegnali::getQSTATO_SEGN(int index)
{
	if(index == 0)
		return data.statoSegnale.Q_STATOSEGN;
	else
		return data.vStatoSegnale[index - 1].Q_STATOSEGN;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoStatoSegnali::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;
	
	// 38 per la parte fissa
	size += 71;
	// 12 bit per ogni N_ITER
	size += 34 * data.N_ITER;

	return size;
}

void pacchettoStatoSegnali::serialize(byte *buffer)
{
	push(buffer, data.NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, 59);
	push(buffer, data.statoSegnale.NID_SEGN, 32, 72);
	push(buffer, data.statoSegnale.Q_STATOSEGN, 2, 104);
	push(buffer, data.N_ITER, 16, 106);
	//data.mS1_vect = new missionStruct1[data.N_ITER1];
	int offset = 122;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		push(buffer, data.vStatoSegnale[i].NID_SEGN, 32, offset);
		offset += 32;
		push(buffer, data.vStatoSegnale[i].Q_STATOSEGN, 2, offset);
		offset += 2;
	}
}

void pacchettoStatoSegnali::deserialize(byte *buffer)
{
	data.NID_PACKET=pop(buffer,  8, 51);
	data.L_PACKET=pop(buffer, 13, 59);
	data.statoSegnale.NID_SEGN=pop(buffer, 32, 72);
	data.statoSegnale.Q_STATOSEGN=pop(buffer, 2, 104);
	setN_ITER(pop(buffer, 16, 106));
	int offset = 122;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		data.vStatoSegnale[i].NID_SEGN=pop(buffer, 32, offset);
		offset += 32;
		data.vStatoSegnale[i].Q_STATOSEGN=pop(buffer, 2, offset);
		offset += 2;
	}
}

pacchettoStatoSegnali::~pacchettoStatoSegnali(void)
{
	delete [] data.vStatoSegnale
}
