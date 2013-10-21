#include "ParalellMethod.h"
#using <System.dll>



ParalellMethod::ParalellMethod(array<Byte> ^A,array<Byte> ^B)
{
	A_array=A;
	B_array=B;
}

void ParalellMethod::ParallelBody(int i )
{
	String ^A =  A_array[i].ToString();
				String ^B = B_array[i].ToString();
				if(A->Equals(B)){
					return;
				}
}