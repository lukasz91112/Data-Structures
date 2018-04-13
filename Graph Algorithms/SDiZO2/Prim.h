#pragma once
#include <list>
#include <queue>
#include <conio.h>
#include <iostream>
#include "ListGraph.h"
class Prim
{
public:
	Prim();
	~Prim();
	const int null_value = INT32_MAX;
	struct edge;
	void  RunMatrix(int **newMatrix, int numberOfVertexes);
	void RunList(std::list<ListGraph::edge> *graphList, int numberOfVertexes);
	std::list<edge> *solution;
	bool DisplayMstSolution();
	int solutionWeight = 0;
	struct compareVertexes;
	struct edge
	{
		int startVertex;
		int destinationVertex;
		int weight;
	};

	struct compareEdges
	{
		bool operator ()(const edge firstEdge, const edge secondEdge)
		{			
			return firstEdge.weight > secondEdge.weight;
		}
	};
	std::priority_queue < edge, std::vector < edge >, compareEdges > edgesPriorityQueue;
	
	
};

