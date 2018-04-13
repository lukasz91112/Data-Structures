#pragma once
#include "List.h"
#include "Array.h"
class ListInterface
{
public:
	ListInterface();
	~ListInterface();
private:
	List *list;
	void listMenu();
	void addElement();
	void deleteElement();
	void loadDataFromFile();
	void generateRandomList();
	void displayList();
	void searchElement();
	void testList();
	void testAddFirst(int numberOfTrials, int sizeOfPopulation);
	void testAddLast(int numberOfTrials, int sizeOfPopulation);
	void testAddRandom(int numberOfTrials, int sizeOfPopulation);
	void testDeleteFirst(int numberOfTrials, int sizeOfPopulation);
	void testDeleteLast(int numberOfTrials, int sizeOfPopulation);
	void testDeleteRandom(int numberOfTrials, int sizeOfPopulation);
	void listTestAdd(int numberOfTrials, int sizeOfPopulation);
	void listTestDelete(int numberOfTrials, int sizeOfPopulation);
	void testSearch(int numberOfTrials, int sizeOfPopulation);
	long long int read_QPC();
};



