#include "pacchettoStatoLineaIXL.h"
#include "utility.h"

pacchettoStatoLineaIXL::pacchettoStatoLineaIXL(void)
{
	NID_PACKET = 0;
	L_PACKET = 0;
	sCDB = gcnew StateCDB();
	N_ITER = 0;
	vStatoCDB = gcnew List<StateCDB^>();
}

// metodo che setta N_ITER
void pacchettoStatoLineaIXL::setN_ITER(int N)
{
	N_ITER = N;

}


// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sar� chiamata da chi vorr� serializzare il messaggio, per poter allocare il buffer
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

void pacchettoStatoLineaIXL::serialize(byte *buffer)
{
	utility::push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, 59);
	utility::push(buffer, sCDB->getNID_CDB(), 32, 72);
	utility::push(buffer, sCDB->getQ_STATOCDB(), 2, 104);
	utility::push(buffer, sCDB->getQ_DEVIATOIO(), 2, 106);
	utility::push(buffer, N_ITER, 16, 108);
	//mS1_vect = new missionStruct1[N_ITER1];
	int offset = 124;
	for each (StateCDB^ var in vStatoCDB )
	{

		utility::push(buffer, var->getNID_CDB(), 32, offset);
		offset += 32;
		utility::push(buffer, var->getQ_STATOCDB(), 2, offset);
		offset += 2;
		utility::push(buffer, var->getQ_DEVIATOIO(), 2, offset);
		offset += 2;
	}
}

void pacchettoStatoLineaIXL::deserialize(byte *buffer)
{

	NID_PACKET=utility::pop(buffer,  8, 51);
	L_PACKET=utility::pop(buffer, 13, 59);
	sCDB->setNID_CDB(utility::pop(buffer, 32, 72));
	sCDB->setQ_STATOCDB(utility::pop(buffer, 2, 104));
	sCDB->setQ_DEVIATOIO(utility::pop(buffer, 2, 106));
	setN_ITER(utility::pop(buffer, 16, 108));
	int offset = 124;
	for(unsigned int i = 0; i < N_ITER; ++i)
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

	out = out+sCDB->ToString();
	out = out+"N_ITER: "+N_ITER+";";
	if(vStatoCDB){
		for each (StateCDB^ var in vStatoCDB)
		{
			out = out+var->ToString();
		}
	}
	return out;
}
