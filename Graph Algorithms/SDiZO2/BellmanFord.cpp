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
// Funkcja wykonuj¹ca algorytm dla macierzowej reprezentacji grafu
bool BellmanFord::RunMatrix(int ** matrix, int numberOfVertexes, int startVertex)
{
	// Tablice przechowuj¹ce wynik algorytmu
	path = new int[numberOfVertexes];
	cost = new int[numberOfVertexes];
	// Pobranie wartoœci grafu
	this->startVertex = startVertex;
	this->numberOfVertexes = numberOfVertexes;
	// Zmienna sprawdzaj¹ca czy nast¹pi³a zmiana w trakcie jednego przejœcia po grafie
	bool isThereAnyChange = false;
	int tempWeight;
	// Obecny wierzcho³ek z którego wychodzi dana krawêdŸ
	int currentStartVertex = startVertex;
	// Inicjalizacja tablic
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		path[currentVertex] = -1;
		cost[currentVertex] = null_value;
	}
	path[startVertex] = startVertex;
	cost[startVertex] = 0;
	// Pêtla g³ówna wykonuj¹ca algorytm
	for (int iterration = 0; iterration < numberOfVertexes; iterration++)
	{
		// Na pocz¹tku zak³adamy ¿e nic siê nie zmieni
		isThereAnyChange = false;
		// Pêtla przeszukuj¹ca wierzcho³ki
		for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		{
			for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
			{
				// Pobranie wagi rozpatrywanej krawêdzi
				tempWeight = matrix[currentStartVertex][currentDestinationVertex];
				// Je¿eli krawêdŸ istnieje to rozpatrywana jest relaksacja
				if (tempWeight != null_value)
				{
					// Je¿eli nast¹pi poprawa to nastêpuje zmiana wartoœci w tablicach oraz oznaczenie ¿e mia³a miejsce jakaœ zmiana
					if ((cost[currentStartVertex] + tempWeight < cost[currentDestinationVertex]) && cost[currentStartVertex] != null_value)
					{
						cost[currentDestinationVertex] = cost[currentStartVertex] + tempWeight;
						path[currentDestinationVertex] = currentStartVertex;
						isThereAnyChange = true;
					}
				}
			}
			// Zmiana obecnie rozpatrywanego wierzcho³ka
			if (currentStartVertex == numberOfVertexes - 1)
				currentStartVertex = 0;
			else currentStartVertex++;
		}
		// Je¿eli nie by³o ¿adnej zmiany to koniec funkcji
		if (!isThereAnyChange)
			return true;
		// Je¿eli zmiana by³a a nie powinno jej byæ to wyst¹pi³ cykl ujemny
		if (isThereAnyChange && iterration == numberOfVertexes - 1)
			return false;
	}
}
// Funkcja wykonuj¹ca algorytm dla listowej reprezentacji grafu
bool BellmanFord::RunList(std::list<ListGraph::edge>* listGraph, int numberOfVertexes, int startVertex)
{
	// Tablice przechowuj¹ce wynik algorytmu
	path = new int[numberOfVertexes];
	cost = new int[numberOfVertexes];
	// Pobranie wartoœci grafu
	this->startVertex = startVertex;
	this->numberOfVertexes = numberOfVertexes;
	// Zmienna sprawdzaj¹ca czy nast¹pi³a zmiana w trakcie jednego przejœcia po grafie
	bool isThereAnyChange = false;
	int tempWeight;
	// Obecny wierzcho³ek z którego wychodzi dana krawêdŸ
	int currentStartVertex = startVertex;
	// Inicjalizacja tablic
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		path[currentVertex] = -1;
		cost[currentVertex] = null_value;
	}
	path[startVertex] = startVertex;
	cost[startVertex] = 0;
	// Pêtla g³ówna wykonuj¹ca algorytm
	for (int iterration = 0; iterration < numberOfVertexes; iterration++)
	{
		// Na pocz¹tku zak³adamy ¿e nic siê nie zmieni
		isThereAnyChange = false;
		// Pêtla przeszukuj¹ca wierzcho³ki
		for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		{
			for (list<ListGraph::edge>::iterator currentEdge = listGraph[currentStartVertex].begin(); currentEdge != listGraph[currentStartVertex].end(); currentEdge++)
			{
				// Pobranie wagi rozpatrywanej krawêdzi
				tempWeight = currentEdge->weight;
				if (tempWeight != null_value)
				{
					// Je¿eli nast¹pi poprawa to nastêpuje zmiana wartoœci w tablicach oraz oznaczenie ¿e mia³a miejsce jakaœ zmiana
					if ((cost[currentStartVertex] + tempWeight < cost[currentEdge->destinationVertex]) && cost[currentStartVertex] != null_value)
					{
						cost[currentEdge->destinationVertex] = cost[currentStartVertex] + tempWeight;
						path[currentEdge->destinationVertex] = currentStartVertex;
						isThereAnyChange = true;
					}
				}
			}
			// Zmiana obecnie rozpatrywanego wierzcho³ka
			if (currentStartVertex == numberOfVertexes - 1)
				currentStartVertex = 0;
			else currentStartVertex++;
		}
		// Je¿eli nie by³o ¿adnej zmiany to koniec funkcji
		if (!isThereAnyChange)
			return true;
		// Je¿eli zmiana by³a a nie powinno jej byæ to wyst¹pi³ cykl ujemny
		if (isThereAnyChange && iterration == numberOfVertexes)
			return false;
	}
}
// Funkcja wyœwietlaj¹ca rozwi¹zanie algorytmu
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
