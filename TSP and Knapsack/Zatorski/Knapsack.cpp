#include "stdafx.h"
#include "Knapsack.h"
#include <random>
#include <ctime>
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

Knapsack::Knapsack()
{
	vectorOfItems = NULL;
}


Knapsack::~Knapsack()
{
	if (vectorOfItems != NULL)
		delete vectorOfItems;
}

// Funkcja ta generuje losowy problem plecakowy
void Knapsack::CreateRandomKnapsack(int numberOfItems, int knapsackCapacity)
{
	srand(time(NULL));
	// Ustawienie pojemno�ci plecaka
	capacity = knapsackCapacity;
	// Ustawienie ilo�ci przedmiot�w
	this->numberOfItems = numberOfItems;
	// Je�eli vector przedmiot�w ju� istnieje to zostanie usuni�ty
	if (vectorOfItems != NULL)
		delete vectorOfItems;
	// Utworzenie nowego vectora z przedmiotami
	vectorOfItems = new vector<item>();
	// Tymczasowy przedmiot
	item *tempItem = new item;
	// Tymczasowa waga oraz warto��
	int tempWeight;
	int tempValue;
	// Obecna waga wszystkich przedmiot�w
	int currentSummaryWeight = 0;
	// Obecna liczba przedmiot�w
	int currentSize = 0;
	while (currentSize < numberOfItems)
	{
		// Je�eli dodajemy ostatni przedmiot to sprawdzamy czy obecna waga przedmiot�w jest wi�ksza od pojemno�ci plecaka
		if (currentSize == numberOfItems - 1)
		{
			// Je�eli jest, to ostatnia waga musi by� odpowiednio dobrana
			if (currentSummaryWeight <= knapsackCapacity)
				tempWeight = knapsackCapacity - currentSummaryWeight + 1;
		}
		// Je�eli nie jest, to waga jest losowana
		else
			tempWeight = rand() % (capacity/2) + 1;
		tempValue = rand() % numberOfItems + 1;
		// Dodawanie nowego przedmiotu
		tempItem->value = tempValue;
		tempItem->weight = tempWeight;
		tempItem->index = currentSize;
		tempItem->density = (float)tempValue / (float)tempWeight;

		vectorOfItems->push_back(*tempItem);
		currentSummaryWeight += tempWeight;
		currentSize++;
	}
	// Sprz�tanie
	delete tempItem;
	// Wy�wietlenie wygenerowanego plecaka
	DisplayKnapsack();

}

// Funkcja wczytuj�ca problem plecakowy z pliku
bool Knapsack::LoadKnapsackFromFile(std::string filename)
{
	// Usuni�cie poprzednich przedmiot�w
	if (vectorOfItems != NULL)
		delete vectorOfItems;
	// Utworzenie nowego vectora z przedmiotami
	vectorOfItems = new vector<item>();

	// Otwarcie pliku
	ifstream file;
	file.open(filename);

	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;

	// Pobranie informacji o ilo�ci element�w oraz pojemno�ci
	file >> capacity;
	file >> numberOfItems;

	// Zmienna przechowuj�ca tymczasowy przedmiot
	item tempItem;


	// P�tla wczytuj�ca przedmioty
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
	{
		file >> tempItem.weight;
		file >> tempItem.value;
		tempItem.index = currentItem;
		tempItem.density = (float)(tempItem.value) / (float)(tempItem.weight);
		vectorOfItems->push_back(tempItem);
	}
	// Wy�wietlenie wczytanego problemu
	DisplayKnapsack();
	file.close();
	return true;
}

// Funkcja wy�wietlaj�ca problem plecakowy
void Knapsack::DisplayKnapsack()
{
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
		cout << (*vectorOfItems)[currentItem].index << " : Wartosc = " << (*vectorOfItems)[currentItem].value << "  Waga = " << (*vectorOfItems)[currentItem].weight << "  Gestosc = " << setprecision(2) << (*vectorOfItems)[currentItem].density << endl;
	cout << "Pojemnosc plecaka: " << capacity << endl << endl;
	system("PAUSE");
}


