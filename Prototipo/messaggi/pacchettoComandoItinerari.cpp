#include "pacchettoComandoItinerari.h"
#include "..\\utility.h"

pacchettoComandoItinerari::pacchettoComandoItinerari(void)
{
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.NID_ITIN = 0;
	data.Q_CMDITIN = 0;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoComandoItinerari::getSize()
{
	return 55;
}

void pacchettoComandoItinerari::serialize(byte *buffer)
{
	push(buffer, data.NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, 59);
	push(buffer, data.NID_ITIN, 32, 72);
	push(buffer, data.Q_CMDITIN, 2, 104);}

void pacchettoComandoItinerari::deserialize(byte *buffer)
{
	data.NID_PACKET=pop(buffer,  8, 51);
	data.L_PACKET=pop(buffer, 13, 59);
	data.NID_ITIN=pop(buffer, 32, 72);
	data.Q_CMDITIN=pop(buffer, 2, 104);
}

pacchettoComandoItinerari::~pacchettoComandoItinerari(void)
{
}
