#pragma once
#include "LogMessage.h"

using namespace System::Collections::Generic;
using namespace System::Collections::Concurrent;

ref class LogClass
{
	 ConcurrentQueue<LogMessage^> ^logmsg;
public:
	LogClass(void);

	void setLogMsg(LogMessage^ lmsg){
		logmsg->Enqueue(lmsg);
	}

	void setLogMsg(int n, DateTime ^d, String ^ms, String ^mi, String ^de){
		LogMessage^ lmsg = gcnew LogMessage(n,d,ms,mi,de);
		logmsg->Enqueue(lmsg);
	}

	
void savetxt(){
	 String^ path = System::IO::Directory::GetCurrentDirectory();
	 System::IO::StreamWriter ^file = gcnew System::IO::StreamWriter("LogMesssageScheduler.txt", true);
	 for each (LogMessage ^var in logmsg)
	 {
			file->WriteLine(var->ToPrint());
	 }
     file->Close();        
}
void savecsv(){
	 String^ path = System::IO::Directory::GetCurrentDirectory();
	 System::IO::StreamWriter ^file = gcnew System::IO::StreamWriter("LogMesssageScheduler.txt", true);
	 for each (LogMessage ^var in logmsg)
	 {
			file->WriteLine(var->ToString());
	 }
     file->Close();        
}
};

