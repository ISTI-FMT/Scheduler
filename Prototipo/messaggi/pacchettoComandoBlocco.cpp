#include "pacchettoComandoBlocco.h"
#include "utility.h"

pacchettoComandoBlocco::pacchettoComandoBlocco(void)
{
	NID_PACKET = 0;
	L_PACKET = 0;
	NID_BLOCCO = 0;
	Q_CMDBLOCCO = 0;
}

// funzione che restituisce la dimensione (ideale, non quella dovuta agli allineamenti 
// fatti dal compilatore) in Byte del messaggio tenendo anche in conto l'eventuale padding
// questa funzione sarà chiamata da chi vorrà serializzare il messaggio, per poter allocare il buffer
int pacchettoComandoBlocco::getSize()
{
	return 55;
}

void pacchettoComandoBlocco::serialize(byte *buffer)
{
	utility::push(buffer, NID_PACKET, 8, 51);
	setL_PACKET(getSize());
	utility::push(buffer, L_PACKET, 13, 59);
	utility::push(buffer, NID_BLOCCO, 32, 72);
	utility::push(buffer, Q_CMDBLOCCO, 2, 104);}

void pacchettoComandoBlocco::deserialize(byte *buffer)
{
	NID_PACKET=utility::pop(buffer,  8, 51);
	L_PACKET=utility::pop(buffer, 13, 59);
	NID_BLOCCO=utility::pop(buffer, 32, 72);
	Q_CMDBLOCCO=utility::pop(buffer, 2, 104);
}

pacchettoComandoBlocco::~pacchettoComandoBlocco(void)
{
}

System::String ^pacchettoComandoBlocco::ToString(){
	System::String ^out;

	out = out+"NID_PACKET: "+NID_PACKET+";";
	out = out+"L_PACKET: "+L_PACKET+";";
	out = out+"NID_BLOCCO: "+NID_BLOCCO+";";
	out = out+"Q_CMDBLOCCO: "+Q_CMDBLOCCO+";";
	return out;
}