#using <System.dll>
#include "AreaCritica.h"
#include "AreaCriticaCircolare.h"
#include "AreaCriticaLineare.h"
#include "MissioneAnnotata.h"

using namespace System;
using namespace System::Collections::Generic;

#pragma once
ref class AreeCritiche
{
private:
	List<AreaCritica^>^ areeCritiche;
	Dictionary<int, List<AreaCritica^>^>^ cdbAree;
	String^ XmlFilename;
public:
	AreeCritiche();
	void leggiFileConfigurazioneAreeCritiche();
	/*
	* Ritorna TRUE se un treno può entrare nel cdb, FALSE altrimenti.
	* Il treno può entrare nel cdb se tutte le aree critiche che lo contengono non hanno raggiunto il massimo numero di treni consentito
	*/
	bool richiestaCdb(int cdb, int Trn);

	void entrataCdb(int cdb, int Trn);
};

