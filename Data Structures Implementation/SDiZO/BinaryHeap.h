#pragma once
#include <string>
class BinaryHeap
{
public:
	BinaryHeap();
	~BinaryHeap();
	std::string cr;
	std::string cl;
	std::string cp;
	int *binaryHeap;
	int elementCounter;
	void addElement(int newElement);
	void deleteElement();
	void generateRandomBinaryHeap(int numberOfElements);
	void repairHeapUp(int index);
	void repairHeapDown();
	void displayTree(std::string sp, std::string sn, int v);
	void displayBinaryHeap();
	bool loadDataFromFile(std::string name);
	bool searchElement(int value);
	void clearBinaryHeap();
	int generateRandomNumber(int range);
};

