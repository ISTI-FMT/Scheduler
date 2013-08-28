#pragma once
#using <System.dll>
using namespace System;

/*Utilizzo i metodi statici di questa classe per eseguire la serializazzione e la deserializzazione
dei messaggi*/

//typedef __int8 byte;

//questa classe contiene dei metodi usati per la serializazzione e deserializzazione
//dei messaggi

ref class utility{

public:
//
// dato un valore data, copia gli len bit meno significativi nel
// vettore buf alle posizioni di bit assolute off..off+len-1
//
static void push (array<Byte>^buf, unsigned int data, int len, int off);

//
// dato un offset >=0 (0..*) che rappresenta la posizione di un bit all'interno
// del vettore di caratteri buf, setta a 1 tale bit.
//
static void setbit(array<Byte>^buf, int offset);


//
// dato un offset >=0 (0..*) che rappresenta la posizione di un bit all'interno
// del vettore di caratteri buf, restituisce il valore numerico del bit.
//
static int getbit(array<Byte>^buf, int offset);

//
// dato un vettore buf, un indice assoluto di posizione di bit nel vettore,
// ed una lunghezza len, restituisce il valore numerico corrispondente
// ai bits off..off+len-1 del vettore.
//
static unsigned int pop (array<Byte>^buf, int len, int off);

};