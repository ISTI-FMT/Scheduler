#include "pacchettoPositionDataATC.h"
#include "utility.h"

pacchettoPositionDataATC::pacchettoPositionDataATC(void)
{
	setNID_PACKET(PacchettoID::PositionDataATC);
	setL_PACKET( 0);
	setN_ITER(0);
	setCDB( gcnew List<StateCDB^>());
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

	out = out+"NID_PACKET: "+get_NID_PACKET()+";";
	out = out+"L_PACKET: "+getL_PACKET()+";";

	if(getListCDB()->Count>0)
		out = out+getListCDB()[0]->ToString();
	out = out+"N_ITER: "+getN_ITER()+";";

	for( int i=1;i<getListCDB()->Count;i++)
	{
		out = out+getListCDB()[i]->ToString();

	}

	return out;
}

void pacchettoPositionDataATC::setN_ITER(int N)
{
	N_ITER = N;

}

void pacchettoPositionDataATC::serialize(array<Byte>^buffer, int offset)
{
	utility::push(buffer, NID_PACKET, 8, offset);
	offset += 8;
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, offset);
	offset += 13;

	if(ListPostionData->Count>0){

		utility::push(buffer,  ListPostionData[0]->getNID_ENGINE(), 32, offset);
		offset += 32;
		utility::push(buffer, ListPostionData[0]->getNID_OPERATIONAL(), 32, offset);
		offset += 32;
		utility::push(buffer,  ListPostionData[0]->getNID_CDB(), 32, offset);
		offset += 32;
	}

	offset = 168;
	utility::push(buffer, N_ITER, 16, offset);
	offset += 16;

	for( int i=1;i<ListPostionData->Count;i++)
	{
		utility::push(buffer, ListPostionData[i]->getNID_ENGINE(), 32, offset);
		offset+=32;
		utility::push(buffer,  ListPostionData[i]->getNID_OPERATIONAL(), 32, offset);
		offset+=32;
		utility::push(buffer,  ListPostionData[i]->getNID_CDB(), 32, offset);
		offset += 32;
	}
}

void pacchettoPositionDataATC::deserialize(array<Byte>^buffer, int offset)
{

	NID_PACKET=utility::pop(buffer,  8, 51);
	if(NID_PACKET!=255){
		L_PACKET=utility::pop(buffer, 13, 59);


		int tNID_ENGINE =utility::pop(buffer, 32, 72);
		int tNID_OPERATIONAL  =utility::pop(buffer, 32, 104);
		int tNID_CDB =utility::pop(buffer, 32, 136);

		setCDB(gcnew StateCDB(tNID_CDB,QStateCDB::cdbOccupato,QStateDeviatoio::deviatoioStatoIgnoto,tNID_OPERATIONAL,tNID_ENGINE));
		setN_ITER(utility::pop(buffer, 16, 168));
		int offset = 184;

		for(int i = 0; i < N_ITER; ++i)
		{
			tNID_ENGINE=utility::pop(buffer, 32, offset);
			offset += 32;
			tNID_OPERATIONAL =utility::pop(buffer, 32, offset);
			offset += 32;
			tNID_CDB=utility::pop(buffer, 32, offset);
			offset += 32;

			setCDB(gcnew  StateCDB(tNID_CDB,QStateCDB::cdbOccupato,QStateDeviatoio::deviatoioStatoIgnoto,tNID_OPERATIONAL,tNID_ENGINE));
		}
	}

}