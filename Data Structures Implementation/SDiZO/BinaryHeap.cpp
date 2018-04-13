#include "stdafx.h"
#include "BinaryHeap.h"
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
#include <random>

using namespace std;

BinaryHeap::BinaryHeap()
{

	int elementCounter = 0;
	
}


BinaryHeap::~BinaryHeap()
{

	elementCounter = 0;
	delete binaryHeap;

}

// Funkcja ta dodaje element o podanej warto�ci jako li�� a nast�pnie naprawia drzewo do g�ry

void BinaryHeap::addElement(int newElement)
{

	// Utworzenie tablicowej reprezentacji kopca
	int *newHeap = new int[elementCounter + 1];

	// Przypisanie li�ciowi warto�ci elementu
	*(newHeap + elementCounter) = newElement;

	// Relokacja kopca
	memcpy(newHeap, binaryHeap, 4 * elementCounter);

	// Zwolnienie pami�ci po starym kopcu
	if (binaryHeap != NULL)
		delete binaryHeap;

	// Aktualizacja adresu kopca
	binaryHeap = newHeap;
	// Zwi�kszenie licznika element�w
	elementCounter++;

	// Je�eli dodany element nie jest pierwszym nast�puje naprawa kopca
	if (elementCounter > 1)
		repairHeapUp(elementCounter - 1);
	
}

// Funkcja ta usuwa korze� kopca

void BinaryHeap::deleteElement()
{

	// Przypisanie ostatniego li�cia jako korze� kopca
	*(binaryHeap) = *(binaryHeap + elementCounter - 1);

	// Utworzenie nowego kopca, o zmniejszonej liczbie element�w
	int *newHeap = new int[elementCounter - 1];

	// Relokacja kopca
	memcpy(newHeap, binaryHeap, 4 * (elementCounter - 1));
	
	// Zwolnienie pami�ci po starym kopcu
	if (binaryHeap != NULL)
		delete binaryHeap;

	// Aktualizacja adresu kopca
	binaryHeap = newHeap;	

	// Zmniejszenie licznika element�w
	elementCounter--;

	// Naprawa kopca w d�
	repairHeapDown();

}

// Funkcja ta generuje losowy kopiec

void BinaryHeap::generateRandomBinaryHeap(int numberOfElements)
{

	clearBinaryHeap();
	// Wczytanie ilo�ci element�w oraz utworzenie kopca o zadanych rozmiarach
	elementCounter = numberOfElements;
	binaryHeap = new int[numberOfElements];

	//P�tla zape�niaj�ca kopiec losowymi warto�ciami oraz naprawiaj�ca go na bie��co
	for (int i = 0; i < numberOfElements; i++)
	{

		*(binaryHeap + i) = generateRandomNumber(1000000);
		repairHeapUp(i);

	}
}

// Funkcja ta naprawia kopiec do g�ry od wskazanej pozycji

void BinaryHeap::repairHeapUp(int index)
{

	// currentIndex - index elementu kt�rego napraw� rozpatrujemy
	int currentIndex = index;
	// Index rodzica elementu pod indexem CurrentIndex
	int parentIndex = floor((currentIndex - 1) / 2);
	// Przypisanie warto�ci elementom
	int currentElement = *(binaryHeap + currentIndex);
	int parentElement = *(binaryHeap + parentIndex);

	// P�tla naprawiaj�ca - zamieniaj�ca miejscami warto�ci w razie potrzeby
	while(parentIndex >= 0)
	{
		// Ustalanie warto�ci element�w pod danymi indexami
		parentElement = *(binaryHeap + parentIndex);
		currentElement = *(binaryHeap + currentIndex);
		// Je�eli rodzic jest mniejszy od syna, nastepuje zamiana miejscami
		if (parentElement < currentElement)
		{

			*(binaryHeap + parentIndex) = currentElement;
			*(binaryHeap + currentIndex) = parentElement;
			// Wyliczanie indexu rodzica
			currentIndex = parentIndex;
			parentIndex = floor((currentIndex - 1) / 2);

		}
		else
			return;
	}

}

// Funkcja ta naprawia kopiec od korzenia w d�

void BinaryHeap::repairHeapDown()
{
	// Index rodzica - domy�lnie korze�
	int parentIndex = 0;
	// Wyliczenie indexu lewego syna
	int leftSonIndex = 2 * parentIndex + 1;
	// Wyliczenie indexu prawego syna
	int rightSonIndex = 2 * parentIndex + 2;
	// Przypisanie warto�ci
	int parent = *binaryHeap;
	int leftSon = *(binaryHeap + leftSonIndex);
	int rightSon = *(binaryHeap + rightSonIndex);
	// P�tla naprawiaj�ca w d�, wykonuj�ca si� dop�ki istnieje jaki kolwiek syn
	while ((leftSonIndex <= elementCounter - 1) || (rightSonIndex <= elementCounter - 1))
	{
		// Przypisanie warto�ci obecnego rodzica
		parent = *(binaryHeap + parentIndex);
		// Przypisanie warto�ci synom - o ile istniej�, je�eli nie to NULL
		if (leftSonIndex <= (elementCounter - 1))
			leftSon = *(binaryHeap + leftSonIndex);
		else
			leftSon = NULL;
		
		if (rightSonIndex <= (elementCounter - 1))
			rightSon = *(binaryHeap + rightSonIndex);
		else
			rightSon = NULL;
		
		// Je�eli prawy syn istnieje i jest wi�kszy od lewego, jest rozpatrywany pod zamiane
		if((rightSon > leftSon ) && (rightSon != NULL))
		{
			// Je�eli rodzic jest mniejszy od prawego syna nast�puje zamiana
			if (parent < rightSon)
			{
				*(binaryHeap + rightSonIndex) = parent;
				*(binaryHeap + parentIndex) = rightSon;
				// Wyliczenie nowych index�w
				parentIndex = rightSonIndex;
				leftSonIndex = 2 * parentIndex + 1;
				rightSonIndex = 2 * parentIndex + 2;
			}
			else
				return;
		}
		else
		{
			// Je�eli lewy syn istnieje i jest wi�kszy od rodzica, nast�puje zamiana
			if ((parent < leftSon) && (leftSon != NULL))
			{
				*(binaryHeap + leftSonIndex) = parent;
				*(binaryHeap + parentIndex) = leftSon;
				// Wyliczenie nowych index�w
				parentIndex = leftSonIndex;
				leftSonIndex = 2 * parentIndex + 1;
				rightSonIndex = 2 * parentIndex + 2;
			}
			else
				return;
		}
	}

}

// Funkcja wy�wietlaj�ca reprezentacje graficzn� kopca - zosta� on skopiowany ze strony -> http://eduinf.waw.pl/inf/alg/001_search/0113.php

void BinaryHeap::displayTree(string sp, string sn, int v)
{
	
	string s;


	if (v < elementCounter)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		displayTree(s + cp, cr, 2 * v + 2);

		s = s.substr(0, sp.length() - 2);

		cout << s << sn << binaryHeap[v] << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		displayTree(s + cp, cl, 2 * v + 1);
		}

}

// Funkcja pomocnicza do wy�wietlania reprezentacji graficznej kopca

void BinaryHeap::displayBinaryHeap()
{
	cr = " ";
	cl = " ";
	cp = "  ";
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;
	displayTree("", "", 0);
}

// Funkcja ta wczytuje dane z pliku

bool BinaryHeap::loadDataFromFile(std::string name)
{

	// Wyczyszczenie obecnego kopca
	clearBinaryHeap();
	// Otwarcie pliku
	ifstream file;
	file.open(name);

	// Sprawdzenie czy plik otwarto z sukcesem
	if (!file.good())
		return false;

	// Pobranie informacji o ilo�ci element�w
	file >> elementCounter;

	// Utworzenie nowego kopca
	// POBRANIE WARTO�CI Z PLIKU POWODUJE UTRAT� OBECNEGO KOPCA!
	binaryHeap = new int[elementCounter];
	// P�tla wczytuj�ca warto�ci z pliku do kopca oraz naprawiaj�ca na bie��co
	for (int i = 0; i < elementCounter; i++)
	{
		if (file.good())
			file >> *(binaryHeap + i);
		repairHeapUp(i);
	}

	return true;
}

// Funkcja sprawdzaj�ca czy podany element znajduje si� w kopcu

bool BinaryHeap::searchElement(int value)
{

	for (int currentElement = 0; currentElement < elementCounter; currentElement++)
	{

		if (*(this->binaryHeap + currentElement) == value)
			return true;

	}
	return false;

}

// Funkcja czy�ci obecny kopiec

void BinaryHeap::clearBinaryHeap()
{
	delete binaryHeap;
}

// Funkcja generuje losow� liczb� z podanego zakresu

int BinaryHeap::generateRandomNumber(int range)
{

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> distFirst(1, range);

	return distFirst(gen);

}


