#include "pacchettoStatoBlocco.h"
#include "utility.h"

pacchettoStatoBlocco::pacchettoStatoBlocco(void)
{
	setNID_PACKET(PacchettoID::StatoBloccoIXL);
	setL_PACKET(0);
	setN_ITER(0);
	setStatoBlocco(gcnew List<StateBlocco^>());
}

void pacchettoStatoBlocco::setN_ITER(int N)
{
	N_ITER = N;
}

int pacchettoStatoBlocco::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;

	// 38 per la parte fissa
	size += 71;
	// 12 bit per ogni N_ITER
	size += 34 * N_ITER;

	return size;
}

void pacchettoStatoBlocco::serialize(array<Byte>^buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset );
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset +8);
	utility::push(buffer, vStatoBlocco[0]->getNID_BLOCCO(), 32, offset + 21);
	utility::push(buffer, vStatoBlocco[0]->getQ_STATOBLOCCO(), 2, offset + 53);
	utility::push(buffer, N_ITER, 16, offset + 55);
	//mS1_vect = new missionStruct1[N_ITER1];
	int shift = 71;
	for( int i =1; i <vStatoBlocco->Count;i++)
	{
		utility::push(buffer, vStatoBlocco[i]->getNID_BLOCCO(), 32, offset + shift);
		shift += 32;
		utility::push(buffer, vStatoBlocco[i]->getQ_STATOBLOCCO(), 2, offset + shift);
		shift += 2;
	}
}

void pacchettoStatoBlocco::deserialize(array<Byte>^buffer, int offset)
{
	NID_PACKET=utility::pop(buffer,  8, offset );
	L_PACKET=utility::pop(buffer, 13, offset + 8);
	int tNID_BLOCCO= utility::pop(buffer, 32, offset + 21);
	int tQ_STATOBLOCCO =utility::pop(buffer, 2, offset + 53);

	setStatoBlocco(gcnew StateBlocco(tNID_BLOCCO,tQ_STATOBLOCCO));
	setN_ITER(utility::pop(buffer, 16, offset + 55));
	int shift = 71;
	for(int i = 0; i < N_ITER; ++i)
	{
		int NID_BLOCCO=utility::pop(buffer, 32, offset + shift);
		shift += 32;
		int Q_STATOBLOCCO=utility::pop(buffer, 2, offset + shift);
		shift += 2;
		setStatoBlocco(gcnew StateBlocco(NID_BLOCCO,Q_STATOBLOCCO));
	}
}

System::String ^pacchettoStatoBlocco::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+get_NID_PACKET()+";";
	out = out+"L_PACKET: "+getL_PACKET()+";";
	out = out+getStatoBlocco()[0]->ToString();
	out = out+"N_ITER: "+getN_ITER()+";";

	for( int i = 1; i <getStatoBlocco()->Count; i++)
	{
		out = out+getStatoBlocco()[i]->ToString();
	}

	return out;
}