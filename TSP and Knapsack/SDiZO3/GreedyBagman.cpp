#include "stdafx.h"
#include "GreedyBagman.h"
#include <iostream>

using namespace std;

GreedyBagman::GreedyBagman()
{
}


GreedyBagman::~GreedyBagman()
{
}

// Funkcja wykonuj¹ca algorytm zach³anny
void GreedyBagman::Run(Bagman * bagman)
{
	// Pobranie danych o problemie komiwoja¿era 
	int **map = bagman->map;
	int numberOfCities = bagman->numberOfCities;
	// Tablica przechowuj¹ca obecne rozwi¹zanie
	int *solution = new int[numberOfCities];
	solution[0] = 0;
	// Talibca przechowuj¹ca czy dane miasto by³o ju¿ odwiedzone
	bool *visited = new bool[numberOfCities];
	// Ustawienie wszystkich miast jako nieodwiedzonych
	for (int i = 0; i < numberOfCities; i++)
		visited[i] = false;
	// Zmienna pomocnicza przechowuj¹ca obecnie najblizsze miasto
	int currentMinCity;
	// Zmienna przechowuj¹ca obecnie najmniejsz¹ wagê
	int currentMinWeight;
	// Zmienna przechowuj¹ca obecn¹ wagê wszystkich dróg
	int currentSummaryWeight = 0;
	// Zmienna przechowuj¹ca obecnie sprawdzane miasto - pocz¹tkowo miasto 0
	int currentStartCity = 0;
	// Oznaczenie miasta o indeksie 0 jako ju¿ odwiedzonego
	visited[0] = true;
	// G³ówna pêtla wykonuj¹ca algorytm zach³anny
	for (int currentCity = 0; currentCity < numberOfCities - 1; currentCity++)
	{
		// Ustawienie obecnie najtañszej drogi jako nieskoñczonoœæ
		currentMinWeight = inf_value;
		// Pêtla wyszukuj¹ca najtañsze miasto
		for (int currentDestinationCity = 0; currentDestinationCity < numberOfCities; currentDestinationCity++)
		{
			// Je¿eli miasto nie by³o odwiedzone, jest tañsze od obecnie najtañszego to jest oznaczone jako najtañsze
			if (map[currentStartCity][currentDestinationCity] < currentMinWeight && !visited[currentDestinationCity] && currentStartCity != currentDestinationCity)
			{
				currentMinCity = currentDestinationCity;
				currentMinWeight = map[currentStartCity][currentMinCity];
			}
		}
		// Miasto wyszukane jako najtañsze zostaje oznaczone jako odwiedzone
		visited[currentMinCity] = true;
		// Dodanie kosztu obecnej drogi do kosztu ³¹cznego
		currentSummaryWeight += currentMinWeight;
		// Dodanie miasta do rozwi¹zania
		solution[currentCity + 1] = currentMinCity;
		// Ustawienie miasta które okaza³o siê najtañsze jako miasta w którym siê znajdujemy
		currentStartCity = currentMinCity;
	}
	// Dodanie kosztu powrotu do domu
	currentSummaryWeight += map[currentStartCity][0];

	// Wyœwietlenie rozwi¹zania
	DisplaySolution(solution, currentSummaryWeight, numberOfCities);

	// Sprz¹tanie
	delete[] solution;
	delete[] visited;
}

// Funkcja wyœwietlaj¹ca rozwi¹zanie
void GreedyBagman::DisplaySolution(int *solution, int summaryWeight, int numberOfCities)
{
	cout << "ALGORYTM ZACHLANNY" << endl << endl;
	cout << "Najlepsza znaleziona droga: [ ";
	for (int currentCity = 0; currentCity < numberOfCities; currentCity++)
		cout << solution[currentCity] << " ";
	cout << "0 ]" << endl;
	cout << "Laczny koszt drogi: " << summaryWeight << endl << endl;
}