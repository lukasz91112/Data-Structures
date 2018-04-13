#include "stdafx.h"
#include "Prim.h"
#include <iostream>
#include <list>
#include "ListGraph.h"

using namespace std;

Prim::Prim()
{
}


Prim::~Prim()
{
	while (!edgesPriorityQueue.empty())
		edgesPriorityQueue.pop();
	delete solution;
}

// Funkcja wykonuj¹ca algorytm dla macierzowej reprezentacji grafu
void Prim::RunMatrix(int **matrix, int numberOfVertexes)
{
	delete solution;
	solutionWeight = 0;
	// Utworzenie listy przechowuj¹cej rozwi¹zanie
	solution = new list<Prim::edge>;
	// Tablica przechowuj¹ca informacje czy dany wierzcho³ek by³ ju¿ odwiedzony
	bool *visitedVertexes = new bool[numberOfVertexes];
	// Zmienne pomocnicze
	edge tempEdge;
	int tempWeight;
	// Wierzcho³ek pocz¹tkowy
	int currentStartVertex = 0;
	// Inicjalizacja tablicy
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		visitedVertexes[currentVertex] = false;
	// G³ówna pêtla wykonuj¹ca algorytm
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		// Oznaczamy wierzcho³ek jako oznaczony
		visitedVertexes[currentStartVertex] = true;
		// Przegl¹danie wierzcho³ków
		for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
		{			
			tempWeight = matrix[currentStartVertex][currentDestinationVertex];
			// Je¿eli krawêdŸ istnieje i wierzcho³ek do którego prowadzi nie by³ sprawdzany to jest ona dodana do kolejki priorytetowej
			if (visitedVertexes[currentDestinationVertex] == false && tempWeight != null_value)
			{
				tempEdge.startVertex = currentStartVertex;
				tempEdge.destinationVertex = currentDestinationVertex;
				tempEdge.weight = tempWeight;
				edgesPriorityQueue.push(tempEdge);
			}
		}
		// Przegl¹danie krawêdzi w kolejce i dodawanie ich do rozwi¹zania je¿eli nie prowadz¹ do ju¿ odwiedzonych wierzcho³ków
		if (!edgesPriorityQueue.empty())
			tempEdge = edgesPriorityQueue.top();
		while (visitedVertexes[tempEdge.destinationVertex] == true && !edgesPriorityQueue.empty())
		{

			edgesPriorityQueue.pop();
			if (!edgesPriorityQueue.empty())
				tempEdge = edgesPriorityQueue.top();
		}
		if (!edgesPriorityQueue.empty())
		{
			edgesPriorityQueue.pop();
			solution->push_back(tempEdge);
			solutionWeight += tempEdge.weight;
			currentStartVertex = tempEdge.destinationVertex;
		}
	}
}
// Funkcja wykonuj¹ca algorytm dla listowej reprezentacji grafu
void Prim::RunList(list<ListGraph::edge> *graphList, int numberOfVertexes)
{
	delete solution;
	solutionWeight = 0;
	// Utworzenie listy przechowuj¹cej rozwi¹zanie
	solution = new list<Prim::edge>;
	// Tablica przechowuj¹ca informacje czy dany wierzcho³ek by³ ju¿ odwiedzony
	bool *visitedVertexes = new bool[numberOfVertexes];
	// Zmienne pomocnicze
	edge tempEdge;
	// Wierzcho³ek pocz¹tkowy
	int currentStartVertex = 0;
	// Inicjalizacja tablicy
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		visitedVertexes[currentVertex] = false;
	// G³ówna pêtla wykonuj¹ca algorytm
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		// Oznaczamy wierzcho³ek jako oznaczony
		visitedVertexes[currentStartVertex] = true;
		// Przegl¹danie wierzcho³ków
		for (list<ListGraph::edge>::iterator currentEdge = graphList[currentStartVertex].begin(); currentEdge != graphList[currentStartVertex].end(); currentEdge++)
		{
			// Je¿eli wierzcho³ek do którego prowadzi dana krawêdŸ nie by³ sprawdzany to jest ona dodana do kolejki priorytetowej
			if (visitedVertexes[currentEdge->destinationVertex] == false)
			{
				tempEdge.startVertex = currentStartVertex;
				tempEdge.destinationVertex = currentEdge->destinationVertex;
				tempEdge.weight = currentEdge->weight;
				edgesPriorityQueue.push(tempEdge);
			}
		}
		// Przegl¹danie krawêdzi w kolejce i dodawanie ich do rozwi¹zania je¿eli nie prowadz¹ do ju¿ odwiedzonych wierzcho³ków
		if (!edgesPriorityQueue.empty())
			tempEdge = edgesPriorityQueue.top();
		while (visitedVertexes[tempEdge.destinationVertex] == true && !edgesPriorityQueue.empty())
		{
			edgesPriorityQueue.pop();
			if (!edgesPriorityQueue.empty())
				tempEdge = edgesPriorityQueue.top();
		}
		if (!edgesPriorityQueue.empty())
		{
			edgesPriorityQueue.pop();
			solution->push_back(tempEdge);
			solutionWeight += tempEdge.weight;
			currentStartVertex = tempEdge.destinationVertex;
		}
	}
}
// Funkcja wyœwietlaj¹ca rozwi¹zanie
bool Prim::DisplayMstSolution()
{
	if (solution->empty())
		return false;
	for (Prim::edge currentEdge : *solution)
	{
		std::cout << currentEdge.startVertex << " - " << currentEdge.destinationVertex << std::endl;
	}
	cout << "WAGA: " << solutionWeight << endl;
	return true;
}


