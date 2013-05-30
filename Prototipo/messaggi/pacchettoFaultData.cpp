#include "pacchettoFaultData.h"
#include "..\\utility.h"

pacchettoFaultData::pacchettoFaultData(void)
{
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.guasto.NID_COMPONENT = 0;
	data.guasto.M_FAULT = 0;
	data.N_ITER = 0;
	data.vGuasto = nullptr;
}

// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
void pacchettoFaultData::setN_ITER(int N)
{
	data.N_ITER = N;
	data.vGuasto = new fault[N];
	for(int i = 0; i < N; ++i)
	{
		data.vGuasto[i].NID_COMPONENT = 0;
		data.vGuasto[i].M_FAULT = 0;
	}
}

// in questi metodi index rappresenta l'indice del guasto di cui si vogliono leggere/scrivere le caratteristiche
// se index è 0, il metodo modificherà i dati relativi al primo guasto, altrimenti modificherà i dati 
// relativi agli altri guasti.
void pacchettoFaultData::setNID_COMPONENT(int index, int N)
{
	if(index == 0)
		data.guasto.NID_COMPONENT = N;
	else
		data.vGuasto[index - 1].NID_COMPONENT = N;
}

int pacchettoFaultData::getNID_COMPONENT(int index)
{
	if(index == 0)
		return data.guasto.NID_COMPONENT;
	else
		return data.vGuasto[index - 1].NID_COMPONENT;
}

void pacchettoFaultData::setM_FAULT(int index, int M)
{
	if(index == 0)
		data.guasto.M_FAULT = M;
	else
		data.vGuasto[index - 1].M_FAULT = M;
}

int pacchettoFaultData::getM_FAULT(int index)
{
	if(index == 0)
		return data.guasto.M_FAULT;
	else
		return data.vGuasto[index - 1].M_FAULT;
}

pacchettoFaultData::~pacchettoFaultData(void)
{
	delete [] data.vGuasto;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoFaultData::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;
	
	// 38 per la parte fissa
	size += 38;
	// 12 bit per ogni N_ITER
	size += 12 * data.N_ITER;

	return size;
}

void pacchettoFaultData::serialize(byte *buffer)
{
	push(buffer, data.NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, 59);
	push(buffer, data.guasto.NID_COMPONENT, 4, 72);
	push(buffer, data.guasto.M_FAULT, 8, 76);
	push(buffer, data.N_ITER, 5, 84);
	//data.mS1_vect = new missionStruct1[data.N_ITER1];
	int offset = 89;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		push(buffer, data.vGuasto[i].NID_COMPONENT, 4, offset);
		offset += 4;
		push(buffer, data.vGuasto[i].M_FAULT, 8, offset);
		offset += 8;
	}
}

void pacchettoFaultData::deserialize(byte *buffer)
{
	data.NID_PACKET=pop(buffer,  8, 51);
	data.L_PACKET=pop(buffer, 13, 59);
	data.guasto.NID_COMPONENT=pop(buffer, 4, 72);
	data.guasto.M_FAULT=pop(buffer, 8, 76);
	setN_ITER(pop(buffer, 5, 84));
	int offset = 89;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		data.vGuasto[i].NID_COMPONENT=pop(buffer, 4, offset);
		offset += 4;
		data.vGuasto[i].M_FAULT=pop(buffer, 8, offset);
		offset += 8;
	}
}


System::String ^pacchettoFaultData::ToString(){
		System::String ^out;

	out = out+"NID_PACKET: "+data.NID_PACKET+";";
	out = out+"L_PACKET: "+data.L_PACKET+";";
	out = out+"NID_COMPONENT: "+data.guasto.NID_COMPONENT+";";
	out = out+"M_FAULT: "+data.guasto.M_FAULT+";";
	out = out+"N_ITER: "+data.N_ITER+";";
	if(data.vGuasto){
			for(unsigned int i=0;i<data.N_ITER;i++){
				out = out+"NID_COMPONENT: "+data.vGuasto[i].NID_COMPONENT+";";
				out = out+"M_FAULT: "+data.vGuasto[i].M_FAULT+";";

			}
		}
	 return out;
}