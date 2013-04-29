#include "LogClass.h"


LogClass::LogClass(void)
{
	logmsg = gcnew ConcurrentQueue<LogMessage^>();
}

