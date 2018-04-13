#include "stdafx.h"
#include "ArrayInterface.h"
#include "ListInterface.h"
#include "BinaryHeapInterface.h"
#include "Array.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <random>
#include <iomanip>
#include <windows.h>

using namespace std;

ArrayInterface::ArrayInterface()
{
	array = new Array();
	arrayMenu();
	PCFreq = 0.0;
	CounterStart = 0;
}


ArrayInterface::~ArrayInterface()
{
}

// Menu tablicy

void ArrayInterface::arrayMenu()
{
	int choice;
	while (true)
	{
		cout << "---- TABLICA ----" << endl;
		cout << "Wybierz operacje: " << endl;
		cout << " 1. Wczytaj dane z pliku" << endl;
		cout << " 2. Dodaj element " << endl;
		cout << " 3. Usun element" << endl;
		cout << " 4. Wyszukaj element" << endl;
		cout << " 5. Wygeneruj losowa tablice" << endl;
		cout << " 6. Wyswietl tablice" << endl;
		cout << " 7. Testuj" << endl;
		cout << " 8. Menu glowne programu" << endl;

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
			generateRandomArray();
			break;

		case 6:
			displayArray();
			break;

		case 7:
			testArray();
			break;

		case 8:
			delete array;
			system("cls");
			return;
			break;

		}
	}
}

// Dodawanie elementu

void ArrayInterface::addElement()
{

	int index;
	int newElement;
	int choice;

	system("cls");
	cout << " 1.Dodaj element na poczatku" << endl;
	cout << " 2.Dodaj element na koncu" << endl;
	cout << " 3.Dodaj pod wskazane miejsce" << endl;

	cin >> choice;

	switch (choice)
	{

	case 1:

		system("cls");
		cout << "Podaj wartosc: ";
		cin >> newElement;
		array->addFirstElement(newElement);
		system("cls");
		break;

	case 2:

		system("cls");
		cout << "Podaj wartosc: ";
		cin >> newElement;
		array->addLastElement(newElement);
		system("cls");
		break;

	case 3:

		system("cls");
		cout << "Podaj index: " << endl;
		cin >> index;
		cout << "Podaj wartosc: " << endl;
		cin >> newElement;
		array->addElement(index, newElement);
		system("cls");
		break;

	}

}

// Usuwanie elementu

void ArrayInterface::deleteElement()
{

	int index;
	int choice;

	system("cls");
	cout << " 1.Usun element na poczatku" << endl;
	cout << " 2.Usun element na koncu" << endl;
	cout << " 3.Usun z wskazanego miejsca" << endl;

	cin >> choice;

	switch (choice)
	{

	case 1:

		array->deleteFirstElement();
		system("cls");
		break;

	case 2:

		array->deleteLastElement();
		system("cls");
		break;

	case 3:

		system("cls");
		cout << "Podaj index: " << endl;
		cin >> index;
		array->deleteElement(index);
		system("cls");
		break;

	}

}

// Szukanie elementu

void ArrayInterface::searchElement()
{

	int value;

	system("cls");
	cout << "Podaj wartosc poszukiwanego elementu: ";
	cin >> value;
	system("cls");
	if (array->searchElement(value))
	{
		cout << "Podana liczba wystepuje w tablicy" << endl;
	}
	else
	{
		cout << "Podana liczba nie wystepuje w tablicy" << endl;
	}
	system("PAUSE");
	system("cls");

}

// Wczytywanie danych z pliku

void ArrayInterface::loadDataFromFile()
{

	string name;

	system("cls");
	cout << "Wprowadz nazwe pliku (nazwa_pliku.txt): ";
	cin >> name;
	system("cls");
	array->loadDataFromFile(name);
	system("cls");

}

// Wyœwietlanie tablicy

void ArrayInterface::displayArray()
{

	system("cls");
	array->displayArray();
	cout << endl;
	system("PAUSE");
	system("cls");

}

// Generowanie losowej tablicy

void ArrayInterface::generateRandomArray()
{

	int numberOfElements;

	system("cls");
	cout << "Wprowadz liczbe elementow : ";
	cin >> numberOfElements;
	array->generateRandomArray(numberOfElements, 1000000);
	system("cls");

}

// Menu testowania tablicy

void ArrayInterface::testArray()
{

	system("cls");
	int choice = 0;
	int numberOfTrials = 0;
	int sizeOfPopulation = 0;
	while (true)
	{
		cout << "Wybierz opcje: " << endl;
		cout << " 1. Ustaw liczbe prób" << endl;
		cout << " 2. Ustaw rozmiar populacji" << endl;
		cout << " 3. Przeprowadz test dodawania" << endl;
		cout << " 4. Przeprowadz test usuwania" << endl;
		cout << " 5. Przeprowadz test wyszukiwania" << endl;
		cout << " 6. Powrót do menu tablicy" << endl;
		cout << "Populacja: " << sizeOfPopulation << endl;
		cout << "Próby: " << numberOfTrials << endl;

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
			arrayTestAdd(numberOfTrials, sizeOfPopulation);
			break;

		case 4:
			system("cls");
			arrayTestDelete(numberOfTrials, sizeOfPopulation);
			break;

		case 5:
			system("cls");
			testSearch(numberOfTrials, sizeOfPopulation);
			break;

		case 6:
			system("cls");
			return;
			break;

		}
	}

}

// Menu testowania dodawania

void ArrayInterface::arrayTestAdd(int numberOfTrials, int sizeOfPopulation)
{

	int choice = 0;

	cout << "Gdzie dane maja byc dodawane?" << endl;
	cout << " 1. W losowe miejsca" << endl;
	cout << " 2. Na poczatku" << endl;
	cout << " 3. Na koncu" << endl;

	cin >> choice;

	switch (choice)
	{

	case 1:
		system("cls");
		testAddRandom(numberOfTrials, sizeOfPopulation);
		break;

	case 2:
		system("cls");
		testAddFirst(numberOfTrials, sizeOfPopulation);
		break;

	case 3:
		system("cls");
		testAddLast(numberOfTrials, sizeOfPopulation);
		break;

	}

}

// Menu testowania usuwania

void ArrayInterface::arrayTestDelete(int numberOfTrials, int sizeOfPopulation)
{

	int choice = 0;

	cout << "Gdzie dane maja byc usuwane?" << endl;
	cout << " 1. Z losowych miejsc" << endl;
	cout << " 2. Z poczatku" << endl;
	cout << " 3. Z konca" << endl;

	cin >> choice;

	switch (choice)
	{

	case 1:
		testDeleteRandom(numberOfTrials, sizeOfPopulation);
		break;

	case 2:
		testDeleteFirst(numberOfTrials, sizeOfPopulation);
		break;

	case 3:
		system("cls");
		testDeleteLast(numberOfTrials, sizeOfPopulation);
		break;

	}

}

// Testowanie dodawania na koñcu

void ArrayInterface::testAddLast(int numberOfTrials, int sizeOfPopulation)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	int tempElement = 0;
	string name = "Array Test Add Last";
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

		array->generateRandomArray(sizeOfPopulation, 1000000);
		tempElement = generateRandomNumber(1000000);

		start = read_QPC();
		array->addLastElement(tempElement);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie dodawania na pocz¹tku

void ArrayInterface::testAddFirst(int numberOfTrials, int sizeOfPopulation)
{

	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	int tempElement = 0;
	string name = "Array Test Add First";
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

		array->generateRandomArray(sizeOfPopulation, 1000000);
		tempElement = generateRandomNumber(1000000);
		start = read_QPC();
		array->addFirstElement(tempElement);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie dodawania w losowe miejsce

void ArrayInterface::testAddRandom(int numberOfTrials, int sizeOfPopulation)
{

	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	int tempElement = 0;
	int tempIndex = 0;
	string name = "Array Test Add Random ";
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

		array->generateRandomArray(sizeOfPopulation, 1000000);
		tempElement = generateRandomNumber(1000000);
		tempIndex = generateRandomNumber(sizeOfPopulation - 1);
		start = read_QPC();
		array->addElement(tempIndex, tempElement);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie usuwania z koñca

void ArrayInterface::testDeleteLast(int numberOfTrials, int sizeOfPopulation)
{

	string name = "Array Test Delete Last";
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

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

		array->generateRandomArray(sizeOfPopulation, 1000000);
		start = read_QPC();
		array->deleteLastElement();
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie usuwania z pocz¹tku

void ArrayInterface::testDeleteFirst(int numberOfTrials, int sizeOfPopulation)
{

	string name = "Array Test Delete First";
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

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

		array->generateRandomArray(sizeOfPopulation, 1000000);
		start = read_QPC();
		array->deleteFirstElement();
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie usuwania z losowych miejsc

void ArrayInterface::testDeleteRandom(int numberOfTrials, int sizeOfPopulation)
{

	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	int tempIndex = 0;
	string name = "Array Test Delete Random";

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

		array->generateRandomArray(sizeOfPopulation, 1000000);
		tempIndex = generateRandomNumber(sizeOfPopulation - 1);
		start = read_QPC();
		array->deleteElement(tempIndex);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie wyszukiwania

void ArrayInterface::testSearch(int numberOfTrials, int sizeOfPopulation)
{

	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	string name = "Array Test Search";

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
		
		array->generateRandomArray(sizeOfPopulation, 1000);
		tempIndex = generateRandomNumber(sizeOfPopulation - 1);
		tempElement = *(array->array + tempIndex);
		start = read_QPC();
		array->searchElement(tempElement);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	
	file.close();

}

// Odczyt zegara

long long int ArrayInterface::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);

}



// Generowanie losowej liczby z zadanego zakresu

int ArrayInterface::generateRandomNumber(int range)
{

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> distFirst(0, range);

	return distFirst(gen);

}

// Generowanie losowej liczby (na potrzeby testów)
int ArrayInterface::generateRandomNumberTest(int range)
{

	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> distFirst(floor(range/2), range);

	return distFirst(gen);

}

