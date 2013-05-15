#include "pacchettoComandoBlocco.h"
#include "..\\utility.h"

pacchettoComandoBlocco::pacchettoComandoBlocco(void)
{
	data.NID_PACKET = 0;
	data.L_PACKET = 0;
	data.NID_BLOCCO = 0;
	data.Q_CMDBLOCCO = 0;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sar� chiamata da chi vorr� serializzare il messaggio, per poter allocare il buffer
int pacchettoComandoBlocco::getSize()
{
	return 55;
}

void pacchettoComandoBlocco::serialize(byte *buffer)
{
	push(buffer, data.NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	push(buffer, data.L_PACKET, 13, 59);
	push(buffer, data.NID_BLOCCO, 32, 72);
	push(buffer, data.Q_CMDBLOCCO, 2, 104);}

void pacchettoComandoBlocco::deserialize(byte *buffer)
{
	data.NID_PACKET=pop(buffer,  8, 51);
	data.L_PACKET=pop(buffer, 13, 59);
	data.NID_BLOCCO=pop(buffer, 32, 72);
	data.Q_CMDBLOCCO=pop(buffer, 2, 104);
}

pacchettoComandoBlocco::~pacchettoComandoBlocco(void)
{
}