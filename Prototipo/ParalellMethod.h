#pragma once
#using <System.dll>
using namespace System;

/*test nell'utilizzo di metodi paralleli http://msdn.microsoft.com/it-it/library/system.threading.tasks.parallel(v=vs.110).aspx */
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
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