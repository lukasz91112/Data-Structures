#pragma once
#include <string>
#include <list>
#include "ListGraph.h"

class BellmanFord
{
public:
	BellmanFord();
	~BellmanFord();
	const int null_value = INT32_MAX;
	int *path;
	int *cost;
	int startVertex;
	int numberOfVertexes;
	bool RunMatrix(int **matrix, int numberOfVertexes, int startVertex);
	bool RunList(std::list<ListGraph::edge> *listGraph, int numberOfVertexes, int startVertex);
	void DisplaySolution();
};

