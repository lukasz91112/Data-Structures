#pragma once
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
class Menu
{
public:
	Menu();
	~Menu();
	MatrixGraph *matrixGraph;
	ListGraph *listGraph;
	Prim *prim;
	Kruskal *kruskal;
	Dijkstra *dijkstra;
	BellmanFord *bellmanFord;
	void MatrixMenu();
	void MatrixLoadFromFile();
	void MatrixGenerateRandom();
	void MatrixDisplayGraph();
	void MatrixPrimAlgorithm();
	void MatrixKruskalAlgorithm();
	void MatrixDijkstraAlgorithm();
	void MatrixBellmanFordAlgorithm();
	void ListMenu();
	void ListLoadFromFile();
	void ListGenerateRandom();
	void ListDisplayGraph();
	void ListPrimAlgorithm();
	void ListKruskalAlgorithm();
	void ListDijkstraAlgorithm();
	void ListBellmanFordAlgorithm();
};

