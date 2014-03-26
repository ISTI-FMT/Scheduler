#include "pacchettoStatoSegnali.h"
#include "utility.h"

pacchettoStatoSegnali::pacchettoStatoSegnali(void)
{
	setNID_PACKET(PacchettoID::StatoSegnali);
	setL_PACKET(0);

	setN_ITER(0);
	setstatoSegnale( gcnew List<StateSegnale^>());
}

void pacchettoStatoSegnali::setN_ITER(int N)
{
	N_ITER = N;
}

int pacchettoStatoSegnali::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;

	// 38 per la parte fissa
	size += 74;
	// 12 bit per ogni N_ITER
	if(N_ITER>0){
		size += 37 * N_ITER;
	}

	return size;
}

void pacchettoStatoSegnali::serialize(array<Byte>^buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset +8);
	utility::push(buffer, vStatoSegnale[0]->getNID_SEGN(), 32, offset + 21);
	utility::push(buffer, vStatoSegnale[0]->getQSTATO_SEGN(), 5, offset + 53);
	utility::push(buffer, N_ITER, 16, offset + 58);
	int shift = 74;
	for( int i =1; i <vStatoSegnale->Count;i++)
	{
		utility::push(buffer, vStatoSegnale[i]->getNID_SEGN(), 32, offset + shift);
		shift += 32;
		utility::push(buffer, vStatoSegnale[i]->getQSTATO_SEGN(), 5, offset + shift);
		shift += 5;
	}

}

void pacchettoStatoSegnali::deserialize(array<Byte>^buffer, int offset)
{
	NID_PACKET=utility::pop(buffer,  8, offset );
	L_PACKET=utility::pop(buffer, 13, offset + 8);
	int tNID_SEGN = utility::pop(buffer, 32, offset + 21);
	int tQSTATO_SEGN = utility::pop(buffer, 5, offset + 53);
	vStatoSegnale->Add(gcnew StateSegnale(tNID_SEGN,tQSTATO_SEGN));
	setN_ITER(utility::pop(buffer, 16, offset + 58));
	int shift = 74;
	for(int i = 0; i < N_ITER; ++i)
	{
		int NID_SEGN=utility::pop(buffer, 32, offset + shift);
		shift += 32;
		int Q_STATOSEGN=utility::pop(buffer, 5, offset + shift);
		shift += 5;
		setstatoSegnale(gcnew StateSegnale(NID_SEGN,Q_STATOSEGN));
	}
}

System::String ^pacchettoStatoSegnali::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+get_NID_PACKET()+";";
	out = out+"L_PACKET: "+getL_PACKET()+";";
	out = out+getstatoSegnale()[0]->ToString();
	out = out+"N_ITER: "+getN_ITER()+";";

	for( int i =1; i <getstatoSegnale()->Count;i++)
	{
		out = out+getstatoSegnale()[i]->ToString();
	}

	return out;
}