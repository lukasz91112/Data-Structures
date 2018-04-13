#pragma once
#include "BinaryHeap.h"

class BinaryHeapInterface
{
public:
	BinaryHeapInterface();
	~BinaryHeapInterface();
private:
	BinaryHeap *binaryHeap = new BinaryHeap();
	void binaryHeapMenu();
	void addElement();
	void deleteElement();
	void loadDataFromFile();
	void generateRandomBinaryHeap();
	void displayBinaryHeap();
	void searchElement();
	void testBinaryHeap();
	void testAddBinaryHeap(int numberOfTrials, int sizeOfPopulation);
	void testDeleteBinaryHeap(int numberOfTrials, int sizeOfPopulation);
	void testSearchBinaryHeap(int numberOfTrials, int sizeOfPopulation);
	long long int read_QPC();
	void test();
};

