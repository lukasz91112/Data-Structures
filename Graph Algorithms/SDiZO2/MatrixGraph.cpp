#include "stdafx.h"
#include "MatrixGraph.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

MatrixGraph::MatrixGraph()
{
	
}

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < numberOfVertexes; i++)
		delete[] matrix[i];
	delete[] matrix;
}
// Funkcja generuj¹ca graf skierowany
void MatrixGraph::GenerateRandomDirectedGraph(int numberOfVertexes, float density)
{
	srand(time(NULL));
	// Macierz reprezantuj¹ca graf
	matrix = new int*[numberOfVertexes];
	// Maksymalna iloœæ krawêdzi jak¹ mo¿e mieæ graf pe³ny
	int maxNumberOfEgdes = (numberOfVertexes*(numberOfVertexes - 1)) / 2;
	// Ile obecnie ma graf krawêdzi - na starcie ma ich tyle co liczba wierzcho³ków, bo tyle jest "zarezerwowanych" dla spójnoœci grafu
	int currentNumberOfEdges = numberOfVertexes;
	// Wyliczenie ile krawêdzi bêdzie mia³ ten graf bior¹c pod uwagê gêstoœæ
	int numberOfEdges = density * maxNumberOfEgdes;
	// Ile razy jeszcze bêdzie mo¿liwoœæ wygenerowania krawêdzi
	int edgesLeft = maxNumberOfEgdes - numberOfVertexes;
	// Zakres jaki mo¿e mieæ waga krawêdzi
	int rangeOfWeight = numberOfVertexes;
	// Inicjalizacja macierzy
	for (int currentRow = 0; currentRow < numberOfVertexes; currentRow++)
		matrix[currentRow] = new int[numberOfVertexes];
	// Wype³nianie macierzy krawêdziami
	for (int currentRow = 0; currentRow < numberOfVertexes; currentRow++)
	{
		for (int currentColumn = 0; currentColumn < numberOfVertexes; currentColumn++)
		{
			// Generowanie krawêdzi wymaganych do spójnoœci grafu
			if (currentRow + 1 == currentColumn)
				matrix[currentRow][currentColumn] = (rand() % rangeOfWeight) + 1;
			else
				if (currentRow == 0 && currentColumn == (numberOfVertexes - 1))
				{
					matrix[currentRow][currentColumn] = (rand() % rangeOfWeight) + 1;
				}
				else
					// Je¿eli rozpatrywane wierzcho³ki spe³niaj¹w warunki po³¹czenia, to rozpatrywane jest utworzenie krawêdzi
					if (currentNumberOfEdges < numberOfEdges && ((currentRow < currentColumn) || (matrix[currentColumn][currentRow] == -1)) && (currentColumn != currentRow))
					{
						// Je¿eli iloœæ krawêdzi które jeszcze trzeba wygenerowaæ wynosi tyle ile jeszcze mo¿na wygenerowaæ to krawêdŸ musi byæ wygenerowana
						if ((numberOfEdges - currentNumberOfEdges) == edgesLeft && (currentColumn != currentRow))
						{
							matrix[currentRow][currentColumn] = (rand() % rangeOfWeight) + 1;
							currentNumberOfEdges++;
						}
						else
							// Je¿eli krawêdŸ nie musi byæ wygenerowana, to losowo podejmowana jest decyzja czy bêdzie ona generowana czy nie
							if (rand() % 2 == 1)
							{
								matrix[currentRow][currentColumn] = (rand() % rangeOfWeight) + 1;
								currentNumberOfEdges++;
							}
							else
							{
								matrix[currentRow][currentColumn] = null_value;
							}
						edgesLeft = edgesLeft - 1;
					}
					else
					{
						matrix[currentRow][currentColumn] = null_value;
					}
		}
	}
	this->numberOfVertexes = numberOfVertexes;

}

bool MatrixGraph::createDirectedGraph(int numbOfNodes, int density)
{

	int randomWeight, numberOfEdgesToGenerate = float(numbOfNodes*(numbOfNodes - 1))*((float)density),
		currentNumberOfEdges = 0, randomNode1 = -1, randomNode2 = -1;

	if (numberOfEdgesToGenerate >= numbOfNodes - 1)
	{
		currentNumberOfEdges += initializeDirectedAdjacencyMatrix(numbOfNodes);
		while (currentNumberOfEdges < numberOfEdgesToGenerate)
		{
			randomNode1 = rand() % numbOfNodes;
			randomNode2 = rand() % numbOfNodes;
			if (matrix[randomNode1][randomNode2] == null_value && randomNode1 != randomNode2)
			{
				randomWeight = rand() % (2 * numbOfNodes);
				matrix[randomNode1][randomNode2] = randomWeight;
				currentNumberOfEdges++;
			}
		}
		this->numberOfEdges = numberOfEdgesToGenerate;
		this->numberOfVertexes = numbOfNodes;
		//showGraph();

		return true;
	}
	else
	{
		cout << endl << "Zbyt mala wartosc dla grafu spojnego" << endl;
		return false;
	}


}

int MatrixGraph::initializeDirectedAdjacencyMatrix(int numberOfNodes)
{
	matrix = new int*[numberOfNodes];
	int randomWeight, numbrOfEdges = 0;
	for (int i = 0; i < numberOfNodes; i++)
	{
		matrix[i] = new int[numberOfNodes];
		for (int j = 0; j < numberOfNodes; j++)
		{
			matrix[i][j] = null_value;
		}
	}

	for (int node = 0; node < numberOfNodes - 1; node++)
	{
		randomWeight = rand() % (20 * numberOfNodes);
		matrix[node][node + 1] = randomWeight;
		numbrOfEdges++;
	}
	return numbrOfEdges;
}

// Funkcja generuj¹ca graf nieskierowany
void MatrixGraph::GenerateRandomNoDirectedGraph(int numberOfVertexes, float density)
{
	delete[] matrix;
	srand(time(NULL));
	// Macierz reprezantuj¹ca graf
	matrix = new int*[numberOfVertexes];
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
	// Pêtla inicjalizuj¹ca graf, zape³nia go wartoœciami -1 oznaczaj¹cymi brak krawêdzi
	for (int currentRow = 0; currentRow < numberOfVertexes; currentRow++)
	{
		matrix[currentRow] = new int[numberOfVertexes];
		for (int currentColumn = 0; currentColumn < numberOfVertexes; currentColumn++)
			matrix[currentRow][currentColumn] = null_value;
	}
	// Pêtla generuj¹ca krawêdzie
	for (int currentRow = 0; currentRow < numberOfVertexes; currentRow++)
	{
		for (int currentColumn = 0; currentColumn < numberOfVertexes; currentColumn++)
		{
			// Generowanie krawêdzi wymaganych do spójnoœci - ³¹czenie wierzcho³ka n z wierzcho³kiem n+1
			if (currentRow + 1 == currentColumn)
			{
				matrix[currentRow][currentColumn] = (rand() % rangeOfWeight) + 1;
				matrix[currentColumn][currentRow] = matrix[currentRow][currentColumn];
			}
			else
				// Je¿eli rozpatrywane wierzcho³ki spe³niaj¹w warunki po³¹czenia, to rozpatrywane jest utworzenie krawêdzi
				if (currentNumberOfEdges < numberOfEdges && (currentColumn != currentRow) && (matrix[currentColumn][currentRow] == null_value))
				{
					// Je¿eli iloœæ krawêdzi które jeszcze trzeba wygenerowaæ wynosi tyle ile jeszcze mo¿na wygenerowaæ to krawêdŸ musi byæ wygenerowana
					if ((numberOfEdges - currentNumberOfEdges) == edgesLeft)
					{
						matrix[currentRow][currentColumn] = (rand() % rangeOfWeight) + 1;
						matrix[currentColumn][currentRow] = matrix[currentRow][currentColumn];
						currentNumberOfEdges++;
					}
					else
						// Je¿eli krawêdŸ nie musi byæ wygenerowana, to losowo podejmowana jest decyzja czy bêdzie ona generowana czy nie
						if (rand() % 2 == 1)
						{
							matrix[currentRow][currentColumn] = (rand() % rangeOfWeight) + 1;
							matrix[currentColumn][currentRow] = matrix[currentRow][currentColumn];
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
// Funkcja wyœwietlaj¹ca graf
void MatrixGraph::DisplayGraph()
{
	int currentWeight;
	int currentWeightSize;
	for (int currentRow = 0; currentRow < numberOfVertexes; currentRow++)
	{
		if (currentRow == 0) 
		{
			cout << "     ";
			for (int currentRowHeader = 0; currentRowHeader < numberOfVertexes; currentRowHeader++)
				cout << currentRowHeader << "   " ;
			cout << endl << endl;
		}
		cout << currentRow << "   ";
		for (int currentColumn = 0; currentColumn < numberOfVertexes; currentColumn++)
		{
			currentWeight = matrix[currentRow][currentColumn];
			currentWeightSize = (int)log10(currentWeight) + 1;
			if (currentWeight == null_value)
				cout << "INF" << " ";
			else
			{
				switch (currentWeightSize)
				{
				case 1:
					cout << " " << currentWeight << "  ";
					break;
				case 2:
					cout << " " << currentWeight << " ";
					break;
				case 3:
					cout << currentWeight << " ";
				default:
					cout << " " << currentWeight << " ";
					break;
				}
			}
		}
		cout << endl;
	}
}
// Funkcja ta przekszta³ca graf w graf nieskierowany (wymagane dla MST)
int** MatrixGraph::MakeNoDirected()
{
	int **newMatrix = new int*[numberOfVertexes];
	int tempWeight;
	for (int currentRow = 0; currentRow < numberOfVertexes; currentRow++)
	{
		newMatrix[currentRow] = new int[numberOfVertexes];
		for (int currentColumn = 0; currentColumn < numberOfVertexes; currentColumn++)
			newMatrix[currentRow][currentColumn] = null_value;
	}

	for (int currentStartVertex = 0; currentStartVertex < numberOfVertexes; currentStartVertex++)
	{
		for (int currentDestinationVertex = 0; currentDestinationVertex < numberOfVertexes; currentDestinationVertex++)
		{
			
			tempWeight = matrix[currentStartVertex][currentDestinationVertex];		
			if (tempWeight != null_value)
			{
				newMatrix[currentStartVertex][currentDestinationVertex] = tempWeight;
				newMatrix[currentDestinationVertex][currentStartVertex] = tempWeight;
			}
		}
	}
	return newMatrix;
}

bool MatrixGraph::LoadGraphFromFile(std::string filename)
{
	
	delete[] matrix;
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
	matrix = new int*[numberOfVertexes];

	for (int currentRow = 0; currentRow < numberOfVertexes; currentRow++)
	{
		matrix[currentRow] = new int[numberOfVertexes];
		for (int currentColumn = 0; currentColumn < numberOfVertexes; currentColumn++)
			matrix[currentRow][currentColumn] = null_value;
	}
	// Zmienne pomocnicze do czytania krawêdzi z pliku
	int tempStartVertex;
	int tempDestinationVertex;
	int tempWeight;
	// Pêtla wczytuj¹ca krawêdie
	for (int currentEdge = 0; currentEdge < numberOfEdges; currentEdge++)
	{
		file >> tempStartVertex;
		file >> tempDestinationVertex;
		file >> tempWeight;
		matrix[tempStartVertex][tempDestinationVertex] = tempWeight;
	}
	return true;
}




