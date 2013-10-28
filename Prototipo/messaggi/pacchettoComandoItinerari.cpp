#include "pacchettoComandoItinerari.h"
#include "utility.h"

pacchettoComandoItinerari::pacchettoComandoItinerari(void)
{
	NID_PACKET = 0;
	L_PACKET = 0;
	NID_ITIN = 0;
	Q_CMDITIN = 0;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoComandoItinerari::getSize()
{
	return 55;
}

void pacchettoComandoItinerari::serialize(array<Byte>^buffer)
{
	utility::push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, 59);
	utility::push(buffer, NID_ITIN, 32, 72);
	utility::push(buffer, Q_CMDITIN, 2, 104);}

void pacchettoComandoItinerari::deserialize(array<Byte>^buffer)
{
	NID_PACKET=utility::pop(buffer,  8, 51);
	L_PACKET=utility::pop(buffer, 13, 59);
	NID_ITIN=utility::pop(buffer, 32, 72);
	Q_CMDITIN=utility::pop(buffer, 2, 104);
}

pacchettoComandoItinerari::~pacchettoComandoItinerari(void)
{
}

System::String ^pacchettoComandoItinerari::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+"NID_ITIN: "+NID_ITIN+";";
	out = out+"Q_CMDITIN: "+Q_CMDITIN+";";
	return out;
}