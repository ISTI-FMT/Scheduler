#include <iostream>
#include "String2string.h"
using namespace std;
#include <msclr\marshal_cppstd.h>

string String2string(System::String ^source)
{
	std::string value = msclr::interop::marshal_as< std::string >(source);
	return value;
}