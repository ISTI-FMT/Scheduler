#using <System.dll>
#include "AreaCritica.h"
#include "AreaCriticaCircolare.h"
#include "AreaCriticaLineare.h"
#include "MissioneAnnotata.h"
#include "Deadlock.h"

using namespace System;
using namespace System::Collections::Generic;

#pragma once
public ref class AreeCritiche
{
private:
	/*
	 * Dizionario che associa TRN a missioni annotate
	 */
	Dictionary<int, MissioneAnnotata^>^ missioni;
	List<AreaCritica^>^ areeCritiche;
	array<int>^ limitiAree;
	Dictionary<int, int>^ posizioniTreni;
	List<Deadlock^>^ deadlockNoti;
	Dictionary<int, List<AreaCritica^>^>^ cdbAree;
	String^ XmlFilename;
	String^ XsdFilename;
	void Init();
public:
	MissioneAnnotata^ get_Missione(int trn) 
	{ 
		MissioneAnnotata^ res = nullptr;
		if (missioni->ContainsKey(trn))
		{
			res = missioni[trn]; 
		}
		return res;
	}

	array<int>^ get_limitiAree() { return limitiAree;}
	AreeCritiche();
	AreeCritiche(String ^xmlAreecritiche);
	void leggiFileConfigurazioneAreeCritiche(System::IO::Stream^ readStreamXML);
	/*
	* Ritorna TRUE se un treno può entrare nel cdb, FALSE altrimenti.
	* Il treno può entrare nel cdb se tutte le aree critiche che lo contengono non hanno raggiunto il massimo numero di treni consentito
	*/
	bool richiestaCdb(int cdb, int Trn);
	void MuoviTreno(int trn, int cdb);
	void EliminaTreno(int trn);
};

