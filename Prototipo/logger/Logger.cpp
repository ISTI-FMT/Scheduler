#include "Logger.h"
#using <System.dll>

using namespace  System::Diagnostics;


Logger::Logger(void)
{
}


void Logger::WriteEntry(String ^message, String ^type, String ^module)
{
	String ^result = gcnew String("");
	String ^mess = String::Format("{0};{1};{2};{3}",
		DateTime::Now,
		type,
		module,
		message);
	int count = message->Split('#')->Length - 1;
	if(count==0){

		array<String^> ^arraystr=mess->Split(';');
		if(arraystr->Length>=7){
			//String ^result = String::Format("{0} Module:{1} NID_MSG:{2} Message:{3} {4} Send in/out:{5} Size:{6}",arraystr[0],arraystr[2],
			//	arraystr[4],arraystr[7],arraystr[6],arraystr[5],arraystr[8]);
			result = String::Format("{4} {0} Module:{1} NID_MSG:{2} Message:{3}\r\n",arraystr[0],arraystr[2],
				arraystr[4],arraystr[7],arraystr[6],arraystr[5],arraystr[8]);

		}else{
			result= mess;
		}
	}else{
		result= mess;
	}
	Trace::WriteLine(result);
}


