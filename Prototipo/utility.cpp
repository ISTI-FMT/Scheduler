#include "utility.h"

 char masks[] = {-128,64,32,16,8,4,2,1}; // le maschere per settare i bit

char vet[5]; // il buffer su cui si deve scrivere

//
// dato un offset >=0 (0..*) che rappresenta la posizione di un bit all'interno
// del vettore di caratteri buf, setta a 1 tale bit.
//
void setbit(char buf[], int offset) {
  //
  // estrai il Byte da modifcare
  //
  int Byteoffset = offset/8;
  int bitoffset = offset%8;
  char workByte;
  workByte= buf[Byteoffset];
  //
  // setta il bit;
  //
  workByte = workByte | masks[bitoffset];
  buf[Byteoffset]=workByte;
}

//
// dato un valore data, copia gli len bit meno significativi nel
// vettore buf alle posizioni di bit assolute off..off+len-1
//
void push (char buf[], unsigned int data, int len, int off) {
   //
   // partendo da bit meno significativi di data
   // per n volte, se il bit e'=1 lo propaghi a buf allineandolo a destra
   // nel suo campo off..off+len-1
   //
   unsigned int work=data;
   for (int i=0; i<len; i++) {
     if (work%2==1) {
       setbit(buf, off+len-1-i);
     };
     work=work/2;
   };
}

// converte un char in un intero senza segno 0x80 = 128 non -128!!
unsigned int toint(char C) {
 int res =0;
  if ((C & (1<<7)) != 0) res = res+128;
  if ((C & (1<<6)) != 0) res = res+64;
  if ((C & (1<<5)) != 0) res = res+32;
  if ((C & (1<<4)) != 0) res = res+16;
  if ((C & (1<<3)) != 0) res = res+8;
  if ((C & (1<<2)) != 0) res = res+4;
  if ((C & (1<<1)) != 0) res = res+2;
  if ((C & (1<<0)) != 0) res = res+1;
  return res;
};

/*// funzione che copia gli N elementi di un Byte[] in un array<Byte>
void copiaByteInArray(Byte *source, array<Byte> ^dest, int N)
{
	for(int i = 0; i < N; ++i)
		dest[i] = source[i];
}

// funzione che copia gli N elementi di un array<Byte> in un Byte[]
void copiaArrayInByte(array<System::Byte> ^source, Byte *dest, int N)
{
	for(int i = 0; i < N; ++i)
		dest[i] = source[i];
}
*/
//
// dato un offset >=0 (0..*) che rappresenta la posizione di un bit all'interno
// del vettore di caratteri buf, restituisce il valore numerico del bit.
//
int getbit(char buf[], int offset) {
  //
  // estrai il Byte da leggere
  //
  int res;
  int Byteoffset = offset/8;
  int bitoffset = offset%8;
  char workByte;
  workByte= buf[Byteoffset];
  //
  // leggi il bit;
  //
  res = (workByte & masks[bitoffset]) != 0;
  return res;
}

//
// dato un vettore buf, un indice assoluto di posizione di bit nel vettore,
// ed una lunghezza len, restituisce il valore numerico corrispondente
// ai bits off..off+len-1 del vettore.
//
unsigned int pop (char buf[], int len, int off) {
   //
   // partendo dal bit piu' significativi ricostruisco il valore numerico
   //
   unsigned int work=getbit(buf,off);
   for (int i=1; i<len; i++)
       work = work*2 +getbit(buf,off+i);
   return work;
}