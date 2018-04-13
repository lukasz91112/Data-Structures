#include "stdafx.h"
#include "BruteForceKnapsack.h"
#include <iostream>

using namespace std;

BruteForceKnapsack::BruteForceKnapsack()
{
}


BruteForceKnapsack::~BruteForceKnapsack()
{
}

// Funkcja realizuj�ca przegl�d zupe�ny
void BruteForceKnapsack::Run(Knapsack *knapsack)
{
	// Pobranie danych o problemie
	vector<Knapsack::item> *vectorOfItems = knapsack->GetVector();
	int numberOfItems = knapsack->GetNumberOfItems();
	int capacity = knapsack->GetCapacity();

	// Zmienne pomocnicze
	// Obecna najwi�ksza warto��
	int currentMaxValue = 0;
	int currentValue;
	int currentWeight;
	// Obecne rozwi�zanie
	bool *tempSolution = new bool[numberOfItems];
	// Obecna kombinacja przedmiot�w mieszcz�cych si� w plecaku
	bool *tempKnapsack = new bool[numberOfItems];
	// Liczba kombinacji
	int numberOfKnapsacks = static_cast<int>(pow(2, numberOfItems)) - 1;
	// 
	int currentItem;
	// Oznaczenie wszystkich przedmiot�w jako nie b�d�cych w plecaku
	for (int tempItem = 0; tempItem < numberOfItems; tempItem++)
		tempKnapsack[tempItem] = false;
	// G��wna p�tla wykonuj�ca algorytm
	for (int currentKnapsack = 0; currentKnapsack < numberOfKnapsacks; currentKnapsack++)
	{
		// Zmienna pomocnicza do zmieniania kombinacji
		currentItem = 0;
		// Waga obecnej kombinacji
		currentWeight = 0;
		// Warto�� obecnej kombinacji
		currentValue = 0;
		// P�tla zmieniaj�ca kombinacje
		while (tempKnapsack[currentItem] == true && currentItem < numberOfItems)
		{
			tempKnapsack[currentItem] = false;
			currentItem++;
		}
		// "W�o�enie" przedmiotu do plecaka
		tempKnapsack[currentItem] = 1;

		// Podliczenie warto�ci oraz wagi obecnej kombinacji przedmiot�w
		for (int tempItem = 0; tempItem < numberOfItems; tempItem++)
			if (tempKnapsack[tempItem])
			{
				currentValue += (*vectorOfItems)[tempItem].value;
				currentWeight += (*vectorOfItems)[tempItem].weight;
			}
		// Je�eli obecna kombinacja ma wi�ksz� warto�� i mie�ci si� w plecaku to staje si� obecnym rozwi�zaniem
		if (currentValue > currentMaxValue && currentWeight <= capacity)
		{
			currentMaxValue = currentValue;
			for (int tempItem = 0; tempItem < numberOfItems; tempItem++)
				tempSolution[tempItem] = tempKnapsack[tempItem];	
		}
	}
	// Wy�wietlenie rozwi�zania
	DisplaySolution(knapsack, tempSolution);
	// Sprz�tanie
	delete[] tempKnapsack;
	delete[] tempSolution;
}

// Funkcja wy�wietlaj�ca rozwi�zanie
void BruteForceKnapsack::DisplaySolution(Knapsack *knapsack, bool *solution)
{
	vector<Knapsack::item> *vectorOfItems = knapsack->GetVector();
	int numberOfItems = knapsack->GetNumberOfItems();
	int summaryWeight = 0;
	int summaryValue = 0;
	cout << "PRZEGLAD ZUPELNY" << endl << endl;
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
	{
		if (solution[currentItem])
		{
			cout << "Przedmiot " << currentItem << " Wartosc " << (*vectorOfItems)[currentItem].value << " Waga: " << (*vectorOfItems)[currentItem].weight << " Gestosc: " << (*vectorOfItems)[currentItem].density << endl;
			summaryWeight += (*vectorOfItems)[currentItem].weight;
			summaryValue += (*vectorOfItems)[currentItem].value;
		}
	}
	cout << "Laczna wartosc: " << summaryValue << " Laczna waga: " << summaryWeight << " Pojemnosc plecaka: " << knapsack->GetCapacity() << endl << endl;

}
