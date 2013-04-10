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
	byte flatCommandData[10];

	struct _structuredCommandData
	{
		structuredHeader head;
		int NID_PACKET : 8;
		int L_PACKET : 13;
		int Q_COMMAND_TYPE : 3;
		int PADDING : 5;
	}structuredCommandData;

}commandData1;

// Messaggio command data quando Q_COMMAND_TYPE == "Chane GOA Level"
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
typedef union _commandData2
{
	byte flatCommandData[10];

	struct _structuredCommandData
	{
		structuredHeader head;
		int NID_PACKET : 8;
		int L_PACKET : 13;
		int Q_COMMAND_TYPE : 3;
		int M_GOA_LEVEL : 2;
		int PADDING : 3;
	}structuredCommandData;

}commandData2;

// Messaggio command data quando Q_COMMAND_TYPE == "Train Running Number"
// L'uso della union permette di accedere ai campi dati in maniera strutturata (per esempio quando si vuole fare una ricezione)
// oppure in maniera flat (per esempio quando si vuole fare una trasmissione)
typedef union _commandData3
{
	byte flatCommandData[14];

	struct _structuredCommandData
	{
		structuredHeader head;
		int NID_PACKET : 8;
		int L_PACKET : 13;
		int Q_COMMAND_TYPE : 3;
		int NID_OPERATIONAL: 32;
		int PADDING : 5;
	}structuredCommandData;

}commandData3;