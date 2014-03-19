#pragma once
#include "tabellaOrario\\Fermata.h"
#include "physicalTrain.h"
#using <System.dll>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Globalization;

//questa classe viene usata per rappresentare il treno nella lista pronti

public enum class StateTrain  { PRONTO = 0, USCITASTAZIONE = 1, ENTRATASTAZIONE = 2,  NONPRONTO = 3, TERMINATO=4};

public ref class Train : public IComparable<Train^>
{ 
	DateTime TimeStampNextEvent;
	int TrainRunningNumber;
	physicalTrain ^PhysicalTrain;
	List<Fermata^> ^Listafermate;
	StateTrain Statodeltreno;
	int indicelistaitinerari;
	int Priorita;
	int PhysicalTrainNumber;
public:
	Train(int p, int trn, physicalTrain ^pt);
	Train(int p, physicalTrain ^pt);
	Train(int p, int trn, physicalTrain ^pt, List<Fermata^> ^listit);
	Train(int p, int trn, physicalTrain ^pt, List<Fermata^> ^listit, double time);
	Train(int p, int trn, physicalTrain ^pt, List<Fermata^> ^listit, StateTrain st);
	int getTRN(){return TrainRunningNumber;};
	physicalTrain^ getPhysicalTrain(){return PhysicalTrain;};
	StateTrain getStatoTreno(){return Statodeltreno;};
	void setStatoTreno(StateTrain st){Statodeltreno=st;};
	void setListaFermate(List<Fermata^> ^listIt){Listafermate=listIt; };
	int getindex(){return indicelistaitinerari;};
	KeyValuePair<int, int> ^getStazioneItinerario();
	void changeOrari( List<Fermata^> ^nuoviorari);
	List<Fermata^>^getListaFermate(){return Listafermate; };
	DateTime ^getTimeNextEvent(){
		setTimeStampNextEvent(getOrarioPartenza());
		return TimeStampNextEvent;};
	Double getOrarioPartenza();
	void goNextItinerario();
	void setTimeStampNextEvent(DateTime TNE){TimeStampNextEvent=TNE;};
	virtual System::String ^ToString() override;


	virtual Int32 CompareTo(Train^ otherKey);
	
	int getPriorita(){return Priorita;};
	void setPriorita(int p){Priorita=p;};

	int getPTN(){return PhysicalTrainNumber;};


	void setTimeStampNextEvent(double time);



};

