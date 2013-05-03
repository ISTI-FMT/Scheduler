#include "SchedulerForm.h"
#include "tabellaOrario\\TabellaOrario.h"
#using <System.dll>
#include "utility.h"

#include "phisicalTrainList.h"
#include "String2string.h"
#include "threads\\ThreadListenerATC.h"
#include <iostream>
#include "threads\\ThreadPresentazione.h"
#include "mapTrenoFisicoLogico.h"
#include "messaggi\\Messaggi.h"
#include "logger\\LogClass.h"

using namespace std;
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;



using namespace System::Diagnostics;

#define TRACE
/*int main()
{
	
	
  
	Trace::WriteLine("Hello world");
	Prototipo::SchedulerForm ^aform = gcnew Prototipo::SchedulerForm();

	//aform->ShowDialog();
	System::Windows::Forms::Application::Run(aform);



	


	 
	
}*/

