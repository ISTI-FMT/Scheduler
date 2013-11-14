#pragma once

#using <System.dll>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Globalization;

ref class KeyListTrain : public IComparable<KeyListTrain^>
{
	int Priorita;
	DateTime TimeStampNextEvent;
	int TrainRunningNumber;
	int TrainPhisicalNumber;
public:
	KeyListTrain(int p, int trn, int tpn);
	KeyListTrain(int p, int tpn);
	virtual Int32 CompareTo(KeyListTrain^ otherKey);
	int getPriorita(){return Priorita;};
	int getTRN(){return TrainRunningNumber;};
	int getTPN(){return TrainPhisicalNumber;};
	DateTime ^getTimeNextEvent(){return TimeStampNextEvent;};
	void setTimeStampNextEvent(DateTime TNE){TimeStampNextEvent=TNE;};
	virtual String ^ToString() override;
};

