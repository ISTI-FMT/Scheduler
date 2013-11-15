#include "ThreadSchedule.h"
#include "TrenoFisicoLogico.h"
#include "messaggi\\pacchettoCommandData.h"

using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Runtime::InteropServices;
using namespace System::Globalization;
using namespace System::Xml;


#define TRACE



ThreadSchedule::ThreadSchedule(List<EventQueue^> ^E, TabellaOrario ^tabo, tabellaItinerari ^tabi,mapTrenoFisicoLogico ^mapTreno, wdogcontrol ^w,ManagerStatoLineaATC ^manATC,ManagerStatoLineaIXL ^manIXL, ConfigurazioneVelocita ^cvel)
{
	if(E->Count>2){
		EQueueIXL=E[0];
		EQueueATC=E[1];
		EQueueATO=E[2];
	}
	mapTrenoLogFisico=mapTreno;
	tabOrario=tabo;
	tabItinerari=tabi;
	confVelocita=cvel;
	wdogs=w;
	managerATC=manATC;
	managerIXL=manIXL;
	ipixl="127.0.0.1";
	listIdCdbItinRic = gcnew List<int>();
	_shouldStop=false;
	listThreadTrain = gcnew List<ThreadSchedulerTrain^>();
}


void ThreadSchedule::SimpleSchedule(){
	try
	{
		Console::WriteLine("Hi!! I'm SimpleSchedule");
		//inizializzazione ATS
		Init();
		int statoInterno = StateSimpleSchedule::PresentazioneTreno;
		int indicelistaitinerari=0;
	
		DateTime time=DateTime::Now;
	
		int trn =0;
		while(!_shouldStop){
			//dormi un po 100  millisecondi cosi da eseguire un ciclo ogni 100 ms
			Thread::Sleep(100);
			//wdogs->onNext();
		
			Event ^eventoATO;



		/*	TimeSpan sec = DateTime::Now - time;
			if(sec.TotalSeconds>20){
				Console::ForegroundColor = ConsoleColor::DarkGreen;
				Console::WriteLine("lo stato interno dello scheduler 1 è PresentazioneTreno");


				time=DateTime::Now;
			}
			*/


			switch (statoInterno)
			{
			case StateSimpleSchedule::PresentazioneTreno:
				{

					// aspetta che si presenti un treno
					eventoATO = EQueueATO->getEvent();
					if(eventoATO!=nullptr){
						
						physicalTrain ^phisical = eventoATO->getEventPresentTrain();
						int enginenumber = phisical->getEngineNumber();
						Console::WriteLine("Si è presentato il treno {0}",enginenumber);
						//statoInterno=StateSimpleSchedule::ControlloTreno;
						List<EventQueue^> ^EList = gcnew List<EventQueue^>();
						EList->Add(EQueueIXL);
						EList->Add(EQueueATC);
						ThreadSchedulerTrain ^ThreadP = gcnew ThreadSchedulerTrain(phisical,EList,tabOrario,tabItinerari,mapTrenoLogFisico,wdogs,	managerATC,managerIXL,confVelocita);
						//Thread TCP che ascolta i messaggi provenienti dall'ATO
						/*Thread ^oThread = gcnew Thread( gcnew ThreadStart( ThreadP, &ThreadSchedulerTrain::SimpleSchedule ) );

						oThread->Start();
						listThreadTrain->Add(ThreadP);*/
					}
					break;
				}
		
			default:
				break;
			}

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


void ThreadSchedule::RequestStop()
    {
        _shouldStop = true;
		/*for each (ThreadSchedulerTrain ^var in listThreadTrain)
		{
			var->RequestStop();
		}*/
    }



void ThreadSchedule::Init(){
	Console::WriteLine("Inizio Inizializzazione dello Scheduler");
	//TODO: in questa fase ad es. controllare che lo stato di tutti i cdb proveniente dall'IXL sia consistente
	Console::WriteLine("Fine Inizializzazione dello Scheduler");
}



bool ThreadSchedule::controllacdb(List<int>^lcdb){
	bool res=true;
	for each (int cdb in lcdb)
	{
		StateCDB ^statocorrentecdb = managerIXL->StatoCDB(cdb);
		if(statocorrentecdb!=nullptr){
			if(statocorrentecdb->getQ_STATOCDB()!=typeStateCDB::cdbLibero){
				return false;
			}
		}else{
			return false;
		}
	}
	return res;
}