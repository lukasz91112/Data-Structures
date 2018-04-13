#pragma once
#include <queue>
#include <list>
#include "ListGraph.h"
class Kruskal
{
public:
	Kruskal();
	~Kruskal();
	const int null_value = INT32_MAX;
	int solutionWeight = 0;
	struct vertex
	{
		int id;
		vertex *parent;
		int rank;
	};
	void RunMatrix(int **matrix, int numberOfVertexes);
	void RunList(std::list<ListGraph::edge> *graphList, int numberOfVertexes);
	int Find(int vertex, Kruskal::vertex *vertexes);
	void Union(vertex *firstTopVertex, vertex *secondTopVertex, Kruskal::vertex * vertexes);
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
	std::list<Kruskal::edge> *solution;
	bool DisplayMstSolution();
};

