#pragma once
#include "TrenoFisicoLogico.h"
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

/*Utilizzo questa classe per leggere i dati di configurazione del file xml MapTreni.xml,
e raccoglierli in una map tra id del treno fisico e una classe che raccoglie le altre informazioni*/

/*-----------------------------------------------------------------------------------------------

L'ATS associa ad ogni treno fisico un TRN
-------------------------------------------------------------------------------------------------*/

public ref class mapTrenoFisicoLogico
{
Dictionary<int, TrenoFisicoLogico^>^ map;
public:

	mapTrenoFisicoLogico(void);

	//void set_Map(Dictionary<int, TrenoFisicoLogico^>^ m){map=m;};
	Dictionary<int, TrenoFisicoLogico^>^ get_Map(){return map;};

	void inizializza();
	void saveXml(System::IO::Stream ^stream);
	virtual  System::String^ ToString() override{
		System::String ^out ="";
		for each( KeyValuePair<int, TrenoFisicoLogico^> kvp in map )
        {
           out+= " Key id treno fisico: "+ kvp.Key+";";
		   out+= kvp.Value->ToString();
        }
	   return out;
	};
};

