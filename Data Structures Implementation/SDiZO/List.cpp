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

	// Je�eli podany index to 0, to funkcja dodaje go jako pierwszy
	if (index == 0)
	{
		addFirstElement(value);
		return;
	}
	// Je�eli podany index jest ostatni, to element dodany zostaje na ko�cu
	if (index == (elementCounter - 1))
	{
		addLastElement(value);
		return;
	}
	// Stworzenie nowego elementu o podanej warto�ci
	Element *newElement = new Element(value);
	// Warto�� pomocnicza, do przewijania listy
	Element *tempElement = head;
	// P�tla przewijaj�ca list�
	for (int currentIndex = 0; currentIndex < index; currentIndex++)
	{

		tempElement = tempElement->nextElement;

	}
	// Wstawianie nowego elementu
	newElement->previousElement = tempElement->previousElement;
	newElement->nextElement = tempElement;
	(tempElement->previousElement)->nextElement = newElement;
	// Zwi�kszenie liczby element�w
	elementCounter++;

}

// Funkcja ta dodaje nowy element na pocz�tku

void List::addFirstElement(int value)
{

	//Utworzenie nowego elementu o podanej warto�ci
	Element *newElement = new Element(value);
	
	// Je�eli lista ma ju� jaki� element to nast�puje podmiana g�owy, je�eli nie to dodany element jest pierwszy, czyli jest g�ow� i ogonem zarazem
	if (head != NULL)
	{
		newElement->nextElement = head;
		head->previousElement = newElement;
	}
	else
		tail = newElement;
	head = newElement;
	// Zwi�kszenie licznika element�w
	elementCounter++;

}

// Funkcja ta dodaje element jako ostatni

void List::addLastElement(int value)
{
	
	// Stworzenie nowego elementu
	Element *newElement = new Element(value);
	// Je�eli lista ma ju� jaki� element, to nast�puje podmiana ogona, je�eli nie to dodany element jest pierwszy, czyli jest ogonem i g�ow� zarazem
	if (tail != NULL)
	{
		newElement->previousElement = tail;
		tail->nextElement = newElement;
	}
	else
		head = newElement;
	tail = newElement;
	// Zwi�kszenie licznika element�w
	elementCounter++;

}

// Funkcja ta usuwa element o podanym indeksie

void List::deleteElement(int index)
{
	
	// Je�eli podany index to 0, to nast�puje usuni�cie pierwszego elementu
	if (index == 0)
	{
		deleteFirstElement();
		return;
	}
	//Je�eli podany index jest ostatni, to nast�puje usuni�cie ostatniego elementu
	if (index == (elementCounter - 1))
	{
		deleteLastElement();
		return;
	}
	//Pomocnicza zmienna do przewijania p�tli
	Element *tempElement = head;

	for (int currentIndex = 0; currentIndex < index; currentIndex++)
	{
		tempElement = tempElement->nextElement;
	}
	// Odci�cie usuwanego elementu od listy
	(tempElement->previousElement)->nextElement = tempElement->nextElement;
	(tempElement->nextElement)->previousElement = tempElement->previousElement;
	// Zwolnienie pami�ci usuwanego elementu
	delete tempElement;

}

// Funkcja ta usuwa pierwszy element

void List::deleteFirstElement()
{

	// Je�eli g�owa istnieje to zostanie usuni�ta
	if (head != NULL)
	{
		// Je�eli g�owa ma sw�j nast�pnik, to zostanie on g�ow�
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

	// Je�eli ogon istnieje to zostanie usuni�ty
	if (tail != NULL)
	{
		// Je�eli ogon ma poprzednika, to zostanie on ogonem
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

// Funkcja ta sprawdza czy podany element znajduje si� w tablicy

bool List::searchElement(int value)
{
	// Pomocniczy element do przeszukania listy
	Element *tempElement = head;
	// P�tla przeszukuje list� dop�ki nie znajdzie elementu lub nie wyjdzie poza zakres
	while (tempElement != NULL)
	{
		if (tempElement->value == value)
			return true;
		tempElement = tempElement->nextElement;
	}
	return false;
}

// Funkcja ta generuje losow� list�

void List::generateRandomList(int numberOfElements, int range)
{
	// Wyczyszczenie poprzedniej listy
	deleteAllElements();
	// Dodawanie losowych element�w
	for (int currentElement = 0; currentElement < numberOfElements; currentElement++)
	{
		addLastElement(generateRandomNumber(range));
	}
}

// Funkcja ta wy�wietla list�

void List::displayList()
{

	Element *tempElement = head;
	while (tempElement != NULL)
	{
		cout << tempElement->value << " ";
		tempElement = tempElement->nextElement;
	}
}

// Funkcja generuj�ca losow� liczbe

int List::generateRandomNumber(int range)
{

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> distFirst(1, range);

	return distFirst(gen);

}

// Funkcja czyszcz�ca obecn� liste

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

	// Pobranie informacji o ilo�ci element�w
	file >> elementCounter;

	// P�tla wczytuj�ca warto�ci z pliku
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

// Funkcja wy�wietlaj�ca warto�� znajduj�c� si� pod danym indexem 

int List::goToIndex(int index)
{
	Element *tempElement = head;
	for (int currentIndex = 0; currentIndex < index; currentIndex++)
	{
		tempElement = tempElement->nextElement;
	}
	return tempElement->value;
}
