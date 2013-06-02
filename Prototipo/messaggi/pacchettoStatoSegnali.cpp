#include "pacchettoStatoSegnali.h"
#include "utility.h"

pacchettoStatoSegnali::pacchettoStatoSegnali(void)
{
	NID_PACKET = 0;
	L_PACKET = 0;
	statoSegnale = gcnew stateSegnale();
	N_ITER = 0;
	vStatoSegnale = gcnew List<stateSegnale^>();
}

// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
void pacchettoStatoSegnali::setN_ITER(int N)
{
	N_ITER = N;

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
	size += 37 * N_ITER;

	return size;
}

void pacchettoStatoSegnali::serialize(byte *buffer, int offset)
{
	push(buffer, NID_PACKET, 8, offset);
	setL_PACKET(getSize());
	push(buffer, L_PACKET, 13, offset +8);
	push(buffer, statoSegnale->getNID_SEGN(), 32, offset + 21);
	push(buffer, statoSegnale->getQSTATO_SEGN(), 2, offset + 53);
	push(buffer, N_ITER, 16, offset + 55);
	//mS1_vect = new missionStruct1[N_ITER1];
	int shift = 71;
	for each (stateSegnale ^var in vStatoSegnale)
	{
		push(buffer, var->getNID_SEGN(), 32, offset + shift);
		shift += 32;
		push(buffer, var->getQSTATO_SEGN(), 5, offset + shift);
		shift += 5;
	}

}

void pacchettoStatoSegnali::deserialize(byte *buffer, int offset)
{
	NID_PACKET=pop(buffer,  8, offset );
	L_PACKET=pop(buffer, 13, offset + 8);
	statoSegnale->setNID_SEGN(pop(buffer, 32, offset + 21));
	statoSegnale->setQSTATO_SEGN(pop(buffer, 2, offset + 53));
	setN_ITER(pop(buffer, 16, offset + 55));
	int shift = 71;
	for(unsigned int i = 0; i < N_ITER; ++i)
	{
		int NID_SEGN=pop(buffer, 32, offset + shift);
		shift += 32;
		int Q_STATOSEGN=pop(buffer, 5, offset + shift);
		shift += 5;
		vStatoSegnale->Add(gcnew stateSegnale(NID_SEGN,Q_STATOSEGN));
	}
}





System::String ^pacchettoStatoSegnali::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+statoSegnale->ToString();
	out = out+"N_ITER: "+N_ITER+";";
	if(vStatoSegnale){
		for each (stateSegnale^ var in vStatoSegnale)
		{


			out = out+var->ToString();

		}
	}
	return out;
}