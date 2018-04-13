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
	// Ustawienie pojemnoœci plecaka
	capacity = knapsackCapacity;
	// Ustawienie iloœci przedmiotów
	this->numberOfItems = numberOfItems;
	// Je¿eli vector przedmiotów ju¿ istnieje to zostanie usuniêty
	if (vectorOfItems != NULL)
		delete vectorOfItems;
	// Utworzenie nowego vectora z przedmiotami
	vectorOfItems = new vector<item>();
	// Tymczasowy przedmiot
	item *tempItem = new item;
	// Tymczasowa waga oraz wartoœæ
	int tempWeight;
	int tempValue;
	// Obecna waga wszystkich przedmiotów
	int currentSummaryWeight = 0;
	// Obecna liczba przedmiotów
	int currentSize = 0;
	while (currentSize < numberOfItems)
	{
		// Je¿eli dodajemy ostatni przedmiot to sprawdzamy czy obecna waga przedmiotów jest wiêksza od pojemnoœci plecaka
		if (currentSize == numberOfItems - 1)
		{
			// Je¿eli jest, to ostatnia waga musi byæ odpowiednio dobrana
			if (currentSummaryWeight <= knapsackCapacity)
				tempWeight = knapsackCapacity - currentSummaryWeight + 1;
		}
		// Je¿eli nie jest, to waga jest losowana
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
	// Sprz¹tanie
	delete tempItem;
	// Wyœwietlenie wygenerowanego plecaka
	DisplayKnapsack();

}

// Funkcja wczytuj¹ca problem plecakowy z pliku
bool Knapsack::LoadKnapsackFromFile(std::string filename)
{
	// Usuniêcie poprzednich przedmiotów
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

	// Pobranie informacji o iloœci elementów oraz pojemnoœci
	file >> capacity;
	file >> numberOfItems;

	// Zmienna przechowuj¹ca tymczasowy przedmiot
	item tempItem;


	// Pêtla wczytuj¹ca przedmioty
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
	{
		file >> tempItem.weight;
		file >> tempItem.value;
		tempItem.index = currentItem;
		tempItem.density = (float)(tempItem.value) / (float)(tempItem.weight);
		vectorOfItems->push_back(tempItem);
	}
	// Wyœwietlenie wczytanego problemu
	DisplayKnapsack();
	file.close();
	return true;
}

// Funkcja wyœwietlaj¹ca problem plecakowy
void Knapsack::DisplayKnapsack()
{
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
		cout << (*vectorOfItems)[currentItem].index << " : Wartosc = " << (*vectorOfItems)[currentItem].value << "  Waga = " << (*vectorOfItems)[currentItem].weight << "  Gestosc = " << setprecision(2) << (*vectorOfItems)[currentItem].density << endl;
	cout << "Pojemnosc plecaka: " << capacity << endl << endl;
	system("PAUSE");
}


