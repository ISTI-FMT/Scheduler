#include "pachettoStatoScudetti.h"

#include "utility.h"

pachettoStatoScudetti::pachettoStatoScudetti(void)
{

	NID_PACKET = 0;
	L_PACKET = 0;
	statoscudetti = gcnew stateScudetti();
	N_ITER = 0;
	vStatoScudetti = gcnew List<stateScudetti^>();
}

// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
void pachettoStatoScudetti::setN_ITER(int N)
{
	N_ITER = N;

}


// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pachettoStatoScudetti::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;


	size += 72;
	// 12 bit per ogni N_ITER
	size += 34 * N_ITER;

	return size;
}

void pachettoStatoScudetti::serialize(byte *buffer, int offset)
{
	push(buffer, NID_PACKET, 8, offset);
	setL_PACKET(getSize());
	push(buffer, L_PACKET, 13, offset + 8);
	push(buffer, statoscudetti->getNID_SCUD(), 32, offset + 21);
	push(buffer, statoscudetti->getQ_STATOSCUD(), 3, offset + 53);
	push(buffer, N_ITER, 16, offset + 56);
	//mS1_vect = new missionStruct1[N_ITER1];
	int shift = 72;
	for each (stateScudetti^ var in vStatoScudetti)
	{
		push(buffer, var->getNID_SCUD(), 32, offset + shift);
		shift += 32;
		push(buffer, var->getQ_STATOSCUD(),3, offset + shift);
		shift += 3;
	}
}

void pachettoStatoScudetti::deserialize(byte *buffer, int offset)
{

	NID_PACKET=pop(buffer,  8, offset);
	L_PACKET=pop(buffer, 13, offset + 8);
	statoscudetti->setNID_SCUD(pop(buffer, 32, offset + 21));
	statoscudetti->setQ_STATOSCUD(pop(buffer, 3, offset + 53));
	setN_ITER(pop(buffer, 16, offset + 56));
	int shift = 72;
	for(unsigned int i = 0; i < N_ITER; ++i)
	{
		int NID_SCUD=pop(buffer, 32, offset + shift);
		shift += 32;
		int Q_STATOSCUD=pop(buffer, 3, offset + shift);
		shift += 2;
		vStatoScudetti->Add(gcnew stateScudetti(NID_SCUD,Q_STATOSCUD));
	}
}




System::String ^pachettoStatoScudetti::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+statoscudetti->ToString();
	out = out+"N_ITER: "+N_ITER+";";
	if(vStatoScudetti){
		for each (stateScudetti^ var in vStatoScudetti)
		{
			out = out+var->ToString();
		}

	}
	return out;
}


