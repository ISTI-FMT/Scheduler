#include "pacchettoStatoBlocco.h"
#include "..\\utility.h"

pacchettoStatoBlocco::pacchettoStatoBlocco(void)
{
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.statoBlocco.NID_BLOCCO = 0;
	data.statoBlocco.Q_STATOBLOCCO = 0;
	data.N_ITER = 0;
	data.vStatoBlocco = nullptr;
}

// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
void pacchettoStatoBlocco::setN_ITER(int N)
{
	data.N_ITER = N;
	data.vStatoBlocco = new blocco[N];
	for(int i = 0; i < N; ++i)
	{
		data.vStatoBlocco[i].NID_BLOCCO = 0;
		data.vStatoBlocco[i].Q_STATOBLOCCO = 0;
	}
}

// in questi metodi index rappresenta l'indice dell'itinerario di cui si vogliono leggere/scrivere le caratteristiche
// se index è 0, il metodo modificherà i dati relativi al primo itinerario, altrimenti modificherà i dati 
// relativi agli altri itinerari.
void pacchettoStatoBlocco::setNID_ITIN(int index, int N)
{
	if(index == 0)
		data.statoBlocco.NID_BLOCCO = N;
	else
		data.vStatoBlocco[index - 1].NID_BLOCCO = N;
}

int pacchettoStatoBlocco::getNID_ITIN(int index)
{
	if(index == 0)
		return data.statoBlocco.NID_BLOCCO;
	else
		return data.vStatoBlocco[index - 1].NID_BLOCCO;
}

void pacchettoStatoBlocco::setQSTATO_ITIN(int index, int Q)
{
	if(index == 0)
		data.statoBlocco.Q_STATOBLOCCO = Q;
	else
		data.vStatoBlocco[index - 1].Q_STATOBLOCCO = Q;
}

int pacchettoStatoBlocco::getQSTATO_ITIN(int index)
{
	if(index == 0)
		return data.statoBlocco.Q_STATOBLOCCO;
	else
		return data.vStatoBlocco[index - 1].Q_STATOBLOCCO;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoStatoBlocco::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;
	
	// 38 per la parte fissa
	size += 71;
	// 12 bit per ogni N_ITER
	size += 34 * data.N_ITER;

	return size;
}

void pacchettoStatoBlocco::serialize(byte *buffer)
{
	push(buffer, data.NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, 59);
	push(buffer, data.statoBlocco.NID_BLOCCO, 32, 72);
	push(buffer, data.statoBlocco.Q_STATOBLOCCO, 2, 104);
	push(buffer, data.N_ITER, 16, 106);
	//data.mS1_vect = new missionStruct1[data.N_ITER1];
	int offset = 122;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		push(buffer, data.vStatoBlocco[i].NID_BLOCCO, 32, offset);
		offset += 32;
		push(buffer, data.vStatoBlocco[i].Q_STATOBLOCCO, 2, offset);
		offset += 2;
	}
}

void pacchettoStatoBlocco::deserialize(byte *buffer)
{
	
	data.NID_PACKET=pop(buffer,  8, 51);
	data.L_PACKET=pop(buffer, 13, 59);
	data.statoBlocco.NID_BLOCCO=pop(buffer, 32, 72);
	data.statoBlocco.Q_STATOBLOCCO=pop(buffer, 2, 104);
	setN_ITER(pop(buffer, 16, 106));
	int offset = 122;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		data.vStatoBlocco[i].NID_BLOCCO=pop(buffer, 32, offset);
		offset += 32;
		data.vStatoBlocco[i].Q_STATOBLOCCO=pop(buffer, 2, offset);
		offset += 2;
	}
}

pacchettoStatoBlocco::~pacchettoStatoBlocco(void)
{
	delete [] data.vStatoBlocco;
}
