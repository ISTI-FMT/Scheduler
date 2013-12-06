#pragma once
#include "IControllerListTrain.h"
#include "KeyListTrain.h"
#include "Train.h"
#include "tabellaOrario\\Fermata.h"

public interface class IListTrainView
{
	void AddListener(IControllerListTrain ^c );
	void ViewNewTrain(KeyListTrain ^key,Train^ train);
	void ViewChangeTrain(KeyListTrain ^key,StateTrain state);
	void ViewChangeTrain(KeyListTrain ^key,List<Fermata^>^ train);
	void ViewDeleteList();
};