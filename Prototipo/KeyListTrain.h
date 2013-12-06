#pragma once
#include "physicalTrain.h"
#using <System.dll>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Globalization;

public ref class KeyListTrain : public IComparable<KeyListTrain^>
{
	int Priorita;
	DateTime ^TimeStampNextEvent;
	int TrainRunningNumber;
	int PhysicalTrainNumber;
public:
	KeyListTrain(int p, int trn, int ptn);
	KeyListTrain(int p, int trn, int ptn, double time);
	KeyListTrain(int p, int ptn);
	virtual Int32 CompareTo(KeyListTrain^ otherKey);
	int getPriorita(){return Priorita;};
	void setPriorita(int p){Priorita=p;};

	int getTRN(){return TrainRunningNumber;};
	int getPTN(){return PhysicalTrainNumber;};
	DateTime ^getTimeNextEvent(){return TimeStampNextEvent;};
	void setTimeStampNextEvent(DateTime TNE){TimeStampNextEvent=TNE;};
	void setTimeStampNextEvent(double time);
	virtual String ^ToString() override;
};

