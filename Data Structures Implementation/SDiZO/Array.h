#pragma once
#include <string>

class Array
{
public:
	int elementCounter;
	Array();
	~Array();
	void addElement(int index, int newElement);
	void addFirstElement(int newElement);
	void addLastElement(int newElement);
	void deleteElement(int index);
	void deleteFirstElement();
	void deleteLastElement();
	void displayArray();
	bool searchElement(int value);
	bool loadDataFromFile(std::string name);
	void generateRandomArray(int numberOfElements, int range);
	int *array;
	void clearArray();
private:
	
};

