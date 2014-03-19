#pragma once
#include "AreaCritica.h"
#include "AreaCriticaCircolare.h"
#include "AreaCriticaLineare.h"
#include "MissioneAnnotata.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;


public ref class AreeCritiche
{
private:
	List<AreaCritica^>^ areeCritiche;
	Dictionary<int, List<AreaCritica^>^>^ cdbAree;
	String^ XmlFilename;
	String^ XsdFilename;
	/*
	Effettua l'entrata dentro il cdb. Aggiorna lo stato delle aree critiche coinvolte nel cdb.
	*/
	void entrataCdb(int cdb, int Trn);
	void leggiConfigurazioneAreeCritiche(Stream^ xmlStream);
public:
	AreeCritiche();
	/*
	Carica la configurazione delle aree critiche da file
	*/
	void leggiFileConfigurazioneAreeCritiche();

	/*
	Legge la configurazione delle aree critiche da una stringa contenente l'xml delle aree critiche
	*/
	void leggiConfigurazioneAreeCritiche(String^ data);

	/*
	* Ritorna TRUE se un treno può entrare nel cdb, FALSE altrimenti.
	* Il treno può entrare nel cdb se tutte le aree critiche che lo contengono non hanno raggiunto il massimo numero di treni consentito
	*/
	bool richiestaCdb(int cdb, int Trn);
};

