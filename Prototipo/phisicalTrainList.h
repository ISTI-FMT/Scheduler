#pragma once
#include "phisicalTrain.h"
#include <list>
#include <iostream>
using namespace std;

class phisicalTrainList
{
	std::list<phisicalTrain> treni;
public:
	phisicalTrainList(void);
	void aggiungiTreno(phisicalTrain &treno){treni.insert(treni.begin(), treno);};
	string getFirstTrainIP();
	int getFirstTrainPort();
	~phisicalTrainList(void);
};

