#include "pacchettoStatoItinerario.h"
#include "..\\utility.h"

pacchettoStatoItinerario::pacchettoStatoItinerario(void)
{
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.statoItinerario.NID_ITIN = 0;
	data.statoItinerario.Q_STATOITIN = 0;
	data.N_ITER = 0;
	data.vStatoItinerario = nullptr;
}

// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
void pacchettoStatoItinerario::setN_ITER(int N)
{
	data.N_ITER = N;
	data.vStatoItinerario = new itinerario[N];
	for(int i = 0; i < N; ++i)
	{
		data.vStatoItinerario[i].NID_ITIN = 0;
		data.vStatoItinerario[i].Q_STATOITIN = 0;
	}
}

// in questi metodi index rappresenta l'indice dell'itinerario di cui si vogliono leggere/scrivere le caratteristiche
// se index è 0, il metodo modificherà i dati relativi al primo itinerario, altrimenti modificherà i dati 
// relativi agli altri itinerari.
void pacchettoStatoItinerario::setNID_ITIN(int index, int N)
{
	if(index == 0)
		data.statoItinerario.NID_ITIN = N;
	else
		data.vStatoItinerario[index - 1].NID_ITIN = N;
}

int pacchettoStatoItinerario::getNID_ITIN(int index)
{
	if(index == 0)
		return data.statoItinerario.NID_ITIN;
	else
		return data.vStatoItinerario[index - 1].NID_ITIN;
}

void pacchettoStatoItinerario::setQ_STATOITIN(int index, int Q)
{
	if(index == 0)
		data.statoItinerario.Q_STATOITIN = Q;
	else
		data.vStatoItinerario[index - 1].Q_STATOITIN = Q;
}

int pacchettoStatoItinerario::getQ_STATOITIN(int index)
{
	if(index == 0)
		return data.statoItinerario.Q_STATOITIN;
	else
		return data.vStatoItinerario[index - 1].Q_STATOITIN;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoStatoItinerario::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;
	
	// 38 per la parte fissa
	size += 71;
	// 12 bit per ogni N_ITER
	size += 34 * data.N_ITER;

	return size;
}

void pacchettoStatoItinerario::serialize(byte *buffer, int offset)
{
	push(buffer, data.NID_PACKET, 8, offset + 51);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, offset + 59);
	push(buffer, data.statoItinerario.NID_ITIN, 32, offset + 72);
	push(buffer, data.statoItinerario.Q_STATOITIN, 2, offset + 104);
	push(buffer, data.N_ITER, 16, offset + 106);
	//data.mS1_vect = new missionStruct1[data.N_ITER1];
	int shift = 122;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		push(buffer, data.vStatoItinerario[i].NID_ITIN, 32, offset + shift);
		shift += 32;
		push(buffer, data.vStatoItinerario[i].Q_STATOITIN, 2, offset + shift);
		shift += 2;
	}
}

void pacchettoStatoItinerario::deserialize(byte *buffer, int offset)
{
	
	data.NID_PACKET=pop(buffer,  8, offset + 51);
	data.L_PACKET=pop(buffer, 13, offset + 59);
	data.statoItinerario.NID_ITIN=pop(buffer, 32, offset + 72);
	data.statoItinerario.Q_STATOITIN=pop(buffer, 2, offset + 104);
	setN_ITER(pop(buffer, 16, offset + 106));
	int shift = 122;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		data.vStatoItinerario[i].NID_ITIN=pop(buffer, 32, offset + shift);
		shift += 32;
		data.vStatoItinerario[i].Q_STATOITIN=pop(buffer, 2, offset + shift);
		shift += 2;
	}
}

pacchettoStatoItinerario::~pacchettoStatoItinerario(void)
{
	delete [] data.vStatoItinerario;
}
