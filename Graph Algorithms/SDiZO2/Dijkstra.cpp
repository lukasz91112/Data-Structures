#include "stdafx.h"
#include "Dijkstra.h"
#include <list>
#include <iostream>
#include <stack>

using namespace std;

Dijkstra::Dijkstra()
{
}


Dijkstra::~Dijkstra()
{
	delete[] path;
	delete[] cost;
}
// Algorytm Djikstry dla macierzowej reprezentacji grafu
void Dijkstra::RunMatrix(int ** matrix, int numberOfVertexes, int startVertex)
{
	// Pobranie informacji o grafie
	this->startVertex = startVertex;
	this->numberOfVertexes = numberOfVertexes;
	// Tablica m�wi�ca o tym kt�ry wierzcho�ek by� ju� odwiedzony
	bool *visitedVertexes = new bool[numberOfVertexes];
	// Obecny wierzcho�ek z kt�rego wychodzi kraw�d� - domy�lnie, wierzcho�ek pocz�tkowy grafu
	int currentStartVertex = startVertex;
	// Zmienna pomocnicza pomagaj�ca wyliczy� wierzcho�ek o minimalnym koszcie
	int tempMinimalCost = 0;
	// Zmienne pomocnicze
	int currentWeight;
	int tempCost;
	// Tablice przechowuj�ce wynik dzia�ania algorytmu
	path = new int[numberOfVertexes];
	cost = new int[numberOfVertexes];
	// P�tla inicjuj�ca tablice przechowuj�ce wynik
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		visitedVertexes[currentVertex] = false;
		path[currentVertex] = null_value;
		cost[currentVertex] = null_value;
	}
	// Przypisanie warto�ci pierwszemu wierzcho�kowi
	cost[currentStartVertex] = 0;
	path[currentStartVertex] = currentStartVertex;
	// P�tla g��wna wykonuj�ca algorytm
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		tempMinimalCost = null_value;
		// Oznaczamy obecnie sprawdzany wierzcho�ek jako odwiedzony
		visitedVertexes[currentStartVertex] = true;
		// Sprawdzanie s�siad�w wierzcho�ka
		for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
		{
			// Pobranie wagi obecnie sprawdzanej kraw�dzi
			currentWeight = matrix[currentStartVertex][currentDestinationVertex];
			// Je�eli kraw�d� istnieje to sprawdzane jest czy poprawi ona koszt rozpatrywanego wierzcho�ka
			if (currentWeight != null_value)
			{
				// Koszt doj�cia do danego wierzcho�ka z obecnego wierzcho�ka
				tempCost = cost[currentStartVertex] + currentWeight;
				// Je�eli koszt z obecnego wierzcho�ka jest mniejszy to nast�puje poprawa
				if (cost[currentDestinationVertex] > tempCost)
				{
					cost[currentDestinationVertex] = tempCost;
					path[currentDestinationVertex] = currentStartVertex;
				}
			}
		}
		// Wyszukiwanie "najta�szego" wierzcho�ka w�r�d s�siad�w - to on b�dzie nast�pny sprawdzany
		for (int currentSearchedVertex = 0; currentSearchedVertex < numberOfVertexes; currentSearchedVertex++)
			if ((cost[currentSearchedVertex] < tempMinimalCost) && (visitedVertexes[currentSearchedVertex] == false))
			{
				currentStartVertex = currentSearchedVertex;
				tempMinimalCost = cost[currentSearchedVertex];
			}
	}
}
// Algorytm Djikstry dla listowej reprezentacji grafu
void Dijkstra::RunList(std::list<ListGraph::edge> *listGraph, int numberOfVertexes, int startVertex)
{
	// Pobranie informacji o grafie
	this->startVertex = startVertex;
	this->numberOfVertexes = numberOfVertexes;
	// Tablica m�wi�ca o tym kt�ry wierzcho�ek by� ju� odwiedzony
	bool *visitedVertexes = new bool[numberOfVertexes];
	// Obecny wierzcho�ek z kt�rego wychodzi kraw�d� - domy�lnie, wierzcho�ek pocz�tkowy grafu
	int currentStartVertex = startVertex;
	// Zmienna pomocnicza pomagaj�ca wyliczy� wierzcho�ek o minimalnym koszcie
	int tempMinimalCost = 0;
	// Zmienne pomocnicze
	int currentWeight;
	int currentDestinationVertex;
	int tempCost;	
	// Tablice przechowuj�ce wynik dzia�ania algorytmu
	path = new int[numberOfVertexes];
	cost = new int[numberOfVertexes];
	// P�tla inicjuj�ca tablice przechowuj�ce wynik
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		visitedVertexes[currentVertex] = false;
		path[currentVertex] = null_value;
		cost[currentVertex] = null_value;
	}
	// Przypisanie warto�ci pierwszemu wierzcho�kowi
	cost[currentStartVertex] = 0;
	path[currentStartVertex] = currentStartVertex;
	// P�tla g��wna wykonuj�ca algorytm
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		tempMinimalCost = null_value;
		// Oznaczamy obecnie sprawdzany wierzcho�ek jako odwiedzony
		visitedVertexes[currentStartVertex] = true;
		// Sprawdzanie s�siad�w wierzcho�ka
		for (std::list<ListGraph::edge>::iterator currentEdge = listGraph[currentStartVertex].begin(); currentEdge != listGraph[currentStartVertex].end(); currentEdge++)
		{
			// Pobranie wagi obecnie sprawdzanej kraw�dzi
			currentWeight = currentEdge->weight;
			// Pobranie wierzcho�ka do kt�rego prowadzi dana kraw�d�
			currentDestinationVertex = currentEdge->destinationVertex;
			// Wyliczenie kosztu z obecnego wierzcho�ka
			tempCost = cost[currentStartVertex] + currentWeight;
			// Je�eli koszt jest lepszy nast�puje poprawa
			if (cost[currentDestinationVertex] > tempCost)
			{
				cost[currentDestinationVertex] = tempCost;
				path[currentDestinationVertex] = currentStartVertex;
			}
		}
		// Nast�puje wyszukiwanie w�r�d s�siad�w wierzcho�ka o najmniejszej wadze - ten bedzie nast�pny sprawdzany
		for (int currentSearchedVertex = 0; currentSearchedVertex < numberOfVertexes; currentSearchedVertex++)
			if ((cost[currentSearchedVertex] < tempMinimalCost) && (visitedVertexes[currentSearchedVertex] == false))
			{
				currentStartVertex = currentSearchedVertex;
				tempMinimalCost = cost[currentSearchedVertex];
			}
	}
}
// Funkcja wy�wietlaj�ca rozwi�zanie
void Dijkstra::DisplaySolution()
{
	int tempParent;
	stack<int> tempPath;
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		cout << "Wierzcholek " << currentVertex << "  Dystans : " << cost[currentVertex] << "  Sciezka : ";
		tempPath.push(currentVertex);
		tempParent = currentVertex;
		while (tempParent != startVertex)
		{
			tempParent = path[tempParent];
			tempPath.push(tempParent);
		}
		if (tempPath.top() != startVertex)
			tempPath.push(startVertex);

		while (!tempPath.empty())
		{
			cout << tempPath.top() << "  ";
			tempPath.pop();
		}
		cout << endl;
	}
}
