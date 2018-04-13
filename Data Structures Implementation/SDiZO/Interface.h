#pragma once
#include "Array.h"

class Interface
{
public:
	Interface();
	~Interface();
private:
	Array *array;
	void mainMenu();
	void tableMenu();
	void addElement();
	void deleteElement();
	void loadDataFromFile();
	void generateRandomArray();
	void displayArray();
	void searchElement();
	void testArray();
	void testAddFirst(int numberOfTrials, int sizeOfPopulation);
	void testAddLast(int numberOfTrials, int sizeOfPopulation);
	void testAddRandom(int numberOfTrials, int sizeOfPopulation);
	void testDeleteFirst(int numberOfTrials, int sizeOfPopulation);
	void testDeleteLast(int numberOfTrials, int sizeOfPopulation);
	void testDeleteRandom(int numberOfTrials, int sizeOfPopulation);
	void testSearch(int numberOfTrials, int sizeOfPopulation);
	void arrayTestAdd(int numberOfTrials, int sizeOfPopulation);
	void arrayTestDelete(int numberOfTrials, int sizeOfPopulation);
	int generateRandomNumber(int range);
	long long int read_QPC();
	
};

