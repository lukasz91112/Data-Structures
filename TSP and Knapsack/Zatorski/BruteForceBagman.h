#pragma once
#include "Bagman.h"
class BruteForceBagman
{
public:
	BruteForceBagman();
	~BruteForceBagman();
	static const int inf_value = INT32_MAX;
	static void RunBagman(Bagman *bagman);
private:
	static void DisplaySolution(Bagman *bagman, int *solution, int summaryWeight);
};

