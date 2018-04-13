#include "stdafx.h"
#include "List.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

List::List()
{

	head = NULL;
	tail = NULL;
	elementCounter = 0;

}


List::~List()
{
	Element *tempElement;;
	while (head != NULL)
	{
		tempElement = head->nextElement;
		delete head;
		head = tempElement;
	}

}

// Funkcja ta dodaje nowy element, we wskazane miejsce

void List::addElement(int value, int index)
{

	// Je¿eli podany index to 0, to funkcja dodaje go jako pierwszy
	if (index == 0)
	{
		addFirstElement(value);
		return;
	}
	// Je¿eli podany index jest ostatni, to element dodany zostaje na koñcu
	if (index == (elementCounter - 1))
	{
		addLastElement(value);
		return;
	}
	// Stworzenie nowego elementu o podanej wartoœci
	Element *newElement = new Element(value);
	// Wartoœæ pomocnicza, do przewijania listy
	Element *tempElement = head;
	// Pêtla przewijaj¹ca listê
	for (int currentIndex = 0; currentIndex < index; currentIndex++)
	{

		tempElement = tempElement->nextElement;

	}
	// Wstawianie nowego elementu
	newElement->previousElement = tempElement->previousElement;
	newElement->nextElement = tempElement;
	(tempElement->previousElement)->nextElement = newElement;
	// Zwiêkszenie liczby elementów
	elementCounter++;

}

// Funkcja ta dodaje nowy element na pocz¹tku

void List::addFirstElement(int value)
{

	//Utworzenie nowego elementu o podanej wartoœci
	Element *newElement = new Element(value);
	
	// Je¿eli lista ma ju¿ jakiœ element to nastêpuje podmiana g³owy, je¿eli nie to dodany element jest pierwszy, czyli jest g³ow¹ i ogonem zarazem
	if (head != NULL)
	{
		newElement->nextElement = head;
		head->previousElement = newElement;
	}
	else
		tail = newElement;
	head = newElement;
	// Zwiêkszenie licznika elementów
	elementCounter++;

}

// Funkcja ta dodaje element jako ostatni

void List::addLastElement(int value)
{
	
	// Stworzenie nowego elementu
	Element *newElement = new Element(value);
	// Je¿eli lista ma ju¿ jakiœ element, to nastêpuje podmiana ogona, je¿eli nie to dodany element jest pierwszy, czyli jest ogonem i g³ow¹ zarazem
	if (tail != NULL)
	{
		newElement->previousElement = tail;
		tail->nextElement = newElement;
	}
	else
		head = newElement;
	tail = newElement;
	// Zwiêkszenie licznika elementów
	elementCounter++;

}

// Funkcja ta usuwa element o podanym indeksie

void List::deleteElement(int index)
{
	
	// Je¿eli podany index to 0, to nastêpuje usuniêcie pierwszego elementu
	if (index == 0)
	{
		deleteFirstElement();
		return;
	}
	//Je¿eli podany index jest ostatni, to nastêpuje usuniêcie ostatniego elementu
	if (index == (elementCounter - 1))
	{
		deleteLastElement();
		return;
	}
	//Pomocnicza zmienna do przewijania pêtli
	Element *tempElement = head;

	for (int currentIndex = 0; currentIndex < index; currentIndex++)
	{
		tempElement = tempElement->nextElement;
	}
	// Odciêcie usuwanego elementu od listy
	(tempElement->previousElement)->nextElement = tempElement->nextElement;
	(tempElement->nextElement)->previousElement = tempElement->previousElement;
	// Zwolnienie pamiêci usuwanego elementu
	delete tempElement;

}

// Funkcja ta usuwa pierwszy element

void List::deleteFirstElement()
{

	// Je¿eli g³owa istnieje to zostanie usuniêta
	if (head != NULL)
	{
		// Je¿eli g³owa ma swój nastêpnik, to zostanie on g³ow¹
		if (head->nextElement != NULL)
		{
			head = head->nextElement;
			delete head->previousElement;
			head->previousElement = NULL;
		}
		else
		{
			delete head;
			head = NULL;
		}
	}

}

// Funkcja ta usuwa ostatni element

void List::deleteLastElement()
{

	// Je¿eli ogon istnieje to zostanie usuniêty
	if (tail != NULL)
	{
		// Je¿eli ogon ma poprzednika, to zostanie on ogonem
		if (tail->previousElement != NULL)
		{
			tail = tail->previousElement;
			delete tail->nextElement;
			tail->nextElement = NULL;
		}
		else
		{
			delete tail;
			tail = NULL;
		}
			
	}
}

// Funkcja ta sprawdza czy podany element znajduje siê w tablicy

bool List::searchElement(int value)
{
	// Pomocniczy element do przeszukania listy
	Element *tempElement = head;
	// Pêtla przeszukuje listê dopóki nie znajdzie elementu lub nie wyjdzie poza zakres
	while (tempElement != NULL)
	{
		if (tempElement->value == value)
			return true;
		tempElement = tempElement->nextElement;
	}
	return false;
}

// Funkcja ta generuje losow¹ listê

void List::generateRandomList(int numberOfElements, int range)
{
	// Wyczyszczenie poprzedniej listy
	deleteAllElements();
	// Dodawanie losowych elementów
	for (int currentElement = 0; currentElement < numberOfElements; currentElement++)
	{
		addLastElement(generateRandomNumber(range));
	}
}

// Funkcja ta wyœwietla listê

void List::displayList()
{

	Element *tempElement = head;
	while (tempElement != NULL)
	{
		cout << tempElement->value << " ";
		tempElement = tempElement->nextElement;
	}
}

// Funkcja generuj¹ca losow¹ liczbe

int List::generateRandomNumber(int range)
{

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> distFirst(1, range);

	return distFirst(gen);

}

// Funkcja czyszcz¹ca obecn¹ liste

void List::deleteAllElements()
{
	
	Element *tempElement;;
	while (head != NULL)
	{
		tempElement = head->nextElement;
		delete head;
		head = tempElement;
	}
	elementCounter = 0;
	head = NULL;
	tail = NULL;

}

// Wczytanie danych z pliku

bool List::loadDataFromFile(string name)
{

	int tempValue;
	deleteAllElements();
	// Otwarcie pliku
	ifstream file;
	file.open(name);

	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;

	// Pobranie informacji o iloœci elementów
	file >> elementCounter;

	// Pêtla wczytuj¹ca wartoœci z pliku
	for (int i = 0; i < elementCounter; i++)
	{
		if (file.good())
		{
			file >> tempValue;
			addLastElement(tempValue);
		}
	}

	return true;

}

// Funkcja wyœwietlaj¹ca wartoœæ znajduj¹c¹ siê pod danym indexem 

int List::goToIndex(int index)
{
	Element *tempElement = head;
	for (int currentIndex = 0; currentIndex < index; currentIndex++)
	{
		tempElement = tempElement->nextElement;
	}
	return tempElement->value;
}
