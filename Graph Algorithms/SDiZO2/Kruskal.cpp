#include "stdafx.h"
#include "Kruskal.h"
#include <iostream>
#include <list>
#include "ListGraph.h"


Kruskal::Kruskal()
{
}


Kruskal::~Kruskal()
{
	delete solution;
	while (!edgesPriorityQueue.empty())
		edgesPriorityQueue.pop();
}
// Algorytm dla macierzowej reprezentacji grafu
void Kruskal::RunMatrix(int ** matrix, int numberOfVertexes)
{
	delete solution;
	solutionWeight = 0;
	// Utworzenie listy przechowuj¹cej rozwi¹zanie
	solution = new std::list<Kruskal::edge>();
	// Zmienne pomocnicze
	int tempWeight;
	edge tempEdge;
	// Tablica przechowuj¹ca wierzcho³ki
	vertex *vertexes = new vertex[numberOfVertexes];
	// Inicjalizacja wierzcho³ków 
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		vertexes[currentVertex] = {
		currentVertex,
		&vertexes[currentVertex],
		0
	};
	// Pêtla pobieraj¹ca krawêdzie z macierzy
	for (int currentStartVertex = 0; currentStartVertex < numberOfVertexes; currentStartVertex++)
	{
		for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
		{
			// Pobranie wagi danej krawêdzi
			tempWeight = matrix[currentStartVertex][currentDestinationVertex];
			// Je¿eli krawêdŸ istnieje to zostaje dodana do kolejki priorytetowej
			if (tempWeight != null_value)
			{
				tempEdge.startVertex = currentStartVertex;
				tempEdge.destinationVertex = currentDestinationVertex;
				tempEdge.weight = tempWeight;
				edgesPriorityQueue.push(tempEdge);
			}
		}			
	}
	// Decydowanie czy dodaæ krawêdŸ do drzewa rozpinaj¹cego
	do
	{
		tempEdge = edgesPriorityQueue.top();
		// Sprawdzenie czy nie utworzy siê cykl
		vertex *firstTopVertex = &vertexes[Find(tempEdge.destinationVertex, vertexes)];
		vertex *secondTopVertex = &vertexes[Find(tempEdge.startVertex, vertexes)];
		// Je¿eli wierzcho³ki nale¿¹ do ró¿nych podgrafów to nastêpuje ich po³¹czenie
		if (firstTopVertex->id != secondTopVertex->id)
		{
			Union(firstTopVertex, secondTopVertex, vertexes);
			solution->push_back(tempEdge);
			solutionWeight += tempEdge.weight;
		}
		edgesPriorityQueue.pop();
	} while (!edgesPriorityQueue.empty());
}
// Algorytm dla listowej reprezentacji grafu
void Kruskal::RunList(std::list<ListGraph::edge>* graphList, int numberOfVertexes)
{
	delete solution;
	solutionWeight = 0;
	// Utworzenie listy przechowuj¹cej rozwi¹zanie
	solution = new std::list<Kruskal::edge>();
	// Zmienne pomocnicze
	int tempWeight;
	edge tempEdge;
	// Tablica przechowuj¹ca wierzcho³ki
	vertex *vertexes = new vertex[numberOfVertexes];
	// Inicjalizacja wierzcho³ków
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		vertexes[currentVertex] = {
		currentVertex,
		&vertexes[currentVertex],
		0
	};
	// Pêtla pobieraj¹ca krawêdzie z listy
	for (int currentStartVertex = 0; currentStartVertex < numberOfVertexes; currentStartVertex++)
	{
		for (std::list<ListGraph::edge>::iterator currentEdge = graphList[currentStartVertex].begin(); currentEdge != graphList[currentStartVertex].end(); currentEdge++)
		{
			tempWeight = currentEdge->weight;
			tempEdge.startVertex = currentStartVertex;
			tempEdge.destinationVertex = currentEdge->destinationVertex;
			tempEdge.weight = tempWeight;
			edgesPriorityQueue.push(tempEdge);
		}
	}
	// Decydowanie czy dodaæ krawêdŸ do drzewa rozpinaj¹cego
	do
	{
		tempEdge = edgesPriorityQueue.top();
		// Sprawdzenie czy nie utworzy siê cykl
		vertex *firstTopVertex = &vertexes[Find(tempEdge.destinationVertex, vertexes)];
		vertex *secondTopVertex = &vertexes[Find(tempEdge.startVertex, vertexes)];
		// Je¿eli po³¹czenie wierzcho³ków nie spowoduje cyklu, nastêpuje po³¹czenie
		if (firstTopVertex->id != secondTopVertex->id)
		{
			Union(firstTopVertex, secondTopVertex, vertexes);
			solution->push_back(tempEdge);
			solutionWeight += tempEdge.weight;
		}
		edgesPriorityQueue.pop();
	} while (!edgesPriorityQueue.empty());
}
// Funkcja zwracaj¹ca reprezentanta danego poddrzewa
int Kruskal::Find(int vertex, Kruskal::vertex *vertexes)
{
	if (vertexes[vertex].parent->id == vertex)
		return vertex;
	return Find(vertexes[vertex].parent->id, vertexes);
}
// Funkcja ³¹cz¹ca poddrzewa
void Kruskal::Union(vertex *firstTopVertex, vertex *secondTopVertex, Kruskal::vertex * vertexes)
{
	if (firstTopVertex->rank < secondTopVertex->rank)
		firstTopVertex->parent = secondTopVertex;
	else
		if (firstTopVertex->rank > secondTopVertex->rank)
			secondTopVertex->parent = firstTopVertex;
		else
		{
			secondTopVertex->parent = firstTopVertex;
			firstTopVertex->rank += 1;
		}
}
// Funkcja wyœwietlaj¹ca rozwi¹zanie
bool Kruskal::DisplayMstSolution()
{
	if (solution->empty())
		return false;
	for (Kruskal::edge currentEdge : *solution)
	{
		std::cout << currentEdge.startVertex << " - " << currentEdge.destinationVertex << std::endl;
	}
	std::cout << "WAGA: " << solutionWeight << std::endl;
	return true;
}
