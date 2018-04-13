#include "stdafx.h"
#include "ListInterface.h"
#include "List.h"
#include "Array.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

ListInterface::ListInterface()
{
	list = new List();
	listMenu();
}


ListInterface::~ListInterface()
{
}

// Menu listy

void ListInterface::listMenu()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "---- LISTA ----" << endl;
		cout << "Wybierz operacje: " << endl;
		cout << " 1. Wczytaj dane z pliku" << endl;
		cout << " 2. Dodaj element " << endl;
		cout << " 3. Usun element" << endl;
		cout << " 4. Wyszukaj element" << endl;
		cout << " 5. Wygeneruj losowa liste" << endl;
		cout << " 6. Wyswietl liste" << endl;
		cout << " 7. Testuj" << endl;
		cout << " 8. Powrot do menu g³ownego" << endl;

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
			generateRandomList();
			break;

		case 6:
			displayList();
			break;

		case 7:
			testList();
			break;

		case 8:
			delete list;
			system("cls");
			return;
			break;

		}
	}
}

// Funkcja dodaj¹ca nowy element

void ListInterface::addElement()
{
	
	int index;
	int newElement;
	int choice;

	system("cls");
	cout << " 1.Dodaj element na pocz¹tku" << endl;
	cout << " 2.Dodaj element na koñcu" << endl;
	cout << " 3.Dodaj pod wskazane miejsce" << endl;

	cin >> choice;

	switch (choice)
	{

	case 1:

		system("cls");
		cout << "Podaj wartosc: ";
		cin >> newElement;
		list->addFirstElement(newElement);
		system("cls");
		break;

	case 2:

		system("cls");
		cout << "Podaj wartosc: ";
		cin >> newElement;
		list->addLastElement(newElement);
		system("cls");
		break;

	case 3:

		system("cls");
		cout << "Podaj index: " << endl;
		cin >> index;
		if ((index < ((list->elementCounter)) && (index >= 0)))
		{
			cout << "Podaj wartosc: " << endl;
			cin >> newElement;
			list->addElement(newElement, index);
		}
		else
			cout << "Podano b³êdny index" << endl;
		system("cls");
		break;

	}
}

// Funkcja usuwaj¹ca element

void ListInterface::deleteElement()
{

	int index;
	int choice;

	system("cls");
	cout << " 1.Usun element na pocz¹tku" << endl;
	cout << " 2.Usun element na koñcu" << endl;
	cout << " 3.Usun z wskazanego miejsca" << endl;

	cin >> choice;

	switch (choice)
	{

	case 1:

		list->deleteFirstElement();
		system("cls");
		break;

	case 2:

		list->deleteLastElement();
		system("cls");
		break;

	case 3:

		system("cls");
		cout << "Podaj index: " << endl;
		cin >> index;
		if ((index < list->elementCounter) && (index >= 0))
			list->deleteElement(index);
		else
		{
			cout << "Podano b³êdny index" << endl;
			system("PAUSE");
		}
		system("cls");
		break;

	}

}

// Funkcja wczytuj¹ca dane z pliku

void ListInterface::loadDataFromFile()
{

	string name;

	system("cls");
	cout << "Wprowadz nazwe pliku (nazwa_pliku.txt): ";
	cin >> name;
	system("cls");
	list->loadDataFromFile(name);
	system("cls");

}

// Funkcja generuj¹ca losow¹ listê

void ListInterface::generateRandomList()
{
	int numberOfElements;

	system("cls");
	cout << "Wprowadz liczbe elementow : ";
	cin >> numberOfElements;
	list->generateRandomList(numberOfElements, 1000000);
	system("cls");
}

// Funkcja wyœwietlaj¹ce obecn¹ listê

void ListInterface::displayList()
{
	system("cls");
	list->displayList();
	cout << endl;
	system("PAUSE");
	system("cls");
}

// Funkcja wyszukuj¹ca dany element

void ListInterface::searchElement()
{
	int value;
	bool result;

	system("cls");
	cout << "Podaj wartosc poszukiwanego elementu: ";
	cin >> value;
	result = list->searchElement(value);
	if (result)
		cout << "Podany element znajduje siê w tablicy" << endl;
	else
		cout << "Nie znaleziono podanego elementu" << endl;
	system("PAUSE");
	system("cls");
}

// Menu testowania

void ListInterface::testList()
{
	system("cls");
	int choice = 0;
	int numberOfTrials = 0;
	int sizeOfPopulation = 0;

	cout << "Wybierz opcje: " << endl;
	cout << " 1. Ustaw liczbe elementow" << endl;
	cout << " 2. Ustaw rozmiar populacji" << endl;
	cout << " 3. Przeprowadz test dodawania" << endl;
	cout << " 4. Przeprowadz test usuwania" << endl;
	cout << " 5. Przeprowadz test wyszukiwania" << endl;
	cout << " 6. Powrót" << endl;
	cout << "Populacja: " << sizeOfPopulation << endl;
	cout << "Próby: " << numberOfTrials << endl;

	cin >> choice;

	while (true)
	{
		switch (choice)
		{

		case 1:
			system("cls");
			cout << "Wprowadz liczbe prób: ";
			cin >> numberOfTrials;
			system("cls");
			testList();
			break;

		case 2:
			system("cls");
			cout << "Wprowadz rozmiar";
			cin >> sizeOfPopulation;
			system("cls");
			testList();
			break;

		case 3:
			system("cls");
			listTestAdd(numberOfTrials, sizeOfPopulation);
			break;

		case 4:
			system("cls");
			listTestDelete(numberOfTrials, sizeOfPopulation);
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

void ListInterface::listTestAdd(int numberOfTrials, int sizeOfPopulation)
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
		testAddRandom(numberOfTrials, sizeOfPopulation);
		system("cls");
		break;

	case 2:
		testAddFirst(numberOfTrials, sizeOfPopulation);
		system("cls");
		break;

	case 3:
		testAddLast(numberOfTrials, sizeOfPopulation);
		system("cls");
		break;

	}
}

// Menu testowania usuwania

void ListInterface::listTestDelete(int numberOfTrials, int sizeOfPopulation)
{
	int choice = 0;

	cout << "Skad dane maja byc usuwane?" << endl;
	cout << " 1. Z losowych miejsc" << endl;
	cout << " 2. Z poczatku" << endl;
	cout << " 3. Z konca" << endl;

	cin >> choice;

	switch (choice)
	{

	case 1:
		testDeleteRandom(numberOfTrials, sizeOfPopulation);
		system("cls");
		break;

	case 2:
		testDeleteFirst(numberOfTrials, sizeOfPopulation);
		system("cls");
		break;

	case 3:
		testDeleteLast(numberOfTrials, sizeOfPopulation);
		system("cls");
		break;

	}
}

// Testowanie dodawania na poczatku

void ListInterface::testAddFirst(int numberOfTrials, int sizeOfPopulation)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	int tempElement = 0;
	string name = "List Test Add First ";
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

		list->generateRandomList(sizeOfPopulation, 1000000);
		tempElement = list->generateRandomNumber(1000000);
		start = read_QPC();
		list->addFirstElement(tempElement);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie dodawania na koncu

void ListInterface::testAddLast(int numberOfTrials, int sizeOfPopulation)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	int tempElement = 0;
	string name = "List Test Add Last ";
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

		list->generateRandomList(sizeOfPopulation, 1000000);
		tempElement = list->generateRandomNumber(1000000);
		start = read_QPC();
		list->addLastElement(tempElement);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie dodawania w losowe miejsce

void ListInterface::testAddRandom(int numberOfTrials, int sizeOfPopulation)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	int tempElement = 0;
	int tempIndex = 0;
	string name = "List Test Add Random ";
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

		list->generateRandomList(sizeOfPopulation, 1000000);
		tempElement = list->generateRandomNumber(1000000);
		tempIndex = list->generateRandomNumber(sizeOfPopulation - 1);
		start = read_QPC();
		list->addElement(tempElement, tempIndex);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie usuwania pierwszego elementu

void ListInterface::testDeleteFirst(int numberOfTrials, int sizeOfPopulation)
{
	string name = "Liste Test Delete First ";
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

		list->generateRandomList(sizeOfPopulation, 1000000);
		start = read_QPC();
		list->deleteFirstElement();
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie usuwania ostatniego elementu

void ListInterface::testDeleteLast(int numberOfTrials, int sizeOfPopulation)
{
	string name = "Liste Test Delete Last ";
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

		list->generateRandomList(sizeOfPopulation, 1000000);
		start = read_QPC();
		list->deleteLastElement();
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie usuwania losowego elementu 

void ListInterface::testDeleteRandom(int numberOfTrials, int sizeOfPopulation)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	int tempIndex = 0;
	string name = "List Test Delete Random ";
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

		list->generateRandomList(sizeOfPopulation, 1000000);
		tempIndex = list->generateRandomNumber(sizeOfPopulation - 1);
		start = read_QPC();
		list->deleteElement(tempIndex);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Testowanie wyszukiwania elementu

void ListInterface::testSearch(int numberOfTrials, int sizeOfPopulation)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	string name = "List Test Search ";
	
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

		list->generateRandomList(sizeOfPopulation, 1000000);
		tempIndex = list->generateRandomNumber(sizeOfPopulation - 1);
		tempElement = list->goToIndex(tempIndex);
		start = read_QPC();
		list->searchElement(tempElement);
		elapsed = read_QPC() - start;
		if (file.good() == true)
		{
			file << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;
		}

	}
	file.close();

}

// Funkcja odczytu zegara

long long int ListInterface::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}

