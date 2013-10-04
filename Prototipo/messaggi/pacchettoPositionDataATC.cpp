#include "pacchettoPositionDataATC.h"
#include "utility.h"

pacchettoPositionDataATC::pacchettoPositionDataATC(void)
{


	NID_PACKET = 0;
	L_PACKET = 0;
	N_ITER=0;
	ListPostionData = gcnew List<StateCDB^>();
}


int pacchettoPositionDataATC::getSize()
{
	// intero che rappresenta la dimensione in bit
	int size = 0;

	// 94 per la parte fissa del pacchetto 
	size += 133;
	// 36 bit per ogni N_ITER
	if(  N_ITER>0  ){
		size += 96* N_ITER;
	}
	// ritorno il numero di byte occupato dalla struttura dati
	return size;
}

System::String^ pacchettoPositionDataATC::toPrint(){
	String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";

	if(ListPostionData->Count>0)
		out = out+ListPostionData[0]->ToString();
	out = out+"N_ITER: "+N_ITER+";";

	for( int i=1;i<ListPostionData->Count;i++)
	{
		out = out+ListPostionData[i]->ToString();

	}

	return out;
}

// funzione che setta N_ITER
void pacchettoPositionDataATC::setN_ITER(int N)
{
	N_ITER = N;

}



void pacchettoPositionDataATC::serialize(array<Byte>^buffer)
{

	utility::push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, 59);

	if(ListPostionData->Count>0){
		utility::push(buffer, ListPostionData[0]->getNID_OPERATIONAL(), 32, 72);
		utility::push(buffer,  ListPostionData[0]->getNID_ENGINE(), 32, 104);
		utility::push(buffer,  ListPostionData[0]->getNID_CDB(), 32, 136);
	}

	utility::push(buffer, N_ITER, 16, 168);

	int offset = 184;
	for( int i=1;i<ListPostionData->Count;i++)
	{

		utility::push(buffer, ListPostionData[i]->getNID_OPERATIONAL(), 32, offset);
		offset+=32;
		utility::push(buffer,  ListPostionData[i]->getNID_ENGINE(), 32, offset);
		offset+=32;
		utility::push(buffer,  ListPostionData[i]->getNID_CDB(), 32, offset);
		offset += 32;

	}

}

void pacchettoPositionDataATC::deserialize(array<Byte>^buffer)
{

	NID_PACKET=utility::pop(buffer,  8, 51);
	L_PACKET=utility::pop(buffer, 13, 59);
	if(NID_PACKET!=255){

		int tNID_OPERATIONAL =utility::pop(buffer, 32, 72);
		int tNID_ENGINE =utility::pop(buffer, 32, 104);
		int tNID_CDB =utility::pop(buffer, 32, 136);

		ListPostionData->Add(gcnew StateCDB(tNID_CDB,typeStateCDB::cdbOccupato,typeStateDeviatoio::deviatoioStatoIgnoto,tNID_OPERATIONAL,tNID_ENGINE));
		setN_ITER(utility::pop(buffer, 16, 168));
		int offset = 184;

		for(unsigned int i = 0; i < N_ITER; ++i)
		{
			tNID_OPERATIONAL=utility::pop(buffer, 32, offset);
			offset += 32;
			tNID_ENGINE=utility::pop(buffer, 32, offset);
			offset += 32;
			tNID_CDB=utility::pop(buffer, 32, offset);
			offset += 32;

			ListPostionData->Add(gcnew  StateCDB(tNID_CDB,typeStateCDB::cdbOccupato,typeStateDeviatoio::deviatoioStatoIgnoto,tNID_OPERATIONAL,tNID_ENGINE));
		}
	}

}