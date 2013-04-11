#pragma once

typedef __int8 byte;

// questa struttura codifica i primi tre campi del messaggio generico
struct structuredHeader
{
	unsigned int NID_MESSAGE : 8;
	unsigned int L_MESSAGE : 11;
	unsigned int T_TRAIN : 32;
};

// Messaggio command data quando Q_COMMAND_TYPE != "Chane GOA Level" e Q_COMMAND_TYPE != "Train Running Number"
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
typedef union _commandData1
{
	byte flatData[10];

	struct _structuredCommandData
	{
		structuredHeader head;
		unsigned int NID_PACKET : 8;
		unsigned int L_PACKET : 13;
		unsigned int Q_COMMAND_TYPE : 3;
		unsigned int PADDING : 5;
	}structuredData;

}commandData1;

// Messaggio command data quando Q_COMMAND_TYPE == "Chane GOA Level"
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
typedef union _commandData2
{
	byte flatData[10];

	struct _structuredCommandData
	{
		structuredHeader head;
		unsigned int NID_PACKET : 8;
		unsigned int L_PACKET : 13;
		unsigned int Q_COMMAND_TYPE : 3;
		unsigned int M_GOA_LEVEL : 2;
		unsigned int PADDING : 3;
	}structuredData;

}commandData2;

// Messaggio command data quando Q_COMMAND_TYPE == "Train Running Number"
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
typedef union _commandData3
{
	byte flatData[14];

	struct _structuredCommandData
	{
		structuredHeader head;
		unsigned int NID_PACKET : 8;
		unsigned int L_PACKET : 13;
		unsigned int Q_COMMAND_TYPE : 3;
		unsigned int NID_OPERATIONAL : 32;
		unsigned int PADDING : 5;
	}structuredData;

}commandData3;

// Struttura dati contente la coppia di valori D_MISSION, V_MISSION
// 22 bit => 3 byte; dell'ultimo byte 2 bit non saranno significativi
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
typedef union _missionStruct1
{
	byte flatData[3];

	struct _structuredData
	{
		unsigned int D_MISSION : 15;
		unsigned int V_MISSION : 7;
	}structuredData;

}missionStruct1;

// Struttura dati contente i valori T_START_TIME, NID_LRGB, D_STOP, Q_DOORS e T_DOORS_TIME
// 67 bit => 9 byte; dell'ultimo byte 5 bit non saranno significativi
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
typedef union _missionStruct2
{
	byte flatData[9];

	struct _structuredData
	{
		unsigned int T_START_TIME : 12;
		unsigned int NID_LRGB : 24;
		unsigned int D_STOP : 15;
		unsigned int Q_DOORS : 4;
		unsigned int T_DOORS_TIME : 12;
	}structuredData;

}missionStruct2;

// Struttura dati il "sotto-header" del messaggio Mission Plan
// 23 bit => 3 byte; dell'ultimo byte 1 bit non saranno significativi
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
typedef union _missionHeader
{
	byte flatData[3];

	struct _structuredData
	{
		unsigned int NID_PACKET : 8;
		unsigned int L_PACKET : 13;
		unsigned int Q_SCALE : 2;
	}structuredData;

}missionHeader;

// Messaggio Mission Data
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
struct missionData
{
	structuredHeader head;
	missionHeader missionHead;
	missionStruct1 mS1;
	unsigned int N_ITER1 : 5;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	missionStruct1 *mS1_vect;
	missionStruct2 mS2;
	unsigned int N_ITER2 : 5;
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
	missionStruct2 *mS2_vect;
	// il padding per questo messaggio è variabile, si conseguenza non può essere specificato in 
	// questa struttura dati. Quello che può essere fatto è: sapendo che la parte fissa del messaggio è lunga 122 bit,
	// e sapendo che ogni "N_ITER" aggiunge 89 bit si può calcolare il numero di bit di padding ed
};