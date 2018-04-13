#include "stdafx.h"
#include "ListGraph.h"
#include <fstream>
#include <iostream>
#include <random>
#include <ctime>
#include <list>
using namespace std;

ListGraph::ListGraph()
{
	srand(time(NULL));
}


ListGraph::~ListGraph()
{
		delete[] graphList;
}


bool ListGraph::LoadGraphFromFile(std::string filename)
{
	// Otwarcie pliku
	ifstream file;
	file.open(filename);

	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;

	// Pobranie informacji o iloœci elementów
	file >> numberOfEdges;
	file >> numberOfVertexes;
	file >> startVertex;
	file >> endVertex;


	// Utworzenie nowego grafu
	graphList = new list<edge>[numberOfVertexes];

	// Zmienne pomocnicze do czytania krawêdzi z pliku
	int tempStartVertex;
	int tempDestinationVertex;
	int tempWeight;
	edge tempEdge;
	// Pêtla wczytuj¹ca krawêdie
	for (int currentEdge = 0; currentEdge < numberOfEdges; currentEdge++)
	{
		file >> tempStartVertex;
		file >> tempDestinationVertex;
		file >> tempWeight;
		tempEdge.destinationVertex = tempDestinationVertex;
		tempEdge.weight = tempWeight;
		graphList[tempStartVertex].push_back(tempEdge);
	}
	return true;
}

void ListGraph::DisplayGraph()
{
	for (int currentVertex = 0; currentVertex < numberOfVertexes; currentVertex++)
		for (list<edge>::iterator currentEdge = graphList[currentVertex].begin(); currentEdge != graphList[currentVertex].end(); currentEdge++)
			cout << "Krawedz: " << currentVertex << " - " << currentEdge->destinationVertex << "  Waga : " << currentEdge->weight << endl;
}


void ListGraph::GenerateRandomNoDirectedGraph(int numberOfVertexes, float density)
{
	delete[] graphList;
	// Lista reprezantuj¹ca graf
	graphList = new list<edge>[numberOfVertexes];
	// Maksymalna iloœæ krawêdzi jak¹ mo¿e mieæ graf pe³ny
	int maxNumberOfEdges = (numberOfVertexes*(numberOfVertexes - 1)) / 2;
	// Ile obecnie ma graf krawêdzi - na starcie ma ich tyle co liczba wierzcho³ków, bo tyle jest "zarezerwowanych" dla spójnoœci grafu
	int currentNumberOfEdges = numberOfVertexes - 1;
	// Wyliczenie ile krawêdzi bêdzie mia³ ten graf bior¹c pod uwagê gêstoœæ
	int numberOfEdges = density * maxNumberOfEdges;
	// Ile razy jeszcze bêdzie mo¿liwoœæ wygenerowania krawêdzi
	int edgesLeft = maxNumberOfEdges - numberOfVertexes;
	// Zakres jaki mo¿e mieæ waga krawêdzi
	int rangeOfWeight = numberOfVertexes;
	// Zmienna pomocniczna przechowuj¹ca tymczasow¹ krawêdŸ
	edge tempEdge;
	
	// Pêtla generuj¹ca krawêdzie
	for (int currentStartVertex = 0; currentStartVertex < numberOfVertexes; currentStartVertex++)
	{
		for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
		{
			// Generowanie krawêdzi wymaganych do spójnoœci - ³¹czenie wierzcho³ka n z wierzcho³kiem n+1
			if (currentStartVertex + 1 == currentDestinationVertex)
			{
				tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
				graphList[currentStartVertex].push_back(tempEdge);
				tempEdge.destinationVertex = currentStartVertex;
				graphList[currentDestinationVertex].push_back(tempEdge);
			}
			else
				// Je¿eli rozpatrywane wierzcho³ki spe³niaj¹w warunki po³¹czenia, to rozpatrywane jest utworzenie krawêdzi
				if (currentNumberOfEdges < numberOfEdges && (currentDestinationVertex != currentStartVertex) && !FindEdge(currentDestinationVertex, currentStartVertex))
				{
					// Je¿eli iloœæ krawêdzi które jeszcze trzeba wygenerowaæ wynosi tyle ile jeszcze mo¿na wygenerowaæ to krawêdŸ musi byæ wygenerowana
					if ((numberOfEdges - currentNumberOfEdges) == edgesLeft)
					{
						tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
						graphList[currentStartVertex].push_back(tempEdge);
						tempEdge.destinationVertex = currentStartVertex;
						graphList[currentDestinationVertex].push_back(tempEdge);
						currentNumberOfEdges++;
					}
					else
						// Je¿eli krawêdŸ nie musi byæ wygenerowana, to losowo podejmowana jest decyzja czy bêdzie ona generowana czy nie
						if (rand() % 2 == 1)
						{
							tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
							graphList[currentStartVertex].push_back(tempEdge);
							tempEdge.destinationVertex = currentStartVertex;
							graphList[currentDestinationVertex].push_back(tempEdge);
							currentNumberOfEdges++;
						}
					// Liczba mo¿liwych krawêdzi zmniejsza siê o jeden
					edgesLeft = edgesLeft - 1;
				}
		}
	}
	// Uaktualnienie informacji o liczbie wierzcho³ków
	this->numberOfVertexes = numberOfVertexes;
}

void ListGraph::GenerateRandomDirectedGraph(int numberOfVertexes, float density)
{
	delete[] graphList;
	// Lista reprezantuj¹ca graf
	graphList = new list<edge>[numberOfVertexes];
	// Maksymalna iloœæ krawêdzi jak¹ mo¿e mieæ graf pe³ny
	int maxNumberOfEdges = (numberOfVertexes*(numberOfVertexes - 1)) / 2;
	// Ile obecnie ma graf krawêdzi - na starcie ma ich tyle co liczba wierzcho³ków, bo tyle jest "zarezerwowanych" dla spójnoœci grafu
	int currentNumberOfEdges = numberOfVertexes - 1;
	// Wyliczenie ile krawêdzi bêdzie mia³ ten graf bior¹c pod uwagê gêstoœæ
	int numberOfEdges = density * maxNumberOfEdges;
	// Ile razy jeszcze bêdzie mo¿liwoœæ wygenerowania krawêdzi
	int edgesLeft = maxNumberOfEdges - numberOfVertexes;
	// Zakres jaki mo¿e mieæ waga krawêdzi
	int rangeOfWeight = numberOfVertexes;
	// Zmienna pomocniczna przechowuj¹ca tymczasow¹ krawêdŸ
	edge tempEdge;

	// Pêtla generuj¹ca krawêdzie
	for (int currentStartVertex = 0; currentStartVertex < numberOfVertexes; currentStartVertex++)
	{
		for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
		{
			// Generowanie krawêdzi wymaganych do spójnoœci - ³¹czenie wierzcho³ka n z wierzcho³kiem n+1
			if (currentStartVertex + 1 == currentDestinationVertex)
			{
				tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
				graphList[currentStartVertex].push_back(tempEdge);
			}
			else
				// Je¿eli rozpatrywane wierzcho³ki spe³niaj¹w warunki po³¹czenia, to rozpatrywane jest utworzenie krawêdzi
				if (currentNumberOfEdges < numberOfEdges && (currentDestinationVertex != currentStartVertex) && !FindEdge(currentDestinationVertex, currentStartVertex))
				{
					// Je¿eli iloœæ krawêdzi które jeszcze trzeba wygenerowaæ wynosi tyle ile jeszcze mo¿na wygenerowaæ to krawêdŸ musi byæ wygenerowana
					if ((numberOfEdges - currentNumberOfEdges) == edgesLeft)
					{
						tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
						graphList[currentStartVertex].push_back(tempEdge);
						currentNumberOfEdges++;
					}
					else
						// Je¿eli krawêdŸ nie musi byæ wygenerowana, to losowo podejmowana jest decyzja czy bêdzie ona generowana czy nie
						if (rand() % 2 == 1)
						{
							tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
							graphList[currentStartVertex].push_back(tempEdge);
							currentNumberOfEdges++;
						}
					// Liczba mo¿liwych krawêdzi zmniejsza siê o jeden
					edgesLeft = edgesLeft - 1;
				}
		}
	}
	// Uaktualnienie informacji o liczbie wierzcho³ków
	this->numberOfVertexes = numberOfVertexes;
}

// Generowanie losowej krawêdzi
ListGraph::edge ListGraph::GenerateTempEdge(int destinationVertex, int rangeOfWeight)
{
	edge tempEdge =
	{
		destinationVertex,
		rand() % rangeOfWeight + 1
	};
	return tempEdge;
}
// Funkcja sprawdza czy krawêdŸ jest w grafie
bool ListGraph::FindEdge(int startVertex, int destinationVertex)
{
	for (list<edge>::iterator currentEdge = graphList[startVertex].begin(); currentEdge != graphList[startVertex].end(); currentEdge++)
		if (currentEdge->destinationVertex == destinationVertex)
			return true;
	return false;
}
// Funkcja sprawdza czy krawêdŸ jest w grafie przekazanym do funkcji
bool ListGraph::FindEdge(int startVertex, int destinationVertex, std::list<edge>* newGraphList)
{
	for (list<edge>::iterator currentEdge = newGraphList[startVertex].begin(); currentEdge != newGraphList[startVertex].end(); currentEdge++)
		if (currentEdge->destinationVertex == destinationVertex)
			return true;
	return false;
}
// Funkcja przekszta³caj¹ca graf w nieskierowany (wymagane do MST)
std::list<ListGraph::edge>* ListGraph::MakeNoDirected()
{
	list<ListGraph::edge> *newList = new list<edge>[numberOfVertexes];
	edge tempEdge;
	for (int currentStartVertex = 0; currentStartVertex < numberOfVertexes; currentStartVertex++)
		for (list<edge>::iterator currentEdge = graphList[currentStartVertex].begin(); currentEdge != graphList[currentStartVertex].end(); currentEdge++)
		{
			tempEdge.destinationVertex = currentEdge->destinationVertex;
			tempEdge.weight = currentEdge->weight;
			newList[currentStartVertex].push_back(tempEdge);
			if (!FindEdge(currentEdge->destinationVertex, currentStartVertex, newList))
			{
				tempEdge.destinationVertex = currentStartVertex;
				newList[currentEdge->destinationVertex].push_back(tempEdge);
			}
		}

	return newList;
}


