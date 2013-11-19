#pragma once
#include "tabellaOrario\\Fermata.h"
#include "physicalTrain.h"
#using <System.dll>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Globalization;

enum  StateTrain { PRONTO = 0, USCITASTAZIONE = 1, ENTRATASTAZIONE = 2,  NONPRONTO = 3, TERMINATO=4};

public ref class Train
{ 
	DateTime TimeStampNextEvent;
	int TrainRunningNumber;
	physicalTrain ^PhysicalTrain;
	List<Fermata^> ^Listaitinerari;
	StateTrain Statodeltreno;
	int indicelistaitinerari;
public:
	Train( int trn, physicalTrain ^pt);
	Train( physicalTrain ^pt);
	Train( int trn, physicalTrain ^pt, List<Fermata^> ^listit);
	Train( int trn, physicalTrain ^pt, List<Fermata^> ^listit, StateTrain st);
	int getTRN(){return TrainRunningNumber;};
	physicalTrain^ getPhysicalTrain(){return PhysicalTrain;};
	StateTrain getStatoTreno(){return Statodeltreno;};
	void setStatoTreno(StateTrain st){Statodeltreno=st;};
	void setListaItineari(List<Fermata^> ^listIt){Listaitinerari=listIt; };
	KeyValuePair<int, int> ^getStazioneItinerario();

	List<Fermata^>^getListaItineari(){return Listaitinerari; };
	DateTime ^getTimeNextEvent(){return TimeStampNextEvent;};
	Double getOrarioPartenza();
	void goNextItinerario();
	void setTimeStampNextEvent(DateTime TNE){TimeStampNextEvent=TNE;};
	virtual System::String ^ToString() override;
};

