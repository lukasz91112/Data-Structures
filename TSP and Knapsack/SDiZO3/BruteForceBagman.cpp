#include "stdafx.h"
#include "BruteForceBagman.h"
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <iomanip>
#include "Bagman.h"
#include <fstream>

using namespace std;

BruteForceBagman::BruteForceBagman()
{
}


BruteForceBagman::~BruteForceBagman()
{
}

// Funkcja realizuj¹ca przegl¹d zupe³ny problemu plecakowego
void BruteForceBagman::RunBagman(Bagman * bagman)
{
	// Pobranie danych o problemie
	int **map = bagman->map;
	int numberOfCities = bagman->numberOfCities;
	// Inicjalizacja tablicy przechowuj¹cej kolejnoœæ odwiedzania miast
	int *citiesSequence = new int[numberOfCities - 1];	
	// Wype³nienie tablicy wartoœciami pocz¹tkowymi
	for (int currentCity = 0; currentCity < numberOfCities - 1; currentCity++)
		citiesSequence[currentCity] = currentCity + 1;
	// Inicjalizacja tablicy przechowuj¹cej najlepsz¹ drogê
	int *solution = new int[numberOfCities];
	solution[0] = 0;
	// Zmienna przechowuj¹ca wagê obecnej drogi
	int currentWeight;
	// Zmienna przechowuj¹ca obecnie najlepsz¹ wagê
	int currentBestWeight = inf_value;
	// Zmienne pomocnicze
	int tempStartCity;
	int tempDestinationCity;

	// G³ówna pêtla wykonuj¹ca algorytm
	do
	{
		// Obecny koszt drogi
		currentWeight = 0;
		// Obecne miasto w którym siê znajdujemy
		tempStartCity = 0;
		// Ustawienie pierwszego miasta docelowego
		tempDestinationCity = citiesSequence[0];
		// Zaktualizowanie kosztu obecnej trasy
		currentWeight += map[tempStartCity][tempDestinationCity];
		// Obliczanie kosztu reszty drogi
		for (int currentCity = 1; currentCity < numberOfCities - 1; currentCity++)
		{
			tempStartCity = citiesSequence[currentCity - 1];
			tempDestinationCity = citiesSequence[currentCity];
			currentWeight += map[tempStartCity][tempDestinationCity];
		}
		// Obliczanie kosztu powrotu
		tempStartCity = citiesSequence[numberOfCities - 2];
		tempDestinationCity = 0;
		currentWeight += map[tempStartCity][tempDestinationCity];

		// Je¿eli koszt obecnej drogi jest mniejszy od obecnie najtañszej drogi to nastêpuje zaktualizowanie rozwi¹zania
		if (currentWeight < currentBestWeight)
		{
			currentBestWeight = currentWeight;
			for (int currentCity = 1; currentCity < numberOfCities; currentCity++)
				solution[currentCity] = citiesSequence[currentCity - 1];
		}
	} while (next_permutation(citiesSequence, citiesSequence + numberOfCities - 1));

	// Wyœwietlenie rozwi¹zania
	DisplaySolution(bagman, solution, currentBestWeight);

	// Sprz¹tanie
	delete[] solution;
	delete[] citiesSequence;

}

long long int BruteForceBagman::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}

void BruteForceBagman::Test()
{
	long long int  start, stop, frequency, result;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	Bagman *bagman = new Bagman();
	bagman->CreateRandomBagman(15);
	string name = "brutebag 15.txt";
	fstream file;


	file.open(name, ios::out | ios::app);

	start = read_QPC();
	RunBagman(bagman);
	stop = read_QPC() - start;

	file << setprecision(0) << (1000.0 * stop) / frequency << endl;

	file.close();
	
}

// Funkcja wyœwietlaj¹ca rozwi¹zanie
void BruteForceBagman::DisplaySolution(Bagman * bagman, int * solution, int summaryWeight)
{
	int numberOfCities = bagman->numberOfCities;
	cout << "PRZEGLAD ZUPELNY" << endl << endl;
	cout << "Najlepsza znaleziona droga: [ ";
	for (int currentCity = 0; currentCity < numberOfCities; currentCity++)
		cout << solution[currentCity] << " ";
	cout << "0 ]" << endl;
	cout << "Laczny koszt drogi: " << summaryWeight << endl << endl;
}
