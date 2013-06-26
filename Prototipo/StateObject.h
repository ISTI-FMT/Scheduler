using namespace System;
using namespace System::Net::Sockets;
using namespace System::Collections::Concurrent;

ref class StateObject
{
public:
    int BUFFER_SIZE;
   Socket^ workSocket;
   array<Byte>^ buffer;
   int fine;
   StateObject() 
   {
	   workSocket=nullptr ;
	   BUFFER_SIZE=17;
      buffer = gcnew array<Byte>(BUFFER_SIZE);
      fine=0;
   };
};