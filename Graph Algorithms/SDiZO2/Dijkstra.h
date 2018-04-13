#pragma once
#include <list>
#include "ListGraph.h"
class Dijkstra
{
public:
	Dijkstra();
	~Dijkstra();
	const int null_value = INT32_MAX;
	int *path;
	int *cost;
	int numberOfVertexes;
	int startVertex;
	void RunMatrix(int **matrix, int numberOfVertexes, int startVertex);
	void RunList(std::list<ListGraph::edge> *listGraph, int numberOfVertexes, int startVertex);
	void DisplaySolution();
};

