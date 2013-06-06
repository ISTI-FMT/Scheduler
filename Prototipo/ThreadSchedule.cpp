#include "ThreadSchedule.h"


using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Runtime::InteropServices;


#define TRACE


ThreadSchedule::ThreadSchedule(EventQueue ^E, TabellaOrario ^tabo, tabellaItinerari ^tabi)
{
	EQueue=E;
	tabOrario=tabo;
	tabItinerari=tabi;
}


void ThreadSchedule::SimpleSchedule(){
	try
	{
		Console::WriteLine("Hi!! I'm SimpleSchedule");
		//inizializzazione ATS
		Init();
		while(true){
			// aspetta che si presenti un treno

			// se trovi che un numero logico nella mappa

			// cerchi se c'è una missione per lui nella tabella orario

			// gli assegni TRN e MISSION

			// aspetti che l'orario e se si trova nel posto giusto chiedi a IXL itinerario uscita-

			// se in posizione giusta richiedi itinerario entrata

			// ripeti passo prec prec

		}
	}
	catch ( ThreadAbortException^ abortException ) 
	{
		#ifdef TRACE
		Logger::Exception(abortException,"ThreadSchedule");  
#endif // TRACE
		Console::WriteLine( dynamic_cast<String^>(abortException->ExceptionState) );
	}
}


void ThreadSchedule::Init(){
	Console::WriteLine("Init Schedule session");

}