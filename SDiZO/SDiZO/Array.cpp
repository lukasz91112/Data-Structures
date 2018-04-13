#include "stdafx.h"
#include "Array.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <random>
#include <windows.h>


using namespace std;

// Konstruktor tablicy, ustawia jedynie liczb� element�w tablicy.
// Faktyczna inicjalizacja nast�puje w momencie dodania pierwszego elementu

Array::Array()
{

	elementCounter = 0;

}


Array::~Array()
{
	clearArray();
}

// Funkcja ta dodaje element o podanej warto�ci, na wskazane miejsce

void Array::addElement(int index, int newElement)
{
	
	// Tworzenie nowej tablicy, o zwi�kszonej liczbie element�w
	int *newArray = new int[elementCounter + 1];

	// Wstawienie nowego elementu na podan� pozycj�
	*(newArray + index) = newElement;

	// Relokacja tablicy
	memcpy(newArray, array, (4 * index));
	memcpy((newArray + index + 1), (array + index), (4 * (elementCounter - index)));

	// Zwolnienie miejsca po starej tablicy
	if (array != NULL)
		delete array;

	// Aktualizacja adresu tablicy
	array = newArray;
		
	// Zwi�kszenie licznika element�w o jeden
	elementCounter++;
	
}

// Funkcja dodaje element na pierwsze miejsce

void Array::addFirstElement(int newElement)
{
	// Utworzenie nowej tablicy o zwi�kszonej liczbie element�w
	int *newArray = new int[elementCounter + 1];

	// Dodanie pierwszego elementu
	*newArray = newElement;

	// Relokacja tablicy
	memcpy(newArray + 1, array, 4 * elementCounter);

	// Zwolnienie pami�ci po starej tablicy
	if (array != NULL)
		delete array;

	array = newArray;
	// Aktualizacja adresu
	elementCounter++;
}

// Funkcja dodaje ostatni element
void Array::addLastElement(int newElement)
{
	// Utworzenie nowej tablicy o zwi�kszonej liczbie element�w
	int *newArray = new int[elementCounter + 1];

	// Dodanie nowego elementu na koniec
	*(newArray + elementCounter) = newElement;

	// Relokacja tablicy
	memcpy(newArray, array, 4 * elementCounter);

	// Zwolnienie miejsca po starej tablicy
	if (array != NULL)
		delete array;

	// Aktualizacja adresu
	array = newArray;

	// Zwi�kszenie liczby element�w
	elementCounter++;
}

// Funkcja ta usuwa element o wskazanym indeksie

void Array::deleteElement(int index)
{
	
	// Utworzenie nowej tablicy, o zmniejszonej liczbie element�w
	int *newArray = new int[elementCounter - 1];

	// Relokacja tablicy
	memcpy(newArray, array, (4 * index));
	memcpy(newArray + index, array + index + 1, (4 * (elementCounter - index)));
	
	// Zwolnienie miejsca po starej tablicy
	if (array != NULL)
		delete array;

	// Aktualizacja adresu tablicy
	array = newArray;

	// Zmniejszenie licznika element�w
	elementCounter--;

}

// Funkcja ta usuwa element z pocz�tku

void Array::deleteFirstElement()
{

	// Utworzenie nowej tablicy, o zmniejszonej liczbie element�w
	int *newArray = new int[elementCounter - 1];

	// Relokacja tablicy
	memcpy(newArray, array + 1, 4*(elementCounter - 1));
	

	// Zwolnienie miejsca po starej tablicy
	if (array != NULL)
		delete array;

	// Aktualizacja adresu tablicy
	array = newArray;

	// Zmniejszenie licznika element�w
	elementCounter--;

}

// Funkcja ta usuwa element z konca

void Array::deleteLastElement()
{

	// Utworzenie nowej tablicy, o zmniejszonej liczbie element�w
	int *newArray = new int[elementCounter - 1];

	// Relokacja tablicy
	memcpy(newArray, array, 4*(elementCounter - 1));


	// Zwolnienie miejsca po starej tablicy
	if (array != NULL)
		delete array;

	// Aktualizacja adresu tablicy
	array = newArray;

	// Zmniejszenie licznika element�w
	elementCounter--;

}

// Funkcja wy�wietla aktualn� tablic�

void Array::displayArray()
{

	// Zmienna pomocnicza do wy�wietlania tablicy
	int *tempElement;

	// P�tla wy�wietlaj�ca wszystkie elementy
	for (int i = 0; i < elementCounter; i++)
	{

		tempElement = (array +i);
		cout << *tempElement << " ";

	}

}

// Funkcja ta sprawdza czy element o podanej warto�ci znajduje si� w tablicy

bool Array::searchElement(int value)
{
	bool isThere = false;
	for (int currentElement = 0; currentElement < elementCounter; currentElement++)
	{

		if (*(this->array + currentElement) == value)
		{

			isThere = true;
			break;

		}
	}
	return isThere;
}

// Funkcja wczytuj�ca dane z pliku o podanej nazwie, zwraca warto�� true, je�li operacja si� powiedzie.
// W przeciwnym wypadku zwraca warto�� false

bool Array::loadDataFromFile(string name)
{
	
	clearArray();
	// Otwarcie pliku
	ifstream file;
	file.open(name);

	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;

	// Pobranie informacji o ilo�ci element�w
	file >> elementCounter;

	// Utworzenie nowej tablicy
	// POBRANIE WARTO�CI Z PLIKU POWODUJE UTRAT� OBECNEJ TABLICY!
	array = new int[elementCounter];

	// P�tla wczytuj�ca warto�ci z tablicy
	for (int i = 0; i < elementCounter; i++)
	{
		if (file.good())
			file >> *(array + i);
	}

	return true;

}

// Funkcja generuje losow� tablic� o podanej ilo�ci danych

void Array::generateRandomArray(int numberOfElements, int range)
{

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> distElement(1, range);
	clearArray();
	// Wczytanie ilo�ci element�w oraz utworzenie tablicy o zadanych rozmiarach
	elementCounter = numberOfElements;
	array = new int[numberOfElements];

	//P�tla zape�niaj�ca tablic� losowymi warto�ciami
	for (int i = 0; i < numberOfElements; i++)
	{

		*(array + i) = distElement(gen);		

	}
	
}

// Funkcja usuwa obecna tablice

void Array::clearArray()
{

	delete array;

}








