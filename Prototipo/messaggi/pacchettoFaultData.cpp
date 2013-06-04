#include "pacchettoFaultData.h"
#include "utility.h"

pacchettoFaultData::pacchettoFaultData(void)
{
	NID_PACKET = 0;
	L_PACKET = 0;
	guasto = gcnew Fault();
	N_ITER = 0;
	vGuasto = gcnew List<Fault^>();
}

// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
void pacchettoFaultData::setN_ITER(int N)
{
	N_ITER = N;

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
	size += 12 * N_ITER;

	return size;
}

void pacchettoFaultData::serialize(byte *buffer)
{
	push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, L_PACKET, 13, 59);
	push(buffer, guasto->getNID_COMPONENT(), 4, 72);
	push(buffer, guasto->getM_FAULT(), 8, 76);
	push(buffer, N_ITER, 5, 84);
	//mS1_vect = new missionStruct1[N_ITER1];
	int offset = 89;
	for each (Fault ^var in vGuasto)
	{
		push(buffer, var->getNID_COMPONENT(), 4, offset);
		offset += 4;
		push(buffer, var->getM_FAULT(), 8, offset);
		offset += 8;
	}

}

void pacchettoFaultData::deserialize(byte *buffer)
{
	NID_PACKET=pop(buffer,  8, 51);
	L_PACKET=pop(buffer, 13, 59);
	guasto->setNID_COMPONENT(pop(buffer, 4, 72));
	guasto->setM_FAULT(pop(buffer, 8, 76));
	setN_ITER(pop(buffer, 5, 84));
	int offset = 89;
	for(unsigned int i = 0; i < N_ITER; ++i)
	{
		int NID_COMPONENT=pop(buffer, 4, offset);
		offset += 4;
		int M_FAULT=pop(buffer, 8, offset);
		offset += 8;
		vGuasto->Add(gcnew Fault(NID_COMPONENT,M_FAULT));
	}
}


System::String ^pacchettoFaultData::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+guasto->ToString();
	out = out+"N_ITER: "+N_ITER+";";
	if(vGuasto){
		for each (Fault^ var in vGuasto)
		{
			out = out+var->ToString();
		}

	}
	return out;
}