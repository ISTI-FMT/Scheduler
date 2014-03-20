#include "pacchettoStatoLineaIXL.h"
#include "utility.h"

pacchettoStatoLineaIXL::pacchettoStatoLineaIXL(void)
{
	setNID_PACKET(PacchettoID::StatoLineaIXL);
	L_PACKET = 0;

	N_ITER = 0;
	vStatoCDB = gcnew List<StateCDB^>();
}

void pacchettoStatoLineaIXL::setN_ITER(int N)
{
	N_ITER = N;

}

int pacchettoStatoLineaIXL::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;

	// 38 per la parte fissa
	size += 73;
	// 12 bit per ogni N_ITER
	size += 36 * N_ITER;

	return size;
}

void pacchettoStatoLineaIXL::serialize(array<Byte>^buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
	offset += 8;
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset);
	offset += 13;
	utility::push(buffer, vStatoCDB[0]->getNID_CDB(), 32, offset);
	offset += 32;
	utility::push(buffer, vStatoCDB[0]->getQ_STATOCDB(), 2, offset);
	offset += 2;
	utility::push(buffer, vStatoCDB[0]->getQ_DEVIATOIO(), 2, offset);
	offset += 2;
	utility::push(buffer, N_ITER, 16, offset);
	offset += 16;
	for ( int i=1;i<vStatoCDB->Count;i++)
	{
		utility::push(buffer, vStatoCDB[i]->getNID_CDB(), 32, offset);
		offset += 32;
		utility::push(buffer, vStatoCDB[i]->getQ_STATOCDB(), 2, offset);
		offset += 2;
		utility::push(buffer, vStatoCDB[i]->getQ_DEVIATOIO(), 2, offset);
		offset += 2;
	}
}

void pacchettoStatoLineaIXL::deserialize(array<Byte>^buffer, int offset)
{
	NID_PACKET=utility::pop(buffer,  8, offset);
	offset += 8;
	L_PACKET=utility::pop(buffer, 13, offset);
	offset += 13;
	int tNID_CDB =utility::pop(buffer, 32, offset);
	offset += 32;
	int tQ_STATOCDB =utility::pop(buffer, 2, offset);
	offset += 2;
	int tQ_DEVIATOIO =utility::pop(buffer, 2, offset);
	offset += 2;
	vStatoCDB->Add(gcnew StateCDB(tNID_CDB,tQ_STATOCDB,tQ_DEVIATOIO));
	setN_ITER(utility::pop(buffer, 16, offset));
	offset += 16;
	for(int i = 0; i < N_ITER; ++i)
	{
		int NID_CDB=utility::pop(buffer, 32, offset);
		offset += 32;
		int Q_STATOCDB=utility::pop(buffer, 2, offset);
		offset += 2;
		int Q_DEVIATOIO=utility::pop(buffer, 2, offset);
		offset += 2;

		vStatoCDB->Add(gcnew StateCDB(NID_CDB,Q_STATOCDB,Q_DEVIATOIO));
	}
}



System::String^ pacchettoStatoLineaIXL::ToString(){
	String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";

	out = out+vStatoCDB[0]->ToString();
	out = out+"N_ITER: "+N_ITER+";";

	for  ( int i = 1; i<vStatoCDB->Count; i++)
	{
		out = out+vStatoCDB[i]->ToString();
	}

	return out;
}
