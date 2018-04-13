#include "stdafx.h"
#include "Test.h"
#include <windows.h>
#include "MatrixGraph.h"
#include "Prim.h"
#include <iomanip>
#include <fstream>
#include <string>
#include "Dijkstra.h"
#include "Kruskal.h"
#include "BellmanFord.h"

using namespace std;

Test::Test()
{
	TestPrim();
}


Test::~Test()
{
}

void Test::TestPrim()
{
	long long int summary, start, stop, frequency, result;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);	
	ListGraph *graph;
	Dijkstra *bellman;
	float density = 0.25;
	int numberOfVertexes = 40;
	char *densityName = new char[3];
	sprintf(densityName, "%d", int(100*density));
	string name = "Bellman list ";
	name.append(densityName);
	name.append(".txt");
	fstream file;
	summary = 0;
	
	for (int currentDensityNumber = 0; currentDensityNumber < 4; currentDensityNumber++)
	{
		name = "Bellman list ";
		sprintf(densityName, "%d", int(100*density));
		name.append(densityName);
		name.append(".txt");
		file.open(name, ios::out | ios::app);
		numberOfVertexes = 40;
		for (int currentVertexNumber = 0; currentVertexNumber < 5; currentVertexNumber++)
		{
			summary = 0;
			for (int currentTrial = 0; currentTrial < 100; currentTrial++)
			{
				graph = new ListGraph();
				graph->GenerateRandomDirectedGraph(numberOfVertexes, density);
				bellman = new Dijkstra();
				start = read_QPC();
				bellman->RunList(graph->graphList, graph->numberOfVertexes, graph->startVertex);
				stop = read_QPC() - start;
				summary += stop;
				delete bellman;
				delete graph;
			}			
			result = summary / 100;
			file << setprecision(0) << (1000000.0 * result) / frequency << endl;
			numberOfVertexes += 40;
			cout << numberOfVertexes << endl;
			
		}
		file.close();
		density += 0.25;
		if (density == 1)
			density = 0.99;
		cout << density << endl;
	}
	
}

long long int Test::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}

void Test::Test()
{
	long long int summary, start, stop, frequency, result;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	ListGraph *graph;
	Dijkstra *bellman;
	float density = 0.25;
	int numberOfVertexes = 40;
	char *densityName = new char[3];
	sprintf(densityName, "%d", int(100 * density));
	string name = "Bellman list ";
	name.append(densityName);
	name.append(".txt");
	fstream file;
	summary = 0;

	for (int currentDensityNumber = 0; currentDensityNumber < 4; currentDensityNumber++)
	{
		name = "Bellman list ";
		sprintf(densityName, "%d", int(100 * density));
		name.append(densityName);
		name.append(".txt");
		file.open(name, ios::out | ios::app);
		numberOfVertexes = 40;
		for (int currentVertexNumber = 0; currentVertexNumber < 5; currentVertexNumber++)
		{
			summary = 0;
			for (int currentTrial = 0; currentTrial < 100; currentTrial++)
			{
				graph = new ListGraph();
				graph->GenerateRandomDirectedGraph(numberOfVertexes, density);
				bellman = new Dijkstra();
				start = read_QPC();
				bellman->RunList(graph->graphList, graph->numberOfVertexes, graph->startVertex);
				stop = read_QPC() - start;
				summary += stop;
				delete bellman;
				delete graph;
			}
			result = summary / 100;
			file << setprecision(0) << (1000000.0 * result) / frequency << endl;
			numberOfVertexes += 40;
			cout << numberOfVertexes << endl;

		}
		file.close();
		density += 0.25;
		if (density == 1)
			density = 0.99;
		cout << density << endl;
	}

}