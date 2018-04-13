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

// Funkcja ta dodaje element o podanej wartoœci jako liœæ a nastêpnie naprawia drzewo do góry

void BinaryHeap::addElement(int newElement)
{

	// Utworzenie tablicowej reprezentacji kopca
	int *newHeap = new int[elementCounter + 1];

	// Przypisanie liœciowi wartoœci elementu
	*(newHeap + elementCounter) = newElement;

	// Relokacja kopca
	memcpy(newHeap, binaryHeap, 4 * elementCounter);

	// Zwolnienie pamiêci po starym kopcu
	if (binaryHeap != NULL)
		delete binaryHeap;

	// Aktualizacja adresu kopca
	binaryHeap = newHeap;
	// Zwiêkszenie licznika elementów
	elementCounter++;

	// Je¿eli dodany element nie jest pierwszym nastêpuje naprawa kopca
	if (elementCounter > 1)
		repairHeapUp(elementCounter - 1);
	
}

// Funkcja ta usuwa korzeñ kopca

void BinaryHeap::deleteElement()
{

	// Przypisanie ostatniego liœcia jako korzeñ kopca
	*(binaryHeap) = *(binaryHeap + elementCounter - 1);

	// Utworzenie nowego kopca, o zmniejszonej liczbie elementów
	int *newHeap = new int[elementCounter - 1];

	// Relokacja kopca
	memcpy(newHeap, binaryHeap, 4 * (elementCounter - 1));
	
	// Zwolnienie pamiêci po starym kopcu
	if (binaryHeap != NULL)
		delete binaryHeap;

	// Aktualizacja adresu kopca
	binaryHeap = newHeap;	

	// Zmniejszenie licznika elementów
	elementCounter--;

	// Naprawa kopca w dó³
	repairHeapDown();

}

// Funkcja ta generuje losowy kopiec

void BinaryHeap::generateRandomBinaryHeap(int numberOfElements)
{

	clearBinaryHeap();
	// Wczytanie iloœci elementów oraz utworzenie kopca o zadanych rozmiarach
	elementCounter = numberOfElements;
	binaryHeap = new int[numberOfElements];

	//Pêtla zape³niaj¹ca kopiec losowymi wartoœciami oraz naprawiaj¹ca go na bie¿¹co
	for (int i = 0; i < numberOfElements; i++)
	{

		*(binaryHeap + i) = generateRandomNumber(1000000);
		repairHeapUp(i);

	}
}

// Funkcja ta naprawia kopiec do góry od wskazanej pozycji

void BinaryHeap::repairHeapUp(int index)
{

	// currentIndex - index elementu którego naprawê rozpatrujemy
	int currentIndex = index;
	// Index rodzica elementu pod indexem CurrentIndex
	int parentIndex = floor((currentIndex - 1) / 2);
	// Przypisanie wartoœci elementom
	int currentElement = *(binaryHeap + currentIndex);
	int parentElement = *(binaryHeap + parentIndex);

	// Pêtla naprawiaj¹ca - zamieniaj¹ca miejscami wartoœci w razie potrzeby
	while(parentIndex >= 0)
	{
		// Ustalanie wartoœci elementów pod danymi indexami
		parentElement = *(binaryHeap + parentIndex);
		currentElement = *(binaryHeap + currentIndex);
		// Je¿eli rodzic jest mniejszy od syna, nastepuje zamiana miejscami
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

// Funkcja ta naprawia kopiec od korzenia w dó³

void BinaryHeap::repairHeapDown()
{
	// Index rodzica - domyœlnie korzeñ
	int parentIndex = 0;
	// Wyliczenie indexu lewego syna
	int leftSonIndex = 2 * parentIndex + 1;
	// Wyliczenie indexu prawego syna
	int rightSonIndex = 2 * parentIndex + 2;
	// Przypisanie wartoœci
	int parent = *binaryHeap;
	int leftSon = *(binaryHeap + leftSonIndex);
	int rightSon = *(binaryHeap + rightSonIndex);
	// Pêtla naprawiaj¹ca w dó³, wykonuj¹ca siê dopóki istnieje jaki kolwiek syn
	while ((leftSonIndex <= elementCounter - 1) || (rightSonIndex <= elementCounter - 1))
	{
		// Przypisanie wartoœci obecnego rodzica
		parent = *(binaryHeap + parentIndex);
		// Przypisanie wartoœci synom - o ile istniej¹, je¿eli nie to NULL
		if (leftSonIndex <= (elementCounter - 1))
			leftSon = *(binaryHeap + leftSonIndex);
		else
			leftSon = NULL;
		
		if (rightSonIndex <= (elementCounter - 1))
			rightSon = *(binaryHeap + rightSonIndex);
		else
			rightSon = NULL;
		
		// Je¿eli prawy syn istnieje i jest wiêkszy od lewego, jest rozpatrywany pod zamiane
		if((rightSon > leftSon ) && (rightSon != NULL))
		{
			// Je¿eli rodzic jest mniejszy od prawego syna nastêpuje zamiana
			if (parent < rightSon)
			{
				*(binaryHeap + rightSonIndex) = parent;
				*(binaryHeap + parentIndex) = rightSon;
				// Wyliczenie nowych indexów
				parentIndex = rightSonIndex;
				leftSonIndex = 2 * parentIndex + 1;
				rightSonIndex = 2 * parentIndex + 2;
			}
			else
				return;
		}
		else
		{
			// Je¿eli lewy syn istnieje i jest wiêkszy od rodzica, nastêpuje zamiana
			if ((parent < leftSon) && (leftSon != NULL))
			{
				*(binaryHeap + leftSonIndex) = parent;
				*(binaryHeap + parentIndex) = leftSon;
				// Wyliczenie nowych indexów
				parentIndex = leftSonIndex;
				leftSonIndex = 2 * parentIndex + 1;
				rightSonIndex = 2 * parentIndex + 2;
			}
			else
				return;
		}
	}

}

// Funkcja wyœwietlaj¹ca reprezentacje graficzn¹ kopca - zosta³ on skopiowany ze strony -> http://eduinf.waw.pl/inf/alg/001_search/0113.php

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

// Funkcja pomocnicza do wyœwietlania reprezentacji graficznej kopca

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

	// Pobranie informacji o iloœci elementów
	file >> elementCounter;

	// Utworzenie nowego kopca
	// POBRANIE WARTOŒCI Z PLIKU POWODUJE UTRATÊ OBECNEGO KOPCA!
	binaryHeap = new int[elementCounter];
	// Pêtla wczytuj¹ca wartoœci z pliku do kopca oraz naprawiaj¹ca na bie¿¹co
	for (int i = 0; i < elementCounter; i++)
	{
		if (file.good())
			file >> *(binaryHeap + i);
		repairHeapUp(i);
	}

	return true;
}

// Funkcja sprawdzaj¹ca czy podany element znajduje siê w kopcu

bool BinaryHeap::searchElement(int value)
{

	for (int currentElement = 0; currentElement < elementCounter; currentElement++)
	{

		if (*(this->binaryHeap + currentElement) == value)
			return true;

	}
	return false;

}

// Funkcja czyœci obecny kopiec

void BinaryHeap::clearBinaryHeap()
{
	delete binaryHeap;
}

// Funkcja generuje losow¹ liczbê z podanego zakresu

int BinaryHeap::generateRandomNumber(int range)
{

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> distFirst(1, range);

	return distFirst(gen);

}


