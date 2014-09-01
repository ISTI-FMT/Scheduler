#using <System.dll>
#include "AreaCritica.h"
#include "AreaCriticaCircolare.h"
#include "AreaCriticaLineare.h"
#include "MissioneAnnotata.h"

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
	String^ XmlFilename;
	String^ XsdFilename;
	array<int>^ limitiAree;

	static const int NessunaAzione = 0;
    static const int EntraSinistra = 3;
    static const int EsciSinistra = -3;
    static const int EntraDestra = 2;
    static const int EsciDestra = -2;
    static const int EntraStessaDirezione = 4;
    static const int EsciStessaDirezione = -4;

    static const int EntrataCircolare = 1;
	static const int UscitaCircolare = -1;
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

	//Data un'area lineare, una missione e il cdb in cui si trova un treno, ritorna la direzione in cui il treno è entrato nell'area
	int get_Direzione(List<int>^ area, List<int>^ missione, int cdbPosizione);

	array<int>^ get_limitiAree() { return limitiAree;}
	AreeCritiche();
	AreeCritiche(String ^xmlAreecritiche);
	void leggiFileConfigurazioneAreeCritiche(System::IO::Stream^ readStreamXML);
	/*
	* Ritorna TRUE se un treno può entrare nel cdb, FALSE altrimenti.
	* Il treno può entrare nel cdb se tutte le aree critiche che lo contengono non hanno raggiunto il massimo numero di treni consentito
	*/
	bool richiestaCdb(int cdb, int Trn);

	List<GestioneAreeCritiche::MissioneTreno^>^ get_missioniTreno();

	void AreeCritiche::Carica(GestioneAreeCritiche::Output::DatiAree^ dati, Dictionary<int,int>^ posizioniTreni);
};

