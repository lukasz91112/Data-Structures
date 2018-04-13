#include "stdafx.h"
#include "Bagman.h"
#include <random>
#include <ctime>
#include <iostream>
#include <fstream>


using namespace std;

Bagman::Bagman()
{
	map = NULL;
}


Bagman::~Bagman()
{
	ClearMap();
}

// Utworzenie losowego problemu komiwoja�era
void Bagman::CreateRandomBagman(int numberOfCities)
{
	srand(time(NULL));
	
	// Usuwanie poprzedniej mapy
	ClearMap();
	// Pobranie danych o tworzonej mapie
	this->numberOfCities = numberOfCities;
	// Inicjalizacja macierzy
	map = new int*[numberOfCities];
	// Wype�nianie macierzy kraw�dziami
	for (int currentStartCity = 0; currentStartCity < numberOfCities; currentStartCity++)
	{
		map[currentStartCity] = new int[numberOfCities];
		for (int currentDestinationCity = 0; currentDestinationCity < numberOfCities; currentDestinationCity++)
			if (currentStartCity == currentDestinationCity)
				map[currentStartCity][currentDestinationCity] = 0;
			else
				map[currentStartCity][currentDestinationCity] = rand() % range_of_weight + 1;
	}
	// Wy�wietlanie wygenerowanej mapy
	DisplayMap();
	system("PAUSE");
}

// Wczytywanie mapy z pliku
bool Bagman::LoadMapFromFile(string filename)
{
	// Otwarcie pliku
	ifstream file;
	file.open(filename);

	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;

	// Usuni�cie poprzedniej mapy
	ClearMap();

	// Pobranie informacji o ilo�ci element�w
	file >> numberOfCities;

	// Inicjalizacja nowej macierzy
	map = new int*[numberOfCities];

	// P�tla wczytuj�ca miasta
	for (int currentStartCity = 0; currentStartCity < numberOfCities; currentStartCity++)
	{
		map[currentStartCity] = new int[numberOfCities];
		for (int currentDestinationCity = 0; currentDestinationCity < numberOfCities; currentDestinationCity++)
			file >> map[currentStartCity][currentDestinationCity];
	}

	file.close();
	// Wy�wietlenie wczytanej mapy
	DisplayMap();
	system("PAUSE");

	return true;
}

// Funkcja wy�wietlaj�ca map� w postaci macierzy s�siedztwa
void Bagman::DisplayMap()
{
	int currentWeight;
	int currentWeightSize;
	for (int currentRow = 0; currentRow < numberOfCities; currentRow++)
	{
		if (currentRow == 0)
		{
			cout << "     ";
			for (int currentRowHeader = 0; currentRowHeader < numberOfCities; currentRowHeader++)
				cout << currentRowHeader << "   ";
			cout << endl << endl;
		}
		cout << currentRow << "   ";
		for (int currentColumn = 0; currentColumn < numberOfCities; currentColumn++)
		{
			currentWeight = map[currentRow][currentColumn];
			currentWeightSize = (int)log10(currentWeight) + 1;
			if (currentWeight == 0)
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
		cout << endl << endl;
	}
}

// Funkcja usuwaj�ca obecn� map�
void Bagman::ClearMap()
{
	if (map != NULL)
		for (int currentCity = 0; currentCity < numberOfCities; currentCity++)
			delete[] map[currentCity];
}
