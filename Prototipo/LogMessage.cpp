#include "LogMessage.h"


LogMessage::LogMessage(void)
{
	 NID_MSG=0;
	time = gcnew DateTime();
	msg = gcnew String("");
	mit = gcnew String("");
	dest = gcnew String("");
}

LogMessage::LogMessage(int n, DateTime ^d, String ^ms, String ^mi, String ^de){
	 NID_MSG=n;
	time = d;
	msg = ms;
	mit =mi;
	dest = de;

}


