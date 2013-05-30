#pragma once
#using <System.dll>
using namespace System;
using namespace System::Diagnostics;

/*********************************************************************************************************
Alessio:
L'ATS mantiene aggiornato un file di log in cui vengono memorizzate tutte le azioni effettuate dal
sistema, ad esempio ricezione/invio di messaggi da ATO o ATC.
**********************************************************************************************************/

ref class Logger
{
public:
	Logger(void);
	static void WriteEntry(String ^message, String ^type, String ^module);

	 static void Info(int NID_MSG,String ^mit, String ^dest,int dim ,String ^ message, String ^ module)
    {
		int id = Process::GetCurrentProcess()->Id;
		String ^result =  String::Format("{0};{1};{2};{3};{4};{5}",id,NID_MSG,dest,mit,message,dim);
        WriteEntry(result, "Info", module);
    }

	  static void Info(String ^ message, String ^ module)
    {
		int id = Process::GetCurrentProcess()->Id;
		String ^result =  String::Format("{0};{1};",id,message);
        WriteEntry(result, "Info", module);
    }

     static void Exception(Exception ^ex, String ^ module)
    {
		int id = Process::GetCurrentProcess()->Id;
		 String ^result =  String::Format("{0};{1}",id,ex->Message);
        WriteEntry(result, "Exception", module);
        
    }

     static void Warning(String ^ message, String ^ module)
    {
		int id = Process::GetCurrentProcess()->Id;
		 String ^result =  String::Format("{0};{1}",id,message);
        WriteEntry(result, "Warning", module);
    }

     static void Error(String ^ message, String ^ module)
    {
        WriteEntry(message, "Error", module);
    }
};

