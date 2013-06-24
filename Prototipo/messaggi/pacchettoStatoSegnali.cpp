#include "pacchettoStatoSegnali.h"
#include "utility.h"

pacchettoStatoSegnali::pacchettoStatoSegnali(void)
{
	NID_PACKET = 0;
	L_PACKET = 0;

	N_ITER = 0;
	vStatoSegnale = gcnew List<StateSegnale^>();
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
	utility::push(buffer, NID_PACKET, 8, offset);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset +8);
	utility::push(buffer, vStatoSegnale[0]->getNID_SEGN(), 32, offset + 21);
	utility::push(buffer, vStatoSegnale[0]->getQSTATO_SEGN(), 2, offset + 53);
	utility::push(buffer, N_ITER, 16, offset + 55);
	//mS1_vect = new missionStruct1[N_ITER1];
	int shift = 71;
	for( int i =1; i <vStatoSegnale->Count;i++)
	{
		utility::push(buffer, vStatoSegnale[i]->getNID_SEGN(), 32, offset + shift);
		shift += 32;
		utility::push(buffer, vStatoSegnale[i]->getQSTATO_SEGN(), 5, offset + shift);
		shift += 5;
	}

}

void pacchettoStatoSegnali::deserialize(byte *buffer, int offset)
{
	NID_PACKET=utility::pop(buffer,  8, offset );
	L_PACKET=utility::pop(buffer, 13, offset + 8);
	int tNID_SEGN = utility::pop(buffer, 32, offset + 21);
	int tQSTATO_SEGN = utility::pop(buffer, 2, offset + 53);
	vStatoSegnale->Add(gcnew StateSegnale(tNID_SEGN,tQSTATO_SEGN));
	setN_ITER(utility::pop(buffer, 16, offset + 55));
	int shift = 71;
	for(unsigned int i = 0; i < N_ITER; ++i)
	{
		int NID_SEGN=utility::pop(buffer, 32, offset + shift);
		shift += 32;
		int Q_STATOSEGN=utility::pop(buffer, 5, offset + shift);
		shift += 5;
		vStatoSegnale->Add(gcnew StateSegnale(NID_SEGN,Q_STATOSEGN));
	}
}





System::String ^pacchettoStatoSegnali::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+vStatoSegnale[0]->ToString();
	out = out+"N_ITER: "+N_ITER+";";

	for( int i =1; i <vStatoSegnale->Count;i++)
	{


		out = out+vStatoSegnale[i]->ToString();

	}

	return out;
}