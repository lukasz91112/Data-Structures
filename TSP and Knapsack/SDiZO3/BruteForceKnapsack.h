#pragma once
#include "Knapsack.h"
#include <vector>

class BruteForceKnapsack
{
public:
	BruteForceKnapsack();
	~BruteForceKnapsack();
	static void Run(Knapsack *knapsack);
private:
	static void DisplaySolution(Knapsack *knapsack, bool *solution);
};