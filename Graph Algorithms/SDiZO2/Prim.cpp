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

// Funkcja wykonuj�ca algorytm dla macierzowej reprezentacji grafu
void Prim::RunMatrix(int **matrix, int numberOfVertexes)
{
	delete solution;
	solutionWeight = 0;
	// Utworzenie listy przechowuj�cej rozwi�zanie
	solution = new list<Prim::edge>;
	// Tablica przechowuj�ca informacje czy dany wierzcho�ek by� ju� odwiedzony
	bool *visitedVertexes = new bool[numberOfVertexes];
	// Zmienne pomocnicze
	edge tempEdge;
	int tempWeight;
	// Wierzcho�ek pocz�tkowy
	int currentStartVertex = 0;
	// Inicjalizacja tablicy
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		visitedVertexes[currentVertex] = false;
	// G��wna p�tla wykonuj�ca algorytm
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		// Oznaczamy wierzcho�ek jako oznaczony
		visitedVertexes[currentStartVertex] = true;
		// Przegl�danie wierzcho�k�w
		for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
		{			
			tempWeight = matrix[currentStartVertex][currentDestinationVertex];
			// Je�eli kraw�d� istnieje i wierzcho�ek do kt�rego prowadzi nie by� sprawdzany to jest ona dodana do kolejki priorytetowej
			if (visitedVertexes[currentDestinationVertex] == false && tempWeight != null_value)
			{
				tempEdge.startVertex = currentStartVertex;
				tempEdge.destinationVertex = currentDestinationVertex;
				tempEdge.weight = tempWeight;
				edgesPriorityQueue.push(tempEdge);
			}
		}
		// Przegl�danie kraw�dzi w kolejce i dodawanie ich do rozwi�zania je�eli nie prowadz� do ju� odwiedzonych wierzcho�k�w
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
// Funkcja wykonuj�ca algorytm dla listowej reprezentacji grafu
void Prim::RunList(list<ListGraph::edge> *graphList, int numberOfVertexes)
{
	delete solution;
	solutionWeight = 0;
	// Utworzenie listy przechowuj�cej rozwi�zanie
	solution = new list<Prim::edge>;
	// Tablica przechowuj�ca informacje czy dany wierzcho�ek by� ju� odwiedzony
	bool *visitedVertexes = new bool[numberOfVertexes];
	// Zmienne pomocnicze
	edge tempEdge;
	// Wierzcho�ek pocz�tkowy
	int currentStartVertex = 0;
	// Inicjalizacja tablicy
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		visitedVertexes[currentVertex] = false;
	// G��wna p�tla wykonuj�ca algorytm
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
	{
		// Oznaczamy wierzcho�ek jako oznaczony
		visitedVertexes[currentStartVertex] = true;
		// Przegl�danie wierzcho�k�w
		for (list<ListGraph::edge>::iterator currentEdge = graphList[currentStartVertex].begin(); currentEdge != graphList[currentStartVertex].end(); currentEdge++)
		{
			// Je�eli wierzcho�ek do kt�rego prowadzi dana kraw�d� nie by� sprawdzany to jest ona dodana do kolejki priorytetowej
			if (visitedVertexes[currentEdge->destinationVertex] == false)
			{
				tempEdge.startVertex = currentStartVertex;
				tempEdge.destinationVertex = currentEdge->destinationVertex;
				tempEdge.weight = currentEdge->weight;
				edgesPriorityQueue.push(tempEdge);
			}
		}
		// Przegl�danie kraw�dzi w kolejce i dodawanie ich do rozwi�zania je�eli nie prowadz� do ju� odwiedzonych wierzcho�k�w
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
// Funkcja wy�wietlaj�ca rozwi�zanie
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


