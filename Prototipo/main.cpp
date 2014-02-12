
#using <System.dll>
/*#include "utility.h"
#include "tabellaOrario\\TabellaOrario.h"
#include "phisicalTrainList.h"
#include "threads\\ThreadListenerATC_IXL.h"
#include <iostream>
#include "threads\\ThreadPresentazione.h"
#include "mapTrenoFisicoLogico.h"
#include "messaggi\\Messaggi.h"*/
#include "form\\SchedulerForm.h"
#include "logger\\Logger.h"



using namespace System::Diagnostics;
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;

using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;




int main()
{
	

#ifdef TRACE
			 Logger::Info("main"," New Run Application");  
#endif // TRACE
	Prototipo::SchedulerForm ^form = gcnew Prototipo::SchedulerForm();

	System::Windows::Forms::Application::Run(form);

	return 0;
}