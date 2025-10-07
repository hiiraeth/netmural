#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <random>
#include "time.h"
#include <chrono>
#include <thread>
#include <future>
#include <iostream>


class DataSource
{
	const int REFRESH_RATE = 50;
	float value = 0;
	std::random_device device;
	std::mt19937 gen;
	std::uniform_real_distribution<float> distrib{40.f, 120.f};

public:
	DataSource();
	void generateRandomValue();
	void getValue(std::atomic<float>* returnValue, std::atomic<bool>* running);
};

#endif