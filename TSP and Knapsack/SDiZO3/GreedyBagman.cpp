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

// Funkcja wykonuj�ca algorytm zach�anny
void GreedyBagman::Run(Bagman * bagman)
{
	// Pobranie danych o problemie komiwoja�era 
	int **map = bagman->map;
	int numberOfCities = bagman->numberOfCities;
	// Tablica przechowuj�ca obecne rozwi�zanie
	int *solution = new int[numberOfCities];
	solution[0] = 0;
	// Talibca przechowuj�ca czy dane miasto by�o ju� odwiedzone
	bool *visited = new bool[numberOfCities];
	// Ustawienie wszystkich miast jako nieodwiedzonych
	for (int i = 0; i < numberOfCities; i++)
		visited[i] = false;
	// Zmienna pomocnicza przechowuj�ca obecnie najblizsze miasto
	int currentMinCity;
	// Zmienna przechowuj�ca obecnie najmniejsz� wag�
	int currentMinWeight;
	// Zmienna przechowuj�ca obecn� wag� wszystkich dr�g
	int currentSummaryWeight = 0;
	// Zmienna przechowuj�ca obecnie sprawdzane miasto - pocz�tkowo miasto 0
	int currentStartCity = 0;
	// Oznaczenie miasta o indeksie 0 jako ju� odwiedzonego
	visited[0] = true;
	// G��wna p�tla wykonuj�ca algorytm zach�anny
	for (int currentCity = 0; currentCity < numberOfCities - 1; currentCity++)
	{
		// Ustawienie obecnie najta�szej drogi jako niesko�czono��
		currentMinWeight = inf_value;
		// P�tla wyszukuj�ca najta�sze miasto
		for (int currentDestinationCity = 0; currentDestinationCity < numberOfCities; currentDestinationCity++)
		{
			// Je�eli miasto nie by�o odwiedzone, jest ta�sze od obecnie najta�szego to jest oznaczone jako najta�sze
			if (map[currentStartCity][currentDestinationCity] < currentMinWeight && !visited[currentDestinationCity] && currentStartCity != currentDestinationCity)
			{
				currentMinCity = currentDestinationCity;
				currentMinWeight = map[currentStartCity][currentMinCity];
			}
		}
		// Miasto wyszukane jako najta�sze zostaje oznaczone jako odwiedzone
		visited[currentMinCity] = true;
		// Dodanie kosztu obecnej drogi do kosztu ��cznego
		currentSummaryWeight += currentMinWeight;
		// Dodanie miasta do rozwi�zania
		solution[currentCity + 1] = currentMinCity;
		// Ustawienie miasta kt�re okaza�o si� najta�sze jako miasta w kt�rym si� znajdujemy
		currentStartCity = currentMinCity;
	}
	// Dodanie kosztu powrotu do domu
	currentSummaryWeight += map[currentStartCity][0];

	// Wy�wietlenie rozwi�zania
	DisplaySolution(solution, currentSummaryWeight, numberOfCities);

	// Sprz�tanie
	delete[] solution;
	delete[] visited;
}

// Funkcja wy�wietlaj�ca rozwi�zanie
void GreedyBagman::DisplaySolution(int *solution, int summaryWeight, int numberOfCities)
{
	cout << "ALGORYTM ZACHLANNY" << endl << endl;
	cout << "Najlepsza znaleziona droga: [ ";
	for (int currentCity = 0; currentCity < numberOfCities; currentCity++)
		cout << solution[currentCity] << " ";
	cout << "0 ]" << endl;
	cout << "Laczny koszt drogi: " << summaryWeight << endl << endl;
}