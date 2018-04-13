#include "stdafx.h"
#include "Array.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <random>
#include <windows.h>


using namespace std;

// Konstruktor tablicy, ustawia jedynie liczbê elementów tablicy.
// Faktyczna inicjalizacja nastêpuje w momencie dodania pierwszego elementu

Array::Array()
{

	elementCounter = 0;

}


Array::~Array()
{
	clearArray();
}

// Funkcja ta dodaje element o podanej wartoœci, na wskazane miejsce

void Array::addElement(int index, int newElement)
{
	
	// Tworzenie nowej tablicy, o zwiêkszonej liczbie elementów
	int *newArray = new int[elementCounter + 1];

	// Wstawienie nowego elementu na podan¹ pozycjê
	*(newArray + index) = newElement;

	// Relokacja tablicy
	memcpy(newArray, array, (4 * index));
	memcpy((newArray + index + 1), (array + index), (4 * (elementCounter - index)));

	// Zwolnienie miejsca po starej tablicy
	if (array != NULL)
		delete array;

	// Aktualizacja adresu tablicy
	array = newArray;
		
	// Zwiêkszenie licznika elementów o jeden
	elementCounter++;
	
}

// Funkcja dodaje element na pierwsze miejsce

void Array::addFirstElement(int newElement)
{
	// Utworzenie nowej tablicy o zwiêkszonej liczbie elementów
	int *newArray = new int[elementCounter + 1];

	// Dodanie pierwszego elementu
	*newArray = newElement;

	// Relokacja tablicy
	memcpy(newArray + 1, array, 4 * elementCounter);

	// Zwolnienie pamiêci po starej tablicy
	if (array != NULL)
		delete array;

	array = newArray;
	// Aktualizacja adresu
	elementCounter++;
}

// Funkcja dodaje ostatni element
void Array::addLastElement(int newElement)
{
	// Utworzenie nowej tablicy o zwiêkszonej liczbie elementów
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

	// Zwiêkszenie liczby elementów
	elementCounter++;
}

// Funkcja ta usuwa element o wskazanym indeksie

void Array::deleteElement(int index)
{
	
	// Utworzenie nowej tablicy, o zmniejszonej liczbie elementów
	int *newArray = new int[elementCounter - 1];

	// Relokacja tablicy
	memcpy(newArray, array, (4 * index));
	memcpy(newArray + index, array + index + 1, (4 * (elementCounter - index)));
	
	// Zwolnienie miejsca po starej tablicy
	if (array != NULL)
		delete array;

	// Aktualizacja adresu tablicy
	array = newArray;

	// Zmniejszenie licznika elementów
	elementCounter--;

}

// Funkcja ta usuwa element z pocz¹tku

void Array::deleteFirstElement()
{

	// Utworzenie nowej tablicy, o zmniejszonej liczbie elementów
	int *newArray = new int[elementCounter - 1];

	// Relokacja tablicy
	memcpy(newArray, array + 1, 4*(elementCounter - 1));
	

	// Zwolnienie miejsca po starej tablicy
	if (array != NULL)
		delete array;

	// Aktualizacja adresu tablicy
	array = newArray;

	// Zmniejszenie licznika elementów
	elementCounter--;

}

// Funkcja ta usuwa element z konca

void Array::deleteLastElement()
{

	// Utworzenie nowej tablicy, o zmniejszonej liczbie elementów
	int *newArray = new int[elementCounter - 1];

	// Relokacja tablicy
	memcpy(newArray, array, 4*(elementCounter - 1));


	// Zwolnienie miejsca po starej tablicy
	if (array != NULL)
		delete array;

	// Aktualizacja adresu tablicy
	array = newArray;

	// Zmniejszenie licznika elementów
	elementCounter--;

}

// Funkcja wyœwietla aktualn¹ tablicê

void Array::displayArray()
{

	// Zmienna pomocnicza do wyœwietlania tablicy
	int *tempElement;

	// Pêtla wyœwietlaj¹ca wszystkie elementy
	for (int i = 0; i < elementCounter; i++)
	{

		tempElement = (array +i);
		cout << *tempElement << " ";

	}

}

// Funkcja ta sprawdza czy element o podanej wartoœci znajduje siê w tablicy

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

// Funkcja wczytuj¹ca dane z pliku o podanej nazwie, zwraca wartoœæ true, jeœli operacja siê powiedzie.
// W przeciwnym wypadku zwraca wartoœæ false

bool Array::loadDataFromFile(string name)
{
	
	clearArray();
	// Otwarcie pliku
	ifstream file;
	file.open(name);

	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;

	// Pobranie informacji o iloœci elementów
	file >> elementCounter;

	// Utworzenie nowej tablicy
	// POBRANIE WARTOŒCI Z PLIKU POWODUJE UTRATÊ OBECNEJ TABLICY!
	array = new int[elementCounter];

	// Pêtla wczytuj¹ca wartoœci z tablicy
	for (int i = 0; i < elementCounter; i++)
	{
		if (file.good())
			file >> *(array + i);
	}

	return true;

}

// Funkcja generuje losow¹ tablicê o podanej iloœci danych

void Array::generateRandomArray(int numberOfElements, int range)
{

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> distElement(1, range);
	clearArray();
	// Wczytanie iloœci elementów oraz utworzenie tablicy o zadanych rozmiarach
	elementCounter = numberOfElements;
	array = new int[numberOfElements];

	//Pêtla zape³niaj¹ca tablicê losowymi wartoœciami
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








