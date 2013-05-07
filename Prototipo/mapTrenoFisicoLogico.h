#pragma once
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

/*-----------------------------------------------------------------------------------------------
Alessio:
L'ATS associa ad ogni treno fisico un TRN
-------------------------------------------------------------------------------------------------*/

ref class mapTrenoFisicoLogico
{
Dictionary<int, int>^ map;
public:

	mapTrenoFisicoLogico(void);
	mapTrenoFisicoLogico(System::String^ s);
	void set_Map(Dictionary<int, int>^ m){map=m;};
	Dictionary<int, int>^ get_Map(){return map;};

	void inizializza(System::String^ s);
	virtual  System::String^ ToString() override{
		System::String ^out ="";
		for each( KeyValuePair<int, int> kvp in map )
        {
           out=kvp.Key+"_"+kvp.Value+";";
        }
	   return out;
	};
};

