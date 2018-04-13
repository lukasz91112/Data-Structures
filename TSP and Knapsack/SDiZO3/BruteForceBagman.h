#pragma once
#include "Bagman.h"
class BruteForceBagman
{
public:
	BruteForceBagman();
	~BruteForceBagman();
	static const int inf_value = INT32_MAX;
	static void RunBagman(Bagman *bagman);
	static long long int BruteForceBagman::read_QPC();
	static void BruteForceBagman::Test();
private:
	static void DisplaySolution(Bagman *bagman, int *solution, int summaryWeight);
};

