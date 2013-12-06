#pragma once
#include "IControllerListTrain.h"

#include "Train.h"
#include "tabellaOrario\\Fermata.h"

public interface class IListTrainView
{
	void AddListener(IControllerListTrain ^c );
	void ViewNewTrain(Train^ train);
	void PaintTrain();
	void ViewDeleteList();
};