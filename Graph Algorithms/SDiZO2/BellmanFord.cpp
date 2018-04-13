#include "stdafx.h"
#include "BellmanFord.h"
#include <stack>
#include <iostream>

using namespace std;

BellmanFord::BellmanFord()
{
}


BellmanFord::~BellmanFord()
{
	delete[] path;
	delete[] cost;
}
// Funkcja wykonuj�ca algorytm dla macierzowej reprezentacji grafu
bool BellmanFord::RunMatrix(int ** matrix, int numberOfVertexes, int startVertex)
{
	// Tablice przechowuj�ce wynik algorytmu
	path = new int[numberOfVertexes];
	cost = new int[numberOfVertexes];
	// Pobranie warto�ci grafu
	this->startVertex = startVertex;
	this->numberOfVertexes = numberOfVertexes;
	// Zmienna sprawdzaj�ca czy nast�pi�a zmiana w trakcie jednego przej�cia po grafie
	bool isThereAnyChange = false;
	int tempWeight;
	// Obecny wierzcho�ek z kt�rego wychodzi dana kraw�d�
	int currentStartVertex = startVertex;
	// Inicjalizacja tablic
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		path[currentVertex] = -1;
		cost[currentVertex] = null_value;
	}
	path[startVertex] = startVertex;
	cost[startVertex] = 0;
	// P�tla g��wna wykonuj�ca algorytm
	for (int iterration = 0; iterration < numberOfVertexes; iterration++)
	{
		// Na pocz�tku zak�adamy �e nic si� nie zmieni
		isThereAnyChange = false;
		// P�tla przeszukuj�ca wierzcho�ki
		for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		{
			for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
			{
				// Pobranie wagi rozpatrywanej kraw�dzi
				tempWeight = matrix[currentStartVertex][currentDestinationVertex];
				// Je�eli kraw�d� istnieje to rozpatrywana jest relaksacja
				if (tempWeight != null_value)
				{
					// Je�eli nast�pi poprawa to nast�puje zmiana warto�ci w tablicach oraz oznaczenie �e mia�a miejsce jaka� zmiana
					if ((cost[currentStartVertex] + tempWeight < cost[currentDestinationVertex]) && cost[currentStartVertex] != null_value)
					{
						cost[currentDestinationVertex] = cost[currentStartVertex] + tempWeight;
						path[currentDestinationVertex] = currentStartVertex;
						isThereAnyChange = true;
					}
				}
			}
			// Zmiana obecnie rozpatrywanego wierzcho�ka
			if (currentStartVertex == numberOfVertexes - 1)
				currentStartVertex = 0;
			else currentStartVertex++;
		}
		// Je�eli nie by�o �adnej zmiany to koniec funkcji
		if (!isThereAnyChange)
			return true;
		// Je�eli zmiana by�a a nie powinno jej by� to wyst�pi� cykl ujemny
		if (isThereAnyChange && iterration == numberOfVertexes - 1)
			return false;
	}
}
// Funkcja wykonuj�ca algorytm dla listowej reprezentacji grafu
bool BellmanFord::RunList(std::list<ListGraph::edge>* listGraph, int numberOfVertexes, int startVertex)
{
	// Tablice przechowuj�ce wynik algorytmu
	path = new int[numberOfVertexes];
	cost = new int[numberOfVertexes];
	// Pobranie warto�ci grafu
	this->startVertex = startVertex;
	this->numberOfVertexes = numberOfVertexes;
	// Zmienna sprawdzaj�ca czy nast�pi�a zmiana w trakcie jednego przej�cia po grafie
	bool isThereAnyChange = false;
	int tempWeight;
	// Obecny wierzcho�ek z kt�rego wychodzi dana kraw�d�
	int currentStartVertex = startVertex;
	// Inicjalizacja tablic
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		path[currentVertex] = -1;
		cost[currentVertex] = null_value;
	}
	path[startVertex] = startVertex;
	cost[startVertex] = 0;
	// P�tla g��wna wykonuj�ca algorytm
	for (int iterration = 0; iterration < numberOfVertexes; iterration++)
	{
		// Na pocz�tku zak�adamy �e nic si� nie zmieni
		isThereAnyChange = false;
		// P�tla przeszukuj�ca wierzcho�ki
		for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		{
			for (list<ListGraph::edge>::iterator currentEdge = listGraph[currentStartVertex].begin(); currentEdge != listGraph[currentStartVertex].end(); currentEdge++)
			{
				// Pobranie wagi rozpatrywanej kraw�dzi
				tempWeight = currentEdge->weight;
				if (tempWeight != null_value)
				{
					// Je�eli nast�pi poprawa to nast�puje zmiana warto�ci w tablicach oraz oznaczenie �e mia�a miejsce jaka� zmiana
					if ((cost[currentStartVertex] + tempWeight < cost[currentEdge->destinationVertex]) && cost[currentStartVertex] != null_value)
					{
						cost[currentEdge->destinationVertex] = cost[currentStartVertex] + tempWeight;
						path[currentEdge->destinationVertex] = currentStartVertex;
						isThereAnyChange = true;
					}
				}
			}
			// Zmiana obecnie rozpatrywanego wierzcho�ka
			if (currentStartVertex == numberOfVertexes - 1)
				currentStartVertex = 0;
			else currentStartVertex++;
		}
		// Je�eli nie by�o �adnej zmiany to koniec funkcji
		if (!isThereAnyChange)
			return true;
		// Je�eli zmiana by�a a nie powinno jej by� to wyst�pi� cykl ujemny
		if (isThereAnyChange && iterration == numberOfVertexes)
			return false;
	}
}
// Funkcja wy�wietlaj�ca rozwi�zanie algorytmu
void BellmanFord::DisplaySolution()
{	
	int tempParent;
	stack<int> *tempPath = new stack<int>;
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		cout << "Wierzcholek " << currentVertex << "  Dystans : " << cost[currentVertex] << "  Sciezka : ";
		tempPath->push(currentVertex);
		tempParent = currentVertex;
		while (tempParent != startVertex)
		{
			tempParent = path[tempParent];
			tempPath->push(tempParent);
		}
		if (tempPath->top() != startVertex)
			tempPath->push(startVertex);

		while (!tempPath->empty())
		{
			cout << tempPath->top() << "  ";
			tempPath->pop();
		}
		cout << endl;
	}
	delete tempPath;
}
