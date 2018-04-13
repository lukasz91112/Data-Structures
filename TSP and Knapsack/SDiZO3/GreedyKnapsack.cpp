#include "stdafx.h"
#include "GreedyKnapsack.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

GreedyKnapsack::GreedyKnapsack()
{
}


GreedyKnapsack::~GreedyKnapsack()
{
}

// Funkcja wykonuj¹ca algorytm zach³anny po gêstoœci
void GreedyKnapsack::RunByDensity(Knapsack * knapsack)
{
	// Inicjalizacja kolejki
	priority_queue < Knapsack::item, vector < Knapsack::item >,compareItemByDensity > *itemsPriorityQueue = new priority_queue < Knapsack::item, vector < Knapsack::item >, compareItemByDensity >();
	// Inicjalizacja listy przechowuj¹cej rozwi¹zanie
	list <Knapsack::item> *solution = new list<Knapsack::item>();
	// Pobranie danych o problemie plecakowym
	vector<Knapsack::item> *vectorOfItems = knapsack->GetVector();
	int numberOfItems = knapsack->GetNumberOfItems();
	int capacity = knapsack->GetCapacity();
	// Zmienna pomocnicza - obecna waga
	int currentWeight = 0;
	// Zmienna pomocnicza - obecnie analizowany przedmiot
	Knapsack::item tempItem;

	// Za³adowanie przedmiotów do kolejki
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
		itemsPriorityQueue->push((*vectorOfItems)[currentItem]);

	// G³ówna pêtla wykonuj¹ca algorytm
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
	{
		// Pobranie przedmiotu z wierzchu kolejki
		tempItem = itemsPriorityQueue->top();
		// Je¿eli dany przedmiot siê mieœci to nastêpuje dodanie go do rozwi¹zania
		if (tempItem.weight + currentWeight <= capacity)
		{
			solution->push_back(tempItem);
			currentWeight += tempItem.weight;
		}
		// Je¿eli plecak jest pe³ny to nastêpuje przerwanie algorytmu
		if (currentWeight == capacity)
			break;
		// Wyrzucenie rozpatrzonego przedmiotu z kolejki
		itemsPriorityQueue->pop();
	}

	// Wyswietlenie rozwiazania
	DisplaySolution(solution, capacity, true);

	// Czyszczenie pamieci
	delete solution;
	delete itemsPriorityQueue;
}

// Funkcja wykonuj¹ca algorytm zach³anny po wartoœci
void GreedyKnapsack::RunByValue(Knapsack * knapsack)
{
	// Inicjalizacja kolejki
	priority_queue < Knapsack::item, vector < Knapsack::item >, compareItemByValue > *itemsPriorityQueue = new priority_queue < Knapsack::item, vector < Knapsack::item >, compareItemByValue >();
	// Inicjalizacja listy przechowuj¹cej rozwi¹zanie
	list <Knapsack::item> *solution = new list<Knapsack::item>();
	// Pobranie danych o problemie plecakowym
	vector<Knapsack::item> *vectorOfItems = knapsack->GetVector();
	int numberOfItems = knapsack->GetNumberOfItems();
	int capacity = knapsack->GetCapacity();
	// Zmienna pomocnicza - obecna waga
	int currentWeight = 0;
	// Zmienna pomocnicza - obecnie analizowany przedmiot
	Knapsack::item tempItem;
	// Za³adowanie przedmiotów do kolejki

	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
		itemsPriorityQueue->push((*vectorOfItems)[currentItem]);

	// G³ówna pêtla wykonuj¹ca algorytm
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
	{
		// Pobranie przedmiotu z wierzchu kolejki
		tempItem = itemsPriorityQueue->top();
		// Je¿eli przedmiot siê mieœci to zostaje dodany do rozwi¹zania
		if (tempItem.weight + currentWeight <= capacity)
		{
			solution->push_back(tempItem);
			currentWeight += tempItem.weight;
		}
		// Je¿eli plecak jest pe³ny to nastêpuje przerwanie algorytmu
		if (currentWeight == capacity)
			break;
		itemsPriorityQueue->pop();
	}

	// Wyswietlenie rozwiazania
	DisplaySolution(solution, capacity, false);

	// Czyszczenie pamieci
	delete solution;
	delete itemsPriorityQueue;
}

// Funkcja wyœwietlaj¹ca rozwi¹zanie
void GreedyKnapsack::DisplaySolution(std::list<Knapsack::item> *listOfItems, int capacity, bool isDensity)
{
	int summaryValue = 0;
	int summaryWeight = 0;
	if (isDensity)
		cout << "ALGORYTM ZACHLANNY WG GESTOSCI" << endl << endl;
	else
		cout << "ALGORYTM ZACHLANNY WG WARTOSCI" << endl << endl;
	for (list<Knapsack::item>::iterator currentItem = listOfItems->begin(); currentItem != listOfItems->end(); currentItem++)
	{
		cout << "Przedmiot " << currentItem->index << " Wartosc: " << currentItem->value << " Waga: " << currentItem->weight << " Gestosc: " << currentItem->density << endl;
		summaryValue += currentItem->value;
		summaryWeight += currentItem->weight;
	}
	cout << "Laczna wartosc: " << summaryValue << " Laczna waga: " << summaryWeight << " Pojemnosc plecaka: " << capacity << endl << endl;
}
