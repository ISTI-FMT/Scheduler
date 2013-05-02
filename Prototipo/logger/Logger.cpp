#include "Logger.h"
#using <System.dll>

using namespace  System::Diagnostics;


Logger::Logger(void)
{
}


 void Logger::WriteEntry(String ^message, String ^type, String ^module)
    {
        Trace::WriteLine(
                String::Format("{0};{1};{2};{3}",
                              DateTime::Now,
                              type,
                              module,
                              message));
    }


