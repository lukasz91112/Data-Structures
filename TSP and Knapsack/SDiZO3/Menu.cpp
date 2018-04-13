#include "stdafx.h"
#include "Menu.h"
#include <iostream>
#include <string>


using namespace std;

Menu::Menu()
{
	knapsack = NULL;
	bagman = NULL;
	SelectProblem();
}


Menu::~Menu()
{
}

void Menu::SelectProblem()
{
	
	while (true)
	{
		system("cls");
		int choice;
		cout << "Wybierz problem: " << endl << "1. Dyskretny problem plecakowy" << endl << "2. Asymetryczny problem komiwojazera" << endl << "3. Wyjdz" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: 
			KnapsackMenu();
			break;
		case 2:
			BagmanMenu();
			break;
		case 3:
			return;
		}
	}
}

void Menu::KnapsackMenu()
{
	knapsack = new Knapsack();
	while (true)
	{
		system("cls");
		int choice;
		cout << "PROBLEM PLECAKOWY" << endl << endl << "Wybierz akcje: " << endl << "1. Wczytaj plik" << endl << "2. Wygeneruj losowy plik" << endl << "3. Prezentuj algorytmy" << endl << "4. Wyjdz" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			KnapsackLoadFromFile();
			break;
		case 2:
			KnapsackCreateRandom();
			break;
		case 3:
			KnapsackRun();
			break;
		case 4:
			delete knapsack;
			return;
		}
	}
}

void Menu::KnapsackLoadFromFile()
{
	system("cls");
	string filename;
	cout << "Wprowadz nazwe pliku: ";
	cin >> filename;
	if (knapsack->LoadKnapsackFromFile(filename))
		cout << "Wczytano pomyslnie" << endl;
	else
		cout << "Blad wczytywania pliku" << endl;
}

void Menu::KnapsackCreateRandom()
{
	system("cls");
	int numberOfItems = 0;
	int capacity = 0;
	cout << "Wprowadz liczbe przedmiotow: ";
	cin >> numberOfItems;
	cout << endl << "Wprowadz pojemnosc plecaka: ";
	cin >> capacity;
	knapsack->CreateRandomKnapsack(numberOfItems, capacity);
}

void Menu::KnapsackRun()
{
	system("cls");
	BruteForceKnapsack::Run(knapsack);
	GreedyKnapsack::RunByDensity(knapsack);
	GreedyKnapsack::RunByValue(knapsack);
	system("PAUSE");
}

void Menu::BagmanMenu()
{
	bagman = new Bagman();
	while (true)
	{
		system("cls");
		int choice;
		cout << "PROBLEM KOMIWOJAZERA" << endl << endl << "Wybierz akcje: " << endl << "1. Wczytaj plik" << endl << "2. Wygeneruj losowy plik" << endl << "3. Prezentuj algorytmy" << endl << "4. Wyjdz" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			BagmanLoadFromFile();
			break;
		case 2:
			BagmanCreateRandom();
			break;
		case 3:
			BagmanRun();
			break;
		case 4:
			delete bagman;
			return;
		}
	}
}

void Menu::BagmanLoadFromFile()
{
	system("cls");
	string filename;
	cout << "Wprowadz nazwe pliku: ";
	cin >> filename;
	if (bagman->LoadMapFromFile(filename))
		cout << "Wczytano pomyslnie" << endl;
	else
	{
		cout << "Blad wczytywania pliku" << endl;
		system("PAUSE");
	}
}

void Menu::BagmanCreateRandom()
{
	system("cls");
	int numberOfCities = 0;
	cout << "Wprowadz liczbe miast: ";
	cin >> numberOfCities;
	bagman->CreateRandomBagman(numberOfCities);
}

void Menu::BagmanRun()
{
	system("cls");
	BruteForceBagman::RunBagman(bagman);
	GreedyBagman::Run(bagman);
	system("PAUSE");
}
