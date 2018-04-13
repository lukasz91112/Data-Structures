#pragma once
#include "Knapsack.h"
#include <list>

class GreedyKnapsack
{
public:
	GreedyKnapsack();
	~GreedyKnapsack();
	static void RunByDensity(Knapsack *knapsack);
	static void RunByValue(Knapsack *knapsack);
	struct compareItemByValue
	{
		bool operator ()(const Knapsack::item firstItem, const Knapsack::item secondItem)
		{
			return firstItem.value < secondItem.value;
		}
	};
	struct compareItemByDensity
	{
		bool operator ()(const Knapsack::item firstItem, const Knapsack::item secondItem)
		{
			return firstItem.density < secondItem.density;
		}
	};

private:
	static void DisplaySolution(std::list <Knapsack::item> *listOfItems, int capacity, bool isDensity);
};

