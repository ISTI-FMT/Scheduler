#pragma once
#include "tabellaOrario\\Fermata.h"
#using <System.dll>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Globalization;

enum  StateTrain { PRONTO = 0, USCITASTAZIONE = 1, ENTRATASTAZIONE = 2,  NONPRONTO = 3, TERMINATO=4};

ref class Train
{ 
	DateTime TimeStampNextEvent;
	int TrainRunningNumber;
	int TrainPhisicalNumber;
	List<Fermata^> ^Listaitinerari;
	StateTrain Statodeltreno;
	int indicelistaitinerari;
public:
	Train( int trn, int tpn);
	Train( int tpn);
	Train( int trn, int tpn, List<Fermata^> ^listit);
	Train( int trn, int tpn, List<Fermata^> ^listit, StateTrain st);
	int getTRN(){return TrainRunningNumber;};
	int getTPN(){return TrainPhisicalNumber;};
	StateTrain getStatoTreno(){return Statodeltreno;};
	void setStatoTreno(StateTrain st){Statodeltreno=st;};
	void setListaItineari(List<Fermata^> ^listIt){Listaitinerari=listIt; };
	KeyValuePair<int, int> ^getStazioneItinerario();

	List<Fermata^>^getListaItineari(){return Listaitinerari; };
	DateTime ^getTimeNextEvent(){return TimeStampNextEvent;};
	void setTimeStampNextEvent(DateTime TNE){TimeStampNextEvent=TNE;};
	virtual System::String ^ToString() override;
};

