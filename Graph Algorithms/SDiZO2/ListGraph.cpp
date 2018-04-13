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

	// Pobranie informacji o ilo�ci element�w
	file >> numberOfEdges;
	file >> numberOfVertexes;
	file >> startVertex;
	file >> endVertex;


	// Utworzenie nowego grafu
	graphList = new list<edge>[numberOfVertexes];

	// Zmienne pomocnicze do czytania kraw�dzi z pliku
	int tempStartVertex;
	int tempDestinationVertex;
	int tempWeight;
	edge tempEdge;
	// P�tla wczytuj�ca kraw�die
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
	// Lista reprezantuj�ca graf
	graphList = new list<edge>[numberOfVertexes];
	// Maksymalna ilo�� kraw�dzi jak� mo�e mie� graf pe�ny
	int maxNumberOfEdges = (numberOfVertexes*(numberOfVertexes - 1)) / 2;
	// Ile obecnie ma graf kraw�dzi - na starcie ma ich tyle co liczba wierzcho�k�w, bo tyle jest "zarezerwowanych" dla sp�jno�ci grafu
	int currentNumberOfEdges = numberOfVertexes - 1;
	// Wyliczenie ile kraw�dzi b�dzie mia� ten graf bior�c pod uwag� g�sto��
	int numberOfEdges = density * maxNumberOfEdges;
	// Ile razy jeszcze b�dzie mo�liwo�� wygenerowania kraw�dzi
	int edgesLeft = maxNumberOfEdges - numberOfVertexes;
	// Zakres jaki mo�e mie� waga kraw�dzi
	int rangeOfWeight = numberOfVertexes;
	// Zmienna pomocniczna przechowuj�ca tymczasow� kraw�d�
	edge tempEdge;
	
	// P�tla generuj�ca kraw�dzie
	for (int currentStartVertex = 0; currentStartVertex < numberOfVertexes; currentStartVertex++)
	{
		for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
		{
			// Generowanie kraw�dzi wymaganych do sp�jno�ci - ��czenie wierzcho�ka n z wierzcho�kiem n+1
			if (currentStartVertex + 1 == currentDestinationVertex)
			{
				tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
				graphList[currentStartVertex].push_back(tempEdge);
				tempEdge.destinationVertex = currentStartVertex;
				graphList[currentDestinationVertex].push_back(tempEdge);
			}
			else
				// Je�eli rozpatrywane wierzcho�ki spe�niaj�w warunki po��czenia, to rozpatrywane jest utworzenie kraw�dzi
				if (currentNumberOfEdges < numberOfEdges && (currentDestinationVertex != currentStartVertex) && !FindEdge(currentDestinationVertex, currentStartVertex))
				{
					// Je�eli ilo�� kraw�dzi kt�re jeszcze trzeba wygenerowa� wynosi tyle ile jeszcze mo�na wygenerowa� to kraw�d� musi by� wygenerowana
					if ((numberOfEdges - currentNumberOfEdges) == edgesLeft)
					{
						tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
						graphList[currentStartVertex].push_back(tempEdge);
						tempEdge.destinationVertex = currentStartVertex;
						graphList[currentDestinationVertex].push_back(tempEdge);
						currentNumberOfEdges++;
					}
					else
						// Je�eli kraw�d� nie musi by� wygenerowana, to losowo podejmowana jest decyzja czy b�dzie ona generowana czy nie
						if (rand() % 2 == 1)
						{
							tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
							graphList[currentStartVertex].push_back(tempEdge);
							tempEdge.destinationVertex = currentStartVertex;
							graphList[currentDestinationVertex].push_back(tempEdge);
							currentNumberOfEdges++;
						}
					// Liczba mo�liwych kraw�dzi zmniejsza si� o jeden
					edgesLeft = edgesLeft - 1;
				}
		}
	}
	// Uaktualnienie informacji o liczbie wierzcho�k�w
	this->numberOfVertexes = numberOfVertexes;
}

void ListGraph::GenerateRandomDirectedGraph(int numberOfVertexes, float density)
{
	delete[] graphList;
	// Lista reprezantuj�ca graf
	graphList = new list<edge>[numberOfVertexes];
	// Maksymalna ilo�� kraw�dzi jak� mo�e mie� graf pe�ny
	int maxNumberOfEdges = (numberOfVertexes*(numberOfVertexes - 1)) / 2;
	// Ile obecnie ma graf kraw�dzi - na starcie ma ich tyle co liczba wierzcho�k�w, bo tyle jest "zarezerwowanych" dla sp�jno�ci grafu
	int currentNumberOfEdges = numberOfVertexes - 1;
	// Wyliczenie ile kraw�dzi b�dzie mia� ten graf bior�c pod uwag� g�sto��
	int numberOfEdges = density * maxNumberOfEdges;
	// Ile razy jeszcze b�dzie mo�liwo�� wygenerowania kraw�dzi
	int edgesLeft = maxNumberOfEdges - numberOfVertexes;
	// Zakres jaki mo�e mie� waga kraw�dzi
	int rangeOfWeight = numberOfVertexes;
	// Zmienna pomocniczna przechowuj�ca tymczasow� kraw�d�
	edge tempEdge;

	// P�tla generuj�ca kraw�dzie
	for (int currentStartVertex = 0; currentStartVertex < numberOfVertexes; currentStartVertex++)
	{
		for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
		{
			// Generowanie kraw�dzi wymaganych do sp�jno�ci - ��czenie wierzcho�ka n z wierzcho�kiem n+1
			if (currentStartVertex + 1 == currentDestinationVertex)
			{
				tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
				graphList[currentStartVertex].push_back(tempEdge);
			}
			else
				// Je�eli rozpatrywane wierzcho�ki spe�niaj�w warunki po��czenia, to rozpatrywane jest utworzenie kraw�dzi
				if (currentNumberOfEdges < numberOfEdges && (currentDestinationVertex != currentStartVertex) && !FindEdge(currentDestinationVertex, currentStartVertex))
				{
					// Je�eli ilo�� kraw�dzi kt�re jeszcze trzeba wygenerowa� wynosi tyle ile jeszcze mo�na wygenerowa� to kraw�d� musi by� wygenerowana
					if ((numberOfEdges - currentNumberOfEdges) == edgesLeft)
					{
						tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
						graphList[currentStartVertex].push_back(tempEdge);
						currentNumberOfEdges++;
					}
					else
						// Je�eli kraw�d� nie musi by� wygenerowana, to losowo podejmowana jest decyzja czy b�dzie ona generowana czy nie
						if (rand() % 2 == 1)
						{
							tempEdge = GenerateTempEdge(currentDestinationVertex, rangeOfWeight);
							graphList[currentStartVertex].push_back(tempEdge);
							currentNumberOfEdges++;
						}
					// Liczba mo�liwych kraw�dzi zmniejsza si� o jeden
					edgesLeft = edgesLeft - 1;
				}
		}
	}
	// Uaktualnienie informacji o liczbie wierzcho�k�w
	this->numberOfVertexes = numberOfVertexes;
}

// Generowanie losowej kraw�dzi
ListGraph::edge ListGraph::GenerateTempEdge(int destinationVertex, int rangeOfWeight)
{
	edge tempEdge =
	{
		destinationVertex,
		rand() % rangeOfWeight + 1
	};
	return tempEdge;
}
// Funkcja sprawdza czy kraw�d� jest w grafie
bool ListGraph::FindEdge(int startVertex, int destinationVertex)
{
	for (list<edge>::iterator currentEdge = graphList[startVertex].begin(); currentEdge != graphList[startVertex].end(); currentEdge++)
		if (currentEdge->destinationVertex == destinationVertex)
			return true;
	return false;
}
// Funkcja sprawdza czy kraw�d� jest w grafie przekazanym do funkcji
bool ListGraph::FindEdge(int startVertex, int destinationVertex, std::list<edge>* newGraphList)
{
	for (list<edge>::iterator currentEdge = newGraphList[startVertex].begin(); currentEdge != newGraphList[startVertex].end(); currentEdge++)
		if (currentEdge->destinationVertex == destinationVertex)
			return true;
	return false;
}
// Funkcja przekszta�caj�ca graf w nieskierowany (wymagane do MST)
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


