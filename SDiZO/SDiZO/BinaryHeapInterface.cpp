#include "stdafx.h"
#include "BinaryHeapInterface.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>

using namespace std;

BinaryHeapInterface::BinaryHeapInterface()
{
	binaryHeapMenu();
}


BinaryHeapInterface::~BinaryHeapInterface()
{
}

// Menu g³ówne kopca

void BinaryHeapInterface::binaryHeapMenu()
{
	int choice;
	while (true)
	{
		cout << "---- LISTA ----" << endl;
		cout << "Wybierz operacje: " << endl;
		cout << " 1. Wczytaj dane z pliku" << endl;
		cout << " 2. Dodaj element " << endl;
		cout << " 3. Usun element" << endl;
		cout << " 4. Wyszukaj element" << endl;
		cout << " 5. Wygeneruj losowa liste" << endl;
		cout << " 6. Wyswietl liste" << endl;
		cout << " 7. Testuj" << endl;
		cout << " 8. Wroc do menu glownego" << endl;

		cin >> choice;

		switch (choice)
		{

		case 1:
			loadDataFromFile();
			break;

		case 2:
			addElement();
			break;

		case 3:
			deleteElement();
			break;

		case 4:
			searchElement();
			break;

		case 5:
			generateRandomBinaryHeap();
			break;

		case 6:
			displayBinaryHeap();
			break;

		case 7:
			testBinaryHeap();
			break;
		case 8:
			delete binaryHeap;
			return;
			break;
		}
	}
}

// Dodawanie elementu

void BinaryHeapInterface::addElement()
{
	int value;
	
	system("cls");
	cout << "Podaj wartosc: " << endl;
	cin >> value;
	binaryHeap->addElement(value);
	system("cls");

}

// Usuwanie elementu

void BinaryHeapInterface::deleteElement()
{
	system("cls");
	if(binaryHeap->elementCounter > 0)
		binaryHeap->deleteElement();
}

// Wczytywanie danych z pliku

void BinaryHeapInterface::loadDataFromFile()
{
	string name;

	system("cls");
	cout << "Wprowadz nazwe pliku (nazwa_pliku.txt): ";
	cin >> name;
	system("cls");
	binaryHeap->loadDataFromFile(name);
	system("cls");
}

// Generowanie losowego kopca

void BinaryHeapInterface::generateRandomBinaryHeap()
{
	int numberOfElements;

	system("cls");
	cout << "Podaj liczbe elementow: " << endl;
	cin >> numberOfElements;
	binaryHeap->generateRandomBinaryHeap(numberOfElements);
	system("cls");

}

// Wyœwietlanie kopca

void BinaryHeapInterface::displayBinaryHeap()
{

	system("cls");
	binaryHeap->displayBinaryHeap();
	system("PAUSE");
	system("cls");

}

// Wyszukiwanie elementu

void BinaryHeapInterface::searchElement()
{
	int value;

	system("cls");
	cout << "Podaj wartosc szukanego elementu: " << endl;
	cin >> value;
	if (binaryHeap->searchElement(value))
		cout << "Podany element znajduje sie w tablicy" << endl;
	else
		cout << "Podany element nie znajduje sie w tablicy" << endl;
	system("PAUSE");
	system("cls");

}

// Menu testowania kopca

void BinaryHeapInterface::testBinaryHeap()
{
	system("cls");
	int choice = 0;
	int sizeOfPopulation = 0;
	int numberOfTrials = 0;

	while (true)
	{
		cout << "Wybierz opcje: " << endl;
		cout << " 1. Ustaw liczbe elementow" << endl;
		cout << " 2. Ustaw rozmiar populacji" << endl;
		cout << " 3. Przeprowadz test dodawania" << endl;
		cout << " 4. Przeprowadz test usuwania" << endl;
		cout << " 5. Przeprowadz test wyszukiwania" << endl;
		cout << " 6. Powrot" << endl;
		cout << "Populacja: " << sizeOfPopulation << endl;
		cout << "Liczba prob: " << numberOfTrials << endl;

		cin >> choice;

		switch (choice)
		{

		case 1:
			system("cls");
			cout << "Wprowadz liczbe elementow: ";
			cin >> numberOfTrials;
			system("cls");
			break;

		case 2:
			system("cls");
			cout << "Wprowadz rozmiar";
			cin >> sizeOfPopulation;
			system("cls");
			break;

		case 3:
			system("cls");
			test();
			//testAddBinaryHeap(numberOfTrials, sizeOfPopulation);
			break;

		case 4:
			system("cls");
			testDeleteBinaryHeap(numberOfTrials, sizeOfPopulation);
			break;

		case 5:
			system("cls");
			testSearchBinaryHeap(numberOfTrials, sizeOfPopulation);
			break;

		case 6:
			system("cls");
			return;
			break;

		}
	}
}

// Testowanie dodawania

void BinaryHeapInterface::testAddBinaryHeap(int numberOfTrials, int sizeOfPopulation)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	int tempElement = 0;
	string name = "Binary Heap Test Add ";
	char *trialName = new char[3];
	char *sizeName = new char[5];
	sprintf(trialName, "%d", numberOfTrials);
	sprintf(sizeName, "%d", sizeOfPopulation);
	name.append(trialName);
	name.append("x");
	name.append(sizeName);
	name.append(".txt");

	fstream file;
	file.open(name, ios::out | ios::app);

	for (int currentTrial = 0; currentTrial < numberOfTrials; currentTrial++)
	{

		binaryHeap->generateRandomBinaryHeap(sizeOfPopulation);
		tempElement = binaryHeap->generateRandomNumber(1000000);
		start = read_QPC();
		binaryHeap->addElement(tempElement);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie usuwania

void BinaryHeapInterface::testDeleteBinaryHeap(int numberOfTrials, int sizeOfPopulation)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	string name = "Binary Heap Test Delete ";
	char *trialName = new char[3];
	char *sizeName = new char[5];
	sprintf(trialName, "%d", numberOfTrials);
	sprintf(sizeName, "%d", sizeOfPopulation);
	name.append(trialName);
	name.append("x");
	name.append(sizeName);
	name.append(".txt");

	fstream file;
	file.open(name, ios::out | ios::app);

	for (int currentTrial = 0; currentTrial < numberOfTrials; currentTrial++)
	{

		binaryHeap->generateRandomBinaryHeap(sizeOfPopulation);
		start = read_QPC();
		binaryHeap->deleteElement();
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie wyszukiwania

void BinaryHeapInterface::testSearchBinaryHeap(int numberOfTrials, int sizeOfPopulation)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	string name = "Binary Heap Test Search ";
	char *trialName = new char[3];
	char *sizeName = new char[5];
	sprintf(trialName, "%d", numberOfTrials);
	sprintf(sizeName, "%d", sizeOfPopulation);
	name.append(trialName);
	name.append("x");
	name.append(sizeName);
	name.append(".txt");
	fstream file;
	file.open(name, ios::out | ios::app);

	int tempElement;
	int tempIndex;

	for (int currentTrial = 0; currentTrial < numberOfTrials; currentTrial++)
	{

		binaryHeap->generateRandomBinaryHeap(sizeOfPopulation);
		tempIndex = binaryHeap->generateRandomNumber(sizeOfPopulation-1);
		tempElement = *(binaryHeap->binaryHeap + tempIndex);
		start = read_QPC();
		binaryHeap->searchElement(tempElement);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Pobieranie aktualnego czasu

long long int BinaryHeapInterface::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}

void BinaryHeapInterface::test()
{
	int populationSize = 1000;


	for (int i = 0; i < 6; i++)
	{
		testAddBinaryHeap(100, populationSize);
		if (populationSize == 1000)
			populationSize = 40000;
		else
			populationSize += 40000;
	}
	populationSize = 1000;
	for (int i = 0; i < 6; i++)
	{
		testDeleteBinaryHeap(100, populationSize);
		if (populationSize == 1000)
			populationSize = 40000;
		else
			populationSize += 40000;
	}
	populationSize = 1000;
	for (int i = 0; i < 6; i++)
	{
		testSearchBinaryHeap(100, populationSize);
		if (populationSize == 1000)
			populationSize = 40000;
		else
			populationSize += 40000;
	}
}