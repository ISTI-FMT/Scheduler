#include "pacchettoStatoLineaIXL.h"
#include "utility.h"

pacchettoStatoLineaIXL::pacchettoStatoLineaIXL(void)
{
	NID_PACKET = 0;
	L_PACKET = 0;
	sCDB = gcnew stateCDB();
	N_ITER = 0;
	vStatoCDB = gcnew List<stateCDB^>();
}

// metodo che setta N_ITER
void pacchettoStatoLineaIXL::setN_ITER(int N)
{
	N_ITER = N;

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
	size += 36 * N_ITER;

	return size;
}

void pacchettoStatoLineaIXL::serialize(byte *buffer)
{
	push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, L_PACKET, 13, 59);
	push(buffer, sCDB->getNID_CDB(), 32, 72);
	push(buffer, sCDB->getQ_STATOCDB(), 2, 104);
	push(buffer, sCDB->getQ_DEVIATOIO(), 2, 106);
	push(buffer, N_ITER, 16, 108);
	//mS1_vect = new missionStruct1[N_ITER1];
	int offset = 124;
	for each (stateCDB^ var in vStatoCDB )
	{

		push(buffer, var->getNID_CDB(), 32, offset);
		offset += 32;
		push(buffer, var->getQ_STATOCDB(), 2, offset);
		offset += 2;
		push(buffer, var->getQ_DEVIATOIO(), 2, offset);
		offset += 2;
	}
}

void pacchettoStatoLineaIXL::deserialize(byte *buffer)
{

	NID_PACKET=pop(buffer,  8, 51);
	L_PACKET=pop(buffer, 13, 59);
	sCDB->setNID_CDB(pop(buffer, 32, 72));
	sCDB->setQ_STATOCDB(pop(buffer, 2, 104));
	sCDB->setQ_DEVIATOIO(pop(buffer, 2, 106));
	setN_ITER(pop(buffer, 16, 108));
	int offset = 124;
	for(unsigned int i = 0; i < N_ITER; ++i)
	{
		int NID_CDB=pop(buffer, 32, offset);
		offset += 32;
		int Q_STATOCDB=pop(buffer, 2, offset);
		offset += 2;
		int Q_DEVIATOIO=pop(buffer, 2, offset);
		offset += 2;

		vStatoCDB->Add(gcnew stateCDB(NID_CDB,Q_STATOCDB,Q_DEVIATOIO));
	}
}



System::String^ pacchettoStatoLineaIXL::ToString(){
	String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";

	out = out+sCDB->ToString();
	out = out+"N_ITER: "+N_ITER+";";
	if(vStatoCDB){
		for each (stateCDB^ var in vStatoCDB)
		{
			out = out+var->ToString();
		}
	}
	return out;
}
