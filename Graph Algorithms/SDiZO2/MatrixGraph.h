#pragma once
#include <string>

class MatrixGraph
{
public:
	MatrixGraph();
	~MatrixGraph();
	const int null_value = INT32_MAX;
	int **matrix;
	int numberOfVertexes;
	int numberOfEdges;
	int startVertex;
	int endVertex;
	void GenerateRandomNoDirectedGraph(int numberOfVertexes, float density);
	void GenerateRandomDirectedGraph(int numberOfVertexes, float density);
	void DisplayGraph();
	int** MakeNoDirected();
	bool LoadGraphFromFile(std::string filename);
	bool createDirectedGraph(int numbOfNodes, int density);
	int initializeDirectedAdjacencyMatrix(int numberOfNodes);
};
