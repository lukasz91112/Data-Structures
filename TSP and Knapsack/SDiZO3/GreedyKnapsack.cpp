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

// Funkcja wykonuj�ca algorytm zach�anny po g�sto�ci
void GreedyKnapsack::RunByDensity(Knapsack * knapsack)
{
	// Inicjalizacja kolejki
	priority_queue < Knapsack::item, vector < Knapsack::item >,compareItemByDensity > *itemsPriorityQueue = new priority_queue < Knapsack::item, vector < Knapsack::item >, compareItemByDensity >();
	// Inicjalizacja listy przechowuj�cej rozwi�zanie
	list <Knapsack::item> *solution = new list<Knapsack::item>();
	// Pobranie danych o problemie plecakowym
	vector<Knapsack::item> *vectorOfItems = knapsack->GetVector();
	int numberOfItems = knapsack->GetNumberOfItems();
	int capacity = knapsack->GetCapacity();
	// Zmienna pomocnicza - obecna waga
	int currentWeight = 0;
	// Zmienna pomocnicza - obecnie analizowany przedmiot
	Knapsack::item tempItem;

	// Za�adowanie przedmiot�w do kolejki
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
		itemsPriorityQueue->push((*vectorOfItems)[currentItem]);

	// G��wna p�tla wykonuj�ca algorytm
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
	{
		// Pobranie przedmiotu z wierzchu kolejki
		tempItem = itemsPriorityQueue->top();
		// Je�eli dany przedmiot si� mie�ci to nast�puje dodanie go do rozwi�zania
		if (tempItem.weight + currentWeight <= capacity)
		{
			solution->push_back(tempItem);
			currentWeight += tempItem.weight;
		}
		// Je�eli plecak jest pe�ny to nast�puje przerwanie algorytmu
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

// Funkcja wykonuj�ca algorytm zach�anny po warto�ci
void GreedyKnapsack::RunByValue(Knapsack * knapsack)
{
	// Inicjalizacja kolejki
	priority_queue < Knapsack::item, vector < Knapsack::item >, compareItemByValue > *itemsPriorityQueue = new priority_queue < Knapsack::item, vector < Knapsack::item >, compareItemByValue >();
	// Inicjalizacja listy przechowuj�cej rozwi�zanie
	list <Knapsack::item> *solution = new list<Knapsack::item>();
	// Pobranie danych o problemie plecakowym
	vector<Knapsack::item> *vectorOfItems = knapsack->GetVector();
	int numberOfItems = knapsack->GetNumberOfItems();
	int capacity = knapsack->GetCapacity();
	// Zmienna pomocnicza - obecna waga
	int currentWeight = 0;
	// Zmienna pomocnicza - obecnie analizowany przedmiot
	Knapsack::item tempItem;
	// Za�adowanie przedmiot�w do kolejki

	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
		itemsPriorityQueue->push((*vectorOfItems)[currentItem]);

	// G��wna p�tla wykonuj�ca algorytm
	for (int currentItem = 0; currentItem < numberOfItems; currentItem++)
	{
		// Pobranie przedmiotu z wierzchu kolejki
		tempItem = itemsPriorityQueue->top();
		// Je�eli przedmiot si� mie�ci to zostaje dodany do rozwi�zania
		if (tempItem.weight + currentWeight <= capacity)
		{
			solution->push_back(tempItem);
			currentWeight += tempItem.weight;
		}
		// Je�eli plecak jest pe�ny to nast�puje przerwanie algorytmu
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

// Funkcja wy�wietlaj�ca rozwi�zanie
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
