#pragma once

typedef __int8 byte;

// questa struttura codifica i primi tre campi del messaggio generico
struct structuredHeader
{
	int NID_MESSAGE : 8;
	int L_MESSAGE : 11;
	int T_TRAIN : 32;
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
		int NID_PACKET : 8;
		int L_PACKET : 13;
		int Q_COMMAND_TYPE : 3;
		int PADDING : 5;
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
		int NID_PACKET : 8;
		int L_PACKET : 13;
		int Q_COMMAND_TYPE : 3;
		int M_GOA_LEVEL : 2;
		int PADDING : 3;
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
		int NID_PACKET : 8;
		int L_PACKET : 13;
		int Q_COMMAND_TYPE : 3;
		int NID_OPERATIONAL : 32;
		int PADDING : 5;
	}structuredData;

}commandData3;

// Struttura dati contente la coppia di valori D_MISSION, V_MISSION
struct missionStruct1
{
	int D_MISSION : 15;
	int V_MISSION : 7;
};

// Struttura dati contente i valori T_START_TIME, NID_LRGB, D_STOP, Q_DOORS e T_DOORS_TIME
struct missionStruct2
{
	int T_START_TIME : 12;
	int NID_LRGB : 24;
	int D_STOP : 15;
	int Q_DOORS : 4;
	int T_DOORS_TIME : 12;
};

// Messaggio Mission Data
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
typedef union _missionData
{
	// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER.
	// nota che nell'allocare il vettore si terrà conto anche di eventuale padding che dovrà 
	// essere aggiunto affinchè la dimensione del vettore sia multipla del byte
	// su come verrà calcolato il padding vedere in fondo alla struttura dati.
	byte *flatData;

	struct _structuredCommandData
	{
		structuredHeader head;
		int NID__PACKET : 8;
		int L_PACKET : 13;
		int Q_SCALE : 2;
		missionStruct1 mS1;
		int N_ITER1 : 5;
		// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
		missionStruct1 *mS1_vect;
		missionStruct2 mS2;
		int N_ITER2 : 5;
		// questo vettore verrà allocato con la new quando sarà noto il valore di N_ITER
		missionStruct2 *mS2_vect;
		// il padding per questo messaggio è variabile, si conseguenza non può essere specificato in 
		// questa struttura dati. Quello che può essere fatto è: sapendo che la parte fissa del messaggio è lunga 122 bit,
		// e sapendo che ogni "N_ITER" aggiunge 89 bit si può calcolare il numero di bit di padding ed
	}structuredData;

}missionData;