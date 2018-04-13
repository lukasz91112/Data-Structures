#pragma once
#include "Element.h"
#include <string>

class List
{
public:
	List();
	~List();
	Element *head;
	Element *tail;
	int elementCounter;

	void addElement(int value, int index);
	void addFirstElement(int value);
	void addLastElement(int value);
	void deleteElement(int index);
	void deleteFirstElement();
	void deleteLastElement();
	bool searchElement(int value);
	void generateRandomList(int numberOfElements, int range);
	void displayList();
	int generateRandomNumber(int range);
	void deleteAllElements();
	bool loadDataFromFile(std::string name);
	int goToIndex(int index);

};

