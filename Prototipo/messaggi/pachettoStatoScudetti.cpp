#include "pachettoStatoScudetti.h"

#include "..\\utility.h"

pachettoStatoScudetti::pachettoStatoScudetti(void)
{
	
	data->NID_PACKET = 0;
	data->L_PACKET = 0;
	data->statoscudetti.NID_SCUD = 0;
	data->statoscudetti.Q_STATOSCUD = 0;
	data->N_ITER = 0;
	data->vStatoScudetti = nullptr;
}

// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
void pachettoStatoScudetti::setN_ITER(int N)
{
	data->N_ITER = N;
	data->vStatoScudetti = new scudetti[N];
	for(int i = 0; i < N; ++i)
	{
		data->vStatoScudetti[i].NID_SCUD = 0;
		data->vStatoScudetti[i].Q_STATOSCUD = 0;
	}
}

// in questi metodi index rappresenta l'indice dell'itinerario di cui si vogliono leggere/scrivere le caratteristiche
// se index è 0, il metodo modificherà i dati relativi al primo itinerario, altrimenti modificherà i dati 
// relativi agli altri itinerari.
void pachettoStatoScudetti::setNID_SCUD(int index, int N)
{
	if(index == 0)
		data->statoscudetti.NID_SCUD = N;
	else
		data->vStatoScudetti[index - 1].NID_SCUD = N;
}

int pachettoStatoScudetti::getNID_SCUD(int index)
{
	if(index == 0)
		return data->statoscudetti.NID_SCUD;
	else
		return data->vStatoScudetti[index - 1].NID_SCUD;
}

void pachettoStatoScudetti::setQ_STATOSCUD(int index, int Q)
{
	if(index == 0)
		data->statoscudetti.Q_STATOSCUD = Q;
	else
		data->vStatoScudetti[index - 1].Q_STATOSCUD = Q;
}

int pachettoStatoScudetti::getQ_STATOSCUD(int index)
{
	if(index == 0)
		return data->statoscudetti.Q_STATOSCUD;
	else
		return data->vStatoScudetti[index - 1].Q_STATOSCUD;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pachettoStatoScudetti::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;
	
	
	size += 72;
	// 12 bit per ogni N_ITER
	size += 34 * data->N_ITER;

	return size;
}

void pachettoStatoScudetti::serialize(byte *buffer, int offset)
{
	push(buffer, data->NID_PACKET, 8, offset);
	setL_PACKET(getSize());
	push(buffer, data->L_PACKET, 13, offset + 8);
	push(buffer, data->statoscudetti.NID_SCUD, 32, offset + 21);
	push(buffer, data->statoscudetti.Q_STATOSCUD, 3, offset + 53);
	push(buffer, data->N_ITER, 16, offset + 56);
	//data->mS1_vect = new missionStruct1[data->N_ITER1];
	int shift = 72;
	for(unsigned int i = 0; i < data->N_ITER; ++i)
	{
		push(buffer, data->vStatoScudetti[i].NID_SCUD, 32, offset + shift);
		shift += 32;
		push(buffer, data->vStatoScudetti[i].Q_STATOSCUD,3, offset + shift);
		shift += 3;
	}
}

void pachettoStatoScudetti::deserialize(byte *buffer, int offset)
{
	
	data->NID_PACKET=pop(buffer,  8, offset);
	data->L_PACKET=pop(buffer, 13, offset + 8);
	data->statoscudetti.NID_SCUD=pop(buffer, 32, offset + 21);
	data->statoscudetti.Q_STATOSCUD=pop(buffer, 3, offset + 53);
	setN_ITER(pop(buffer, 16, offset + 56));
	int shift = 72;
	for(unsigned int i = 0; i < data->N_ITER; ++i)
	{
		data->vStatoScudetti[i].NID_SCUD=pop(buffer, 32, offset + shift);
		shift += 32;
		data->vStatoScudetti[i].Q_STATOSCUD=pop(buffer, 3, offset + shift);
		shift += 2;
	}
}

pachettoStatoScudetti::~pachettoStatoScudetti(void)
{
	delete [] data->vStatoScudetti;
}


System::String ^pachettoStatoScudetti::ToString(){
		System::String ^out;

	out = out+"NID_PACKET: "+data->NID_PACKET+";";
	out = out+"L_PACKET: "+data->L_PACKET+";";
	out = out+"NID_SCUD: "+data->statoscudetti.NID_SCUD+";";
	out = out+"Q_STATOSCUD: "+data->statoscudetti.Q_STATOSCUD+";";
	out = out+"N_ITER: "+data->N_ITER+";";
	if(data->vStatoScudetti){
			for(unsigned int i=0;i<data->N_ITER;i++){
				out = out+"NID_SCUD: "+data->vStatoScudetti[i].NID_SCUD+";";
				out = out+"Q_STATOSCUD: "+data->vStatoScudetti[i].Q_STATOSCUD+";";

			}
		}
	 return out;
}


