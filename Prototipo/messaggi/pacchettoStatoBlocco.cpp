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

// metodo che setta N_ITER
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

// in questi metodi index rappresenta l'indice del blocco di cui si vogliono leggere/scrivere le caratteristiche
// se index è 0, il metodo modificherà i dati relativi al primo blocco, altrimenti modificherà i dati 
// relativi agli altri blocchi.
void pacchettoStatoBlocco::setNID_BLOCCO(int index, int N)
{
	if(index == 0)
		data.statoBlocco.NID_BLOCCO = N;
	else
		data.vStatoBlocco[index - 1].NID_BLOCCO = N;
}

int pacchettoStatoBlocco::getNID_BLOCCO(int index)
{
	if(index == 0)
		return data.statoBlocco.NID_BLOCCO;
	else
		return data.vStatoBlocco[index - 1].NID_BLOCCO;
}

void pacchettoStatoBlocco::setQ_STATOBLOCCO(int index, int Q)
{
	if(index == 0)
		data.statoBlocco.Q_STATOBLOCCO = Q;
	else
		data.vStatoBlocco[index - 1].Q_STATOBLOCCO = Q;
}

int pacchettoStatoBlocco::getQ_STATOBLOCCO(int index)
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

void pacchettoStatoBlocco::serialize(byte *buffer, int offset)
{
	push(buffer, data.NID_PACKET, 8, offset + 51);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, offset + 59);
	push(buffer, data.statoBlocco.NID_BLOCCO, 32, offset + 72);
	push(buffer, data.statoBlocco.Q_STATOBLOCCO, 2, offset + 104);
	push(buffer, data.N_ITER, 16, offset + 106);
	//data.mS1_vect = new missionStruct1[data.N_ITER1];
	int shift = 122;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		push(buffer, data.vStatoBlocco[i].NID_BLOCCO, 32, offset + shift);
		shift += 32;
		push(buffer, data.vStatoBlocco[i].Q_STATOBLOCCO, 2, offset + shift);
		shift += 2;
	}
}

void pacchettoStatoBlocco::deserialize(byte *buffer, int offset)
{
	
	data.NID_PACKET=pop(buffer,  8, offset + 51);
	data.L_PACKET=pop(buffer, 13, offset + 59);
	data.statoBlocco.NID_BLOCCO=pop(buffer, 32, offset + 72);
	data.statoBlocco.Q_STATOBLOCCO=pop(buffer, 2, offset + 104);
	setN_ITER(pop(buffer, 16, offset + 106));
	int shift = 122;
	for(unsigned int i = 0; i < data.N_ITER; ++i)
	{
		data.vStatoBlocco[i].NID_BLOCCO=pop(buffer, 32, offset + shift);
		shift += 32;
		data.vStatoBlocco[i].Q_STATOBLOCCO=pop(buffer, 2, offset + shift);
		shift += 2;
	}
}

pacchettoStatoBlocco::~pacchettoStatoBlocco(void)
{
	delete [] data.vStatoBlocco;
}

System::String ^pacchettoStatoBlocco::ToString(){
		System::String ^out;

	out = out+"NID_PACKET: "+data.NID_PACKET+";";
	out = out+"L_PACKET: "+data.L_PACKET+";";
	out = out+"NID_BLOCCO: "+data.statoBlocco.NID_BLOCCO+";";
	out = out+"Q_STATOBLOCCO: "+data.statoBlocco.Q_STATOBLOCCO+";";
	out = out+"N_ITER: "+data.N_ITER+";";
	if(data.vStatoBlocco){
			for(unsigned int i=0;i<data.N_ITER;i++){
				out = out+"NID_BLOCCO: "+data.vStatoBlocco[i].NID_BLOCCO+";";
				out = out+"Q_STATOBLOCCO: "+data.vStatoBlocco[i].Q_STATOBLOCCO+";";

			}
		}
	 return out;
}