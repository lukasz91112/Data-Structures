#include "stdafx.h"
#include "Interface.h"
#include "ArrayInterface.h"
#include "ListInterface.h"
#include "BinaryHeapInterface.h"
#include "Array.h"
#include <iostream>





using namespace std;

// Utworzenie tablicy oraz wyœwietlenie menu g³ównego

Interface::Interface()
{
	this->mainMenu();
}

// Destruktor

Interface::~Interface()
{
	
}

// Menu g³ówne programu - Wybór struktury

void Interface:: mainMenu()
{
	int choice;
	while (true)
	{
		cout << "Wybierz strukture danych: " << endl;
		cout << " 1. Tablica " << endl;
		cout << " 2. Lista " << endl;
		cout << " 3. Kopiec " << endl;

		cin >> choice;

		switch (choice)
		{

		case 1:
			system("cls");
			new ArrayInterface();
			break;

		case 2:
			system("cls");
			new ListInterface();
			break;

		case 3:
			system("cls");
			new BinaryHeapInterface();
			break;
		}
		system("cls");
	}
	
}








