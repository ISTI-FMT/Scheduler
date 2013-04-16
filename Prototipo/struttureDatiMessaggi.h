#pragma once

typedef __int8 byte;

// questa struttura codifica i primi tre campi del messaggio generico
// 51 bit, in memoria per�, causa allineamento, occupa 64 bit
struct structuredHeader
{
	unsigned int NID_MESSAGE : 8;
	unsigned int L_MESSAGE : 11;
	unsigned int T_TRAIN : 32;
};

// Messaggio command data quando Q_COMMAND_TYPE != "Chane GOA Level" e Q_COMMAND_TYPE != "Train Running Number"
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
struct commandData1
{
	structuredHeader head;
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int Q_COMMAND_TYPE : 3;
	unsigned int PADDING : 5;
};

// Messaggio command data quando Q_COMMAND_TYPE == "Chane GOA Level"
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
struct commandData2
{
	structuredHeader head;
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int Q_COMMAND_TYPE : 3;
	unsigned int M_GOA_LEVEL : 2;
	unsigned int PADDING : 3;
};

// Messaggio command data quando Q_COMMAND_TYPE == "Train Running Number"
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
struct commandData3
{
	structuredHeader head;
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int Q_COMMAND_TYPE : 3;
	unsigned int NID_OPERATIONAL : 32;
	unsigned int PADDING : 5;
};

// Struttura dati contente la coppia di valori D_MISSION, V_MISSION
// 22 bit => 3 byte; dell'ultimo byte 2 bit non saranno significativi
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
struct missionStruct1
{
	unsigned int D_MISSION : 15;
	unsigned int V_MISSION : 7;
};

// Struttura dati contente i valori T_START_TIME, NID_LRGB, D_STOP, Q_DOORS e T_DOORS_TIME
// 67 bit => 9 byte; dell'ultimo byte 5 bit non saranno significativi
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
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
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
struct missionHeader
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int Q_SCALE : 2;
};

// Messaggio Mission Data
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
struct missionData
{
	structuredHeader head;
	missionHeader missionHead;
	missionStruct1 mS1;
	unsigned int N_ITER1 : 5;
	// questo vettore verr� allocato con la new quando sar� noto il valore di N_ITER
	missionStruct1 *mS1_vect;
	missionStruct2 mS2;
	unsigned int N_ITER2 : 5;
	// questo vettore verr� allocato con la new quando sar� noto il valore di N_ITER
	struct missionStruct2 *mS2_vect;
	// il padding per questo messaggio � variabile, si conseguenza non pu� essere specificato in 
	// questa struttura dati. Quello che pu� essere fatto �: sapendo che la parte fissa del messaggio � lunga 122 bit,
	// e sapendo che ogni "N_ITER" aggiunge 89 bit si pu� calcolare il numero di bit di padding ed
};

// struttura dati per la gestione del mission ack
// 54 bit
struct missionAck 
{
	unsigned int NID_PACKET : 8;
	unsigned int L_PACKET : 13;
	unsigned int T_TRAIN : 32;
	unsigned int Q_MISSION_RESPONSE : 1;
};

// Struttura dati per la gestione dell'acknowledgement
// 129 bit => 17 byte (7 bit di padding)
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
struct acknowledgement
{
	struct structuredHeader head;
	unsigned int NID_ENGINE : 24;
	struct missionAck ack;
	unsigned int padding : 7;
};