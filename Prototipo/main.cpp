
#using <System.dll>
/*#include "utility.h"
#include "tabellaOrario\\TabellaOrario.h"
#include "phisicalTrainList.h"
#include "threads\\ThreadListenerUdp.h"
#include <iostream>
#include "threads\\ThreadListenerTcp.h"
#include "mapTrenoFisicoLogico.h"
#include "messaggi\\Messaggi.h"*/
#include "SchedulerForm.h"
#include "logger\\Logger.h"



using namespace System::Diagnostics;
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;

using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;


using namespace System::Diagnostics::CodeAnalysis;


[STAThread,ExcludeFromCodeCoverage]
int main()
{
	try{
	 Console::SetWindowPosition( 0, 0 );
#ifdef TRACE
			 Logger::Info("main"," New Run Application");  
#endif // TRACE
	Prototipo::SchedulerForm ^form = gcnew Prototipo::SchedulerForm();

	System::Windows::Forms::Application::Run(form);
	}catch(System::Exception  ^e){

		Console::WriteLine(e->Message);
	}
	return 0;
}