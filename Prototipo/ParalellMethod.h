#pragma once
#using <System.dll>
using namespace System;

ref class ParalellMethod
{
	array<Byte> ^A_array;
	array<Byte> ^B_array;
public:

	ParalellMethod(array<Byte> ^A,array<Byte> ^B);
	void ParallelBody(int i);
};

/*	ParalellMethod ^par = gcnew ParalellMethod(end_byte_old,end_byte);
		ParallelLoopResult ^result =	System::Threading::Tasks::Parallel::For(0,end_byte_old->Length, gcnew Action<int>(par,&ParalellMethod::ParallelBody) );
		*/