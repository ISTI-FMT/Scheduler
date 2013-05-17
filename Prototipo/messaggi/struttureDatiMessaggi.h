#pragma once

const int WAKE_UP = 0;
const int CHANGE_GOA_LEVEL = 3;
const int TRN = 4;
const int SLEEP = 7;

typedef __int8 byte;

// questa struttura codifica i primi tre campi del messaggio generico
// 51 bit, in memoria però, causa allineamento, occupa 64 bit
struct structuredHeader
{
	unsigned int NID_MESSAGE : 8;
	unsigned int L_MESSAGE : 11;
	unsigned int T_TIME : 32;
	unsigned int NID_ENGINE : 24;
};

struct commandData
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int Q_COMMAND_TYPE : 3;
	unsigned int M_GOA_LEVEL : 2;
	unsigned int NID_OPERATIONAL : 32;
	unsigned int PADDING : 5;
};

// Struttura dati contente la coppia di valori D_MISSION, V_MISSION
// 22 bit => 3 byte; dell'ultimo byte 2 bit non saranno significativi
struct missionStruct1
{
	unsigned int D_MISSION : 15;
	unsigned int V_MISSION : 7;
};

// Struttura dati contente i valori T_START_TIME, NID_LRGB, D_STOP, Q_DOORS e T_DOORS_TIME
// 67 bit => 9 byte; dell'ultimo byte 5 bit non saranno significativi
struct missionStruct2
{
	unsigned int T_START_TIME : 12;
	unsigned int NID_LRGB : 24;
	unsigned int D_STOP : 15;
	unsigned int Q_DOORS : 4;
	unsigned int T_DOORS_TIME : 12;
};

// Struttura dati il "sotto-header" del messaggio Mission Plan
// 23 bit => 3 byte; dell'ultimo byte 1 bit non saranno significativi
struct missionHeader
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int Q_SCALE : 2;
};

// Messaggio Mission Data
struct missionData
{
	
	missionHeader missionHead;
	missionStruct1 mS1;
	unsigned int N_ITER1 : 5;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	missionStruct1 *mS1_vect;
	missionStruct2 mS2;
	unsigned int N_ITER2 : 5;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	struct missionStruct2 *mS2_vect;
	// il padding per questo messaggio è variabile, si conseguenza non può essere specificato in 
	// questa struttura dati. Quello che può essere fatto è: sapendo che la parte fissa del messaggio è lunga 122 bit,
	// e sapendo che ogni "N_ITER" aggiunge 89 bit si può calcolare il numero di bit di padding ed
};

// struttura dati per la gestione del mission ack
// 54 bit
struct missionAck 
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int T_TRAIN : 32;
	unsigned int Q_MISSION_RESPONSE : 1;
	unsigned int padding : 7;
};

struct pstatolineastruct{

unsigned int NID_CDB : 32;
	unsigned int Q_STATOCDB : 2;
	unsigned int Q_DEVIATIOIO : 2;

};

struct presentation
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int M_PORT : 32;
	//unsigned int padding : 8;
};

struct pkgstatolinea{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int NID_OPERATIONAL : 32;
	struct pstatolineastruct pstato;
	unsigned int N_ITER : 5;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	struct pstatolineastruct *pstato1;
};

struct statoCDB
{
	unsigned int NID_CDB : 32;
	unsigned int Q_STATOCDB : 2;
	unsigned int Q_DEVIATOIO : 2;
};

struct StatoLinea
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	statoCDB stato;
	unsigned int N_ITER : 16;
	statoCDB *vStato;
};

struct fault
{
	unsigned int NID_COMPONENT : 4;
	unsigned int M_FAULT : 8;
};

struct FaultData
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	fault guasto;
	unsigned int N_ITER : 16;
	fault *vGuasto;
};

struct itinerario
{
	unsigned int NID_ITIN : 32;
	unsigned int Q_STATOITIN : 2;
};

struct StatoItinerario
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	itinerario statoItinerario;
	unsigned int N_ITER : 16;
	itinerario *vStatoItinerario;
};

struct segnale
{
	unsigned int NID_SEGN : 32;
	unsigned int Q_STATOSEGN : 5;
};

struct StatoSegnale
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	segnale statoSegnale;
	unsigned int N_ITER : 16;
	segnale *vStatoSegnale;
};

struct End
{
	unsigned int NID_PACKET : 8;
};

struct ComandoItinerario
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int NID_ITIN : 32;
	unsigned int Q_CMDITIN : 2;
};

struct ComandoBlocco
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int NID_BLOCCO : 32;
	unsigned int Q_CMDBLOCCO : 2;
};

struct blocco
{
	unsigned int NID_BLOCCO : 32;
	unsigned int Q_STATOBLOCCO : 2;
};

struct StatoBlocco
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	blocco statoBlocco;
	unsigned int N_ITER : 16;
	blocco *vStatoBlocco;
};

struct CDB
{
	unsigned int NID_CDB : 32;
	unsigned int Q_STATOCDB : 2;
	unsigned int Q_DEVIATOIO : 2;
};

struct StatoLineaIXL
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	CDB statoCDB;
	unsigned int N_ITER : 16;
	CDB *vStatoCDB;
};