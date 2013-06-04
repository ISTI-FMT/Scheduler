#pragma once





// questa struttura codifica i primi tre campi del messaggio generico
// 51 bit, in memoria però, causa allineamento, occupa 64 bit
/*struct structuredHeader
{
	unsigned int NID_MESSAGE : 8;
	unsigned int L_MESSAGE : 11;
	unsigned int T_TIME : 32;
	unsigned int NID_ENGINE : 24;
};*/



// Struttura dati contente la coppia di valori D_MISSION, V_MISSION
// 22 bit => 3 byte; dell'ultimo byte 2 bit non saranno significativi


// Struttura dati contente i valori T_START_TIME, NID_LRGB, D_STOP, Q_DOORS e T_DOORS_TIME
// 67 bit => 9 byte; dell'ultimo byte 5 bit non saranno significativi


// Struttura dati il "sotto-header" del messaggio Mission Plan
// 23 bit => 3 byte; dell'ultimo byte 1 bit non saranno significativi


// Messaggio Mission Data


// struttura dati per la gestione del mission ack
// 54 bit


















