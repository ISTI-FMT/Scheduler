#include "pacchettoStatoItinerario.h"
#include "utility.h"

pacchettoStatoItinerario::pacchettoStatoItinerario(void)
{
	NID_PACKET = 0;
	L_PACKET = 0;
	statoItinerario = gcnew StateItinerario();
	N_ITER = 0;
	vStatoItinerario = gcnew List<StateItinerario^>();
}

// metodo che setta N_ITER ed alloca conseguentemente il vettore vGuasto
void pacchettoStatoItinerario::setN_ITER(int N)
{
	N_ITER = N;

}



// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoStatoItinerario::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;

	// 38 per la parte fissa
	size += 71;
	// 12 bit per ogni N_ITER
	size += 34 * N_ITER;

	return size;
}


void pacchettoStatoItinerario::serialize(byte *buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset + 8);
	utility::push(buffer, statoItinerario->getNID_ITIN(), 32, offset + 21);
	utility::push(buffer, statoItinerario->getQ_STATOITIN(), 2, offset + 53);
	utility::push(buffer, N_ITER, 16, offset + 55);
	//mS1_vect = new missionStruct1[N_ITER1];
	int shift = 71;
	for each (StateItinerario^ var in vStatoItinerario)
	{
		utility::push(buffer, var->getNID_ITIN(), 32, offset + shift);
		shift += 32;
		utility::push(buffer, var->getQ_STATOITIN(), 2, offset + shift);
		shift += 2;
	}
}

void pacchettoStatoItinerario::deserialize(byte *buffer, int offset)
{

	NID_PACKET=utility::pop(buffer,  8, offset);
	L_PACKET=utility::pop(buffer, 13, offset + 8);
	statoItinerario->setNID_ITIN(utility::pop(buffer, 32, offset + 21));
	statoItinerario->setQ_STATOITIN(utility::pop(buffer, 2, offset + 53));
	setN_ITER(utility::pop(buffer, 16, offset + 55));
	int shift = 71;
	for(unsigned int i = 0; i < N_ITER; ++i)
	{
		int NID_ITIN=utility::pop(buffer, 32, offset + shift);
		shift += 32;
		int Q_STATOITIN=utility::pop(buffer, 2, offset + shift);
		shift += 2;
		vStatoItinerario->Add(gcnew StateItinerario(NID_ITIN,Q_STATOITIN));
	}
}




System::String ^pacchettoStatoItinerario::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+statoItinerario->ToString();
	out = out+"N_ITER: "+N_ITER+";";
	if(vStatoItinerario){
		for each (StateItinerario ^var in vStatoItinerario)
		{
			out = out+var->ToString();
		}
	}
	return out;
}