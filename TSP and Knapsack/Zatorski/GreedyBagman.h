#pragma once
#include "Bagman.h"
#include <string>
class GreedyBagman
{
public:
	GreedyBagman();
	~GreedyBagman();
	static const int inf_value = INT32_MAX;
	static void Run(Bagman *bagman);
private:
	static void DisplaySolution(int *solution, int summaryWeight, int numberOfCities);
	
};

