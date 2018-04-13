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

// Funkcja realizuj¹ca przegl¹d zupe³ny
void BruteForceKnapsack::Run(Knapsack *knapsack)
{
	// Pobranie danych o problemie
	vector<Knapsack::item> *vectorOfItems = knapsack->GetVector();
	int numberOfItems = knapsack->GetNumberOfItems();
	int capacity = knapsack->GetCapacity();

	// Zmienne pomocnicze
	// Obecna najwiêksza wartoœæ
	int currentMaxValue = 0;
	int currentValue;
	int currentWeight;
	// Obecne rozwi¹zanie
	bool *tempSolution = new bool[numberOfItems];
	// Obecna kombinacja przedmiotów mieszcz¹cych siê w plecaku
	bool *tempKnapsack = new bool[numberOfItems];
	// Liczba kombinacji
	int numberOfKnapsacks = static_cast<int>(pow(2, numberOfItems)) - 1;
	// 
	int currentItem;
	// Oznaczenie wszystkich przedmiotów jako nie bêd¹cych w plecaku
	for (int tempItem = 0; tempItem < numberOfItems; tempItem++)
		tempKnapsack[tempItem] = false;
	// G³ówna pêtla wykonuj¹ca algorytm
	for (int currentKnapsack = 0; currentKnapsack < numberOfKnapsacks; currentKnapsack++)
	{
		// Zmienna pomocnicza do zmieniania kombinacji
		currentItem = 0;
		// Waga obecnej kombinacji
		currentWeight = 0;
		// Wartoœæ obecnej kombinacji
		currentValue = 0;
		// Pêtla zmieniaj¹ca kombinacje
		while (tempKnapsack[currentItem] == true && currentItem < numberOfItems)
		{
			tempKnapsack[currentItem] = false;
			currentItem++;
		}
		// "W³o¿enie" przedmiotu do plecaka
		tempKnapsack[currentItem] = 1;

		// Podliczenie wartoœci oraz wagi obecnej kombinacji przedmiotów
		for (int tempItem = 0; tempItem < numberOfItems; tempItem++)
			if (tempKnapsack[tempItem])
			{
				currentValue += (*vectorOfItems)[tempItem].value;
				currentWeight += (*vectorOfItems)[tempItem].weight;
			}
		// Je¿eli obecna kombinacja ma wiêksz¹ wartoœæ i mieœci siê w plecaku to staje siê obecnym rozwi¹zaniem
		if (currentValue > currentMaxValue && currentWeight <= capacity)
		{
			currentMaxValue = currentValue;
			for (int tempItem = 0; tempItem < numberOfItems; tempItem++)
				tempSolution[tempItem] = tempKnapsack[tempItem];	
		}
	}
	// Wyœwietlenie rozwi¹zania
	DisplaySolution(knapsack, tempSolution);
	// Sprz¹tanie
	delete[] tempKnapsack;
	delete[] tempSolution;
}

// Funkcja wyœwietlaj¹ca rozwi¹zanie
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
