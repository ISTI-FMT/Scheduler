using namespace System;
using namespace System::Net::Sockets;
using namespace System::Collections::Concurrent;

/*Utilizzo questa classe per ricevere ed inviare messaggi TCP asincroni*/
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
ref class StateObject
{
public:
    int BUFFER_SIZE;
   Socket^ workSocket;
   array<Byte>^ buffer;
   int fine;
   int enginenumber;
   StateObject(int e) 
   {
	   workSocket=nullptr ;
	   BUFFER_SIZE=17;
      buffer = gcnew array<Byte>(BUFFER_SIZE);
      fine=0;
	  enginenumber=e;
   };
};