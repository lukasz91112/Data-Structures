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
	// Tablica mówi¹ca o tym który wierzcho³ek by³ ju¿ odwiedzony
	bool *visitedVertexes = new bool[numberOfVertexes];
	// Obecny wierzcho³ek z którego wychodzi krawêdŸ - domyœlnie, wierzcho³ek pocz¹tkowy grafu
	int currentStartVertex = startVertex;
	// Zmienna pomocnicza pomagaj¹ca wyliczyæ wierzcho³ek o minimalnym koszcie
	int tempMinimalCost = 0;
	// Zmienne pomocnicze
	int currentWeight;
	int tempCost;
	// Tablice przechowuj¹ce wynik dzia³ania algorytmu
	path = new int[numberOfVertexes];
	cost = new int[numberOfVertexes];
	// Pêtla inicjuj¹ca tablice przechowuj¹ce wynik
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		visitedVertexes[currentVertex] = false;
		path[currentVertex] = null_value;
		cost[currentVertex] = null_value;
	}
	// Przypisanie wartoœci pierwszemu wierzcho³kowi
	cost[currentStartVertex] = 0;
	path[currentStartVertex] = currentStartVertex;
	// Pêtla g³ówna wykonuj¹ca algorytm
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		tempMinimalCost = null_value;
		// Oznaczamy obecnie sprawdzany wierzcho³ek jako odwiedzony
		visitedVertexes[currentStartVertex] = true;
		// Sprawdzanie s¹siadów wierzcho³ka
		for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
		{
			// Pobranie wagi obecnie sprawdzanej krawêdzi
			currentWeight = matrix[currentStartVertex][currentDestinationVertex];
			// Je¿eli krawêdŸ istnieje to sprawdzane jest czy poprawi ona koszt rozpatrywanego wierzcho³ka
			if (currentWeight != null_value)
			{
				// Koszt dojœcia do danego wierzcho³ka z obecnego wierzcho³ka
				tempCost = cost[currentStartVertex] + currentWeight;
				// Je¿eli koszt z obecnego wierzcho³ka jest mniejszy to nastêpuje poprawa
				if (cost[currentDestinationVertex] > tempCost)
				{
					cost[currentDestinationVertex] = tempCost;
					path[currentDestinationVertex] = currentStartVertex;
				}
			}
		}
		// Wyszukiwanie "najtañszego" wierzcho³ka wœród s¹siadów - to on bêdzie nastêpny sprawdzany
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
	// Tablica mówi¹ca o tym który wierzcho³ek by³ ju¿ odwiedzony
	bool *visitedVertexes = new bool[numberOfVertexes];
	// Obecny wierzcho³ek z którego wychodzi krawêdŸ - domyœlnie, wierzcho³ek pocz¹tkowy grafu
	int currentStartVertex = startVertex;
	// Zmienna pomocnicza pomagaj¹ca wyliczyæ wierzcho³ek o minimalnym koszcie
	int tempMinimalCost = 0;
	// Zmienne pomocnicze
	int currentWeight;
	int currentDestinationVertex;
	int tempCost;	
	// Tablice przechowuj¹ce wynik dzia³ania algorytmu
	path = new int[numberOfVertexes];
	cost = new int[numberOfVertexes];
	// Pêtla inicjuj¹ca tablice przechowuj¹ce wynik
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		visitedVertexes[currentVertex] = false;
		path[currentVertex] = null_value;
		cost[currentVertex] = null_value;
	}
	// Przypisanie wartoœci pierwszemu wierzcho³kowi
	cost[currentStartVertex] = 0;
	path[currentStartVertex] = currentStartVertex;
	// Pêtla g³ówna wykonuj¹ca algorytm
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		tempMinimalCost = null_value;
		// Oznaczamy obecnie sprawdzany wierzcho³ek jako odwiedzony
		visitedVertexes[currentStartVertex] = true;
		// Sprawdzanie s¹siadów wierzcho³ka
		for (std::list<ListGraph::edge>::iterator currentEdge = listGraph[currentStartVertex].begin(); currentEdge != listGraph[currentStartVertex].end(); currentEdge++)
		{
			// Pobranie wagi obecnie sprawdzanej krawêdzi
			currentWeight = currentEdge->weight;
			// Pobranie wierzcho³ka do którego prowadzi dana krawêdŸ
			currentDestinationVertex = currentEdge->destinationVertex;
			// Wyliczenie kosztu z obecnego wierzcho³ka
			tempCost = cost[currentStartVertex] + currentWeight;
			// Je¿eli koszt jest lepszy nastêpuje poprawa
			if (cost[currentDestinationVertex] > tempCost)
			{
				cost[currentDestinationVertex] = tempCost;
				path[currentDestinationVertex] = currentStartVertex;
			}
		}
		// Nastêpuje wyszukiwanie wœród s¹siadów wierzcho³ka o najmniejszej wadze - ten bedzie nastêpny sprawdzany
		for (int currentSearchedVertex = 0; currentSearchedVertex < numberOfVertexes; currentSearchedVertex++)
			if ((cost[currentSearchedVertex] < tempMinimalCost) && (visitedVertexes[currentSearchedVertex] == false))
			{
				currentStartVertex = currentSearchedVertex;
				tempMinimalCost = cost[currentSearchedVertex];
			}
	}
}
// Funkcja wyœwietlaj¹ca rozwi¹zanie
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
