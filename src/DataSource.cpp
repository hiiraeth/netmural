#include "DataSource.h"


DataSource::DataSource()
{
	value = 0;
}

void DataSource::generateRandomValue()
{
	this->value = distrib(gen);
	std::this_thread::sleep_for(std::chrono::milliseconds(REFRESH_RATE));
}

void DataSource::getValue(std::atomic<float>* returnValue, std::atomic<bool>* running)
{
	
	while (running->load())
	{
		generateRandomValue();
		*returnValue = value;

		if (!(running->load())) {
			std::cout << "Breaking from loop...";
			break;
		}
	}
}