#include "phisicalTrainList.h"


phisicalTrainList::phisicalTrainList(void)
{
}

string phisicalTrainList::getFirstTrainIP()
{
	std::list<phisicalTrain>::iterator it=treni.begin();
	return (*it).getIpAddress();
}

int phisicalTrainList::getFirstTrainPort()
{
	std::list<phisicalTrain>::iterator it=treni.begin();
	return (*it).getTcpPort();
}

phisicalTrainList::~phisicalTrainList(void)
{
}
