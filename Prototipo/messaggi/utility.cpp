#include "utility.h"



//
// dato un offset >=0 (0..*) che rappresenta la posizione di un bit all'interno
// del vettore di caratteri buf, setta a 1 tale bit.
//
void utility::setbit(array<Byte>^buf, int offset) {
  //
  // estrai il Byte da modifcare
  //
  int Byteoffset = offset/8;
  int bitoffset = offset%8;
  Byte workByte;
  workByte= buf[Byteoffset];
   array<Byte> ^masks = {-128,64,32,16,8,4,2,1}; // le maschere per settare i bit
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
void utility::push (array<Byte>^buf, unsigned int data, int len, int off) {
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

//
// dato un offset >=0 (0..*) che rappresenta la posizione di un bit all'interno
// del vettore di caratteri buf, restituisce il valore numerico del bit.
//
int utility::getbit(array<Byte>^buf, int offset) {
  //
  // estrai il Byte da leggere
  //
  int res;
  int Byteoffset = offset/8;
  int bitoffset = offset%8;
  Byte workByte;
  workByte= buf[Byteoffset];
   array<Byte> ^ masks = {-128,64,32,16,8,4,2,1}; // le maschere per settare i bit
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
unsigned int utility::pop (array<Byte>^buf, int len, int off) {
   //
   // partendo dal bit piu' significativi ricostruisco il valore numerico
   //
   unsigned int work=getbit(buf,off);
   for (int i=1; i<len; i++)
       work = work*2 +getbit(buf,off+i);
   return work;
}