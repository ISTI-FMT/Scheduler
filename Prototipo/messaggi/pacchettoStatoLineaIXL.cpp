#include "pacchettoStatoLineaIXL.h"
#include "..\\utility.h"

pacchettoStatoLineaIXL::pacchettoStatoLineaIXL(void)
{
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.statoCDB.NID_CDB = 0;
	data.statoCDB.Q_STATOCDB = 0;
	data.statoCDB.Q_DEVIATOIO = 0;
	data.N_ITER = 0;
	data.vStatoCDB = nullptr;
}

// metodo che setta N_ITER
void pacchettoStatoLineaIXL::setN_ITER(int N)
{
	data.N_ITER = N;
	data.vStatoCDB = new CDB[N];
	for(int i = 0; i < N; ++i)
	{
		data.vStatoCDB[i].NID_CDB = 0;
		data.vStatoCDB[i].Q_STATOCDB = 0;
		data.vStatoCDB[i].Q_DEVIATOIO = 0;
	}
}

// in questi metodi index rappresenta l'indice del CDB di cui si vogliono leggere/scrivere le caratteristiche
// se index è 0, il metodo modificherà i dati relativi al primo CDB, altrimenti modificherà i dati 
// relativi agli altri CDB.
void pacchettoStatoLineaIXL::setNID_CDB(int index, int N)
{
	if(index == 0)
		data.statoCDB.NID_CDB = N;
	else
		data.vStatoCDB[index - 1].NID_CDB = N;
}

int pacchettoStatoLineaIXL::getNID_CDB(int index)
{
	if(index == 0)
		return data.statoCDB.NID_CDB;
	else
		return data.vStatoCDB[index - 1].NID_CDB;
}

void pacchettoStatoLineaIXL::setQ_STATOCDB(int index, int Q)
{
	if(index == 0)
		data.statoCDB.Q_STATOCDB = Q;
	else
		data.vStatoCDB[index - 1].Q_STATOCDB = Q;
}

int pacchettoStatoLineaIXL::getQ_STATOCDB(int index)
{
	if(index == 0)
		return data.statoCDB.Q_STATOCDB;
	else
		return data.vStatoCDB[index - 1].Q_STATOCDB;
}

void pacchettoStatoLineaIXL::setQ_DEVIATOIO(int index, int Q)
{
	if(index == 0)
		data.statoCDB.Q_DEVIATOIO = Q;
	else
		data.vStatoCDB[index - 1].Q_DEVIATOIO = Q;
}

int pacchettoStatoLineaIXL::getQ_DEVIATOIO(int index)
{
	if(index == 0)
		return data.statoCDB.Q_DEVIATOIO;
	else
		return data.vStatoCDB[index - 1].Q_DEVIATOIO;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoStatoLineaIXL::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;
	
	// 38 per la parte fissa
	size += 73;
	// 12 bit per ogni N_ITER
	size += 36 * data.N_ITER;

	return size;
}

void pacchettoStatoLineaIXL::serialize(byte *buffer)
{
	push(buffer, data.NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, 59);
	push(buffer, data.statoCDB.NID_CDB, 32, 72);
	push(buffer, data.statoCDB.Q_STATOCDB, 2, 104);
	push(buffer, data.statoCDB.Q_DEVIATOIO, 2, 106);
	push(buffer, data.N_ITER, 16, 108);
	//data.mS1_vect = new missionStruct1[data.N_ITER1];
	int offset = 124;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		push(buffer, data.vStatoCDB[i].NID_CDB, 32, offset);
		offset += 32;
		push(buffer, data.vStatoCDB[i].Q_STATOCDB, 2, offset);
		offset += 2;
		push(buffer, data.vStatoCDB[i].Q_DEVIATOIO, 2, offset);
		offset += 2;
	}
}

void pacchettoStatoLineaIXL::deserialize(byte *buffer)
{
	
	data.NID_PACKET=pop(buffer,  8, 51);
	data.L_PACKET=pop(buffer, 13, 59);
	data.statoCDB.NID_CDB=pop(buffer, 32, 72);
	data.statoCDB.Q_STATOCDB=pop(buffer, 2, 104);
	data.statoCDB.Q_DEVIATOIO=pop(buffer, 2, 106);
	setN_ITER(pop(buffer, 16, 108));
	int offset = 124;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		data.vStatoCDB[i].NID_CDB=pop(buffer, 32, offset);
		offset += 32;
		data.vStatoCDB[i].Q_STATOCDB=pop(buffer, 2, offset);
		offset += 2;
		data.vStatoCDB[i].Q_DEVIATOIO=pop(buffer, 2, offset);
		offset += 2;
	}
}

pacchettoStatoLineaIXL::~pacchettoStatoLineaIXL(void)
{
	delete [] data.vStatoCDB;
}
