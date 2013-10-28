#include "pacchettoFaultData.h"
#include "utility.h"

pacchettoFaultData::pacchettoFaultData(void)
{
	NID_PACKET = 0;
	L_PACKET = 0;
	
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

void pacchettoFaultData::serialize(array<Byte>^buffer)
{
	utility::push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, 59);
	utility::push(buffer, vGuasto[0]->getNID_COMPONENT(), 4, 72);
	utility::push(buffer, vGuasto[0]->getM_FAULT(), 8, 76);
	utility::push(buffer, N_ITER, 5, 84);
	//mS1_vect = new missionStruct1[N_ITER1];
	int offset = 89;
	for (int i=1;i<vGuasto->Count;i++)
	{
		utility::push(buffer, vGuasto[i]->getNID_COMPONENT(), 4, offset);
		offset += 4;
		utility::push(buffer, vGuasto[i]->getM_FAULT(), 8, offset);
		offset += 8;
	}

}

void pacchettoFaultData::deserialize(array<Byte>^buffer)
{
	NID_PACKET=utility::pop(buffer,  8, 51);
	L_PACKET=utility::pop(buffer, 13, 59);
	int tNID_COMPONENT= utility::pop(buffer, 4, 72);
	int tM_FAULT =utility::pop(buffer, 8, 76);
	vGuasto->Add(gcnew Fault(tNID_COMPONENT,tM_FAULT));
	setN_ITER(utility::pop(buffer, 5, 84));
	int offset = 89;
	for(unsigned int i = 0; i < N_ITER; ++i)
	{
		int NID_COMPONENT=utility::pop(buffer, 4, offset);
		offset += 4;
		int M_FAULT=utility::pop(buffer, 8, offset);
		offset += 8;
		vGuasto->Add(gcnew Fault(NID_COMPONENT,M_FAULT));
	}
}


System::String ^pacchettoFaultData::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+vGuasto[0]->ToString();
	out = out+"N_ITER: "+N_ITER+";";
	
		for (int i=1;i<vGuasto->Count;i++)
		{
			out = out+vGuasto[i]->ToString();
		}

	
	return out;
}