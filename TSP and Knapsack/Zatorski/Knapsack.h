#pragma once
#include <vector>
#include <string>

class Knapsack
{
public:
	Knapsack();
	~Knapsack();
	struct item
	{
		int index;
		int value;
		int weight;
		float density;
	};
	void CreateRandomKnapsack(int numberOfItems, int knapsackCapacity);
	bool LoadKnapsackFromFile(std::string filename);
	void DisplayKnapsack();
	std::vector<item>* GetVector()
	{
		return vectorOfItems;
	}
	int GetCapacity()
	{
		return capacity;
	}
	int GetNumberOfItems()
	{
		return numberOfItems;
	}
private:
	int capacity;
	int numberOfItems;
	std::vector<item> *vectorOfItems;
	
};

