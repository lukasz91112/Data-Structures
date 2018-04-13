#pragma once
#include "Knapsack.h"
#include "BruteForceKnapsack.h"
#include "GreedyKnapsack.h"
#include "Bagman.h"
#include "BruteForceBagman.h"
#include "GreedyBagman.h"

class Menu
{
public:
	Menu();
	~Menu();
	Knapsack *knapsack;
	Bagman *bagman;
	void SelectProblem();
	void KnapsackMenu();	
	void KnapsackLoadFromFile();
	void KnapsackCreateRandom();
	void KnapsackRun();
	void BagmanMenu();
	void BagmanLoadFromFile();
	void BagmanCreateRandom();
	void BagmanRun();
};

