#pragma once

#include <iostream>
using namespace std;

typedef __int8 byte;

//
// dato un valore data, copia gli len bit meno significativi nel
// vettore buf alle posizioni di bit assolute off..off+len-1
//
void push (char buf[], unsigned int data, int len, int off);

//
// dato un offset >=0 (0..*) che rappresenta la posizione di un bit all'interno
// del vettore di caratteri buf, setta a 1 tale bit.
//
void setbit( char buf[], int offset);

// converte un char in un intero senza segno 0x80 = 128 non -128!!
unsigned int toint(char C);