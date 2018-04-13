#pragma once
#include <list>
#include <string>
class ListGraph
{
public:
	ListGraph();
	~ListGraph();
	int numberOfEdges;
	int numberOfVertexes;
	int startVertex;
	int endVertex;
	struct edge
	{
		int destinationVertex;
		int weight;
	};
	std::list<edge> *graphList;
	bool LoadGraphFromFile(std::string filename);
	void DisplayGraph();
	void GenerateRandomNoDirectedGraph(int numberOfVertexes, float density);
	void GenerateRandomDirectedGraph(int numberOfVertexes, float density);
	edge GenerateTempEdge(int destinationVertex, int weight);
	bool FindEdge(int startVertex, int destinationEdge);
	bool FindEdge(int startVertex, int destinationEdge, std::list<edge> *newGraphList);
	std::list<edge>* MakeNoDirected();
};

