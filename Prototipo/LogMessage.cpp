#include "LogMessage.h"


LogMessage::LogMessage(void)
{
	 NID_MSG=0;
	time = gcnew DateTime();
	msg = gcnew String("");
	mit = gcnew String("");
	dest = gcnew String("");
}
