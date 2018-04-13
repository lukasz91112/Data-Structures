#include "stdafx.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include "MatrixGraph.h"


using namespace std;

Menu::Menu()
{
	while (true)
	{
		system("cls");
		int choice;
		cout << "Wybierz reprezentacje grafu: " << endl;
		cout << "0. Macierz" << endl;
		cout << "1. Listy" << endl;
		cout << "2. Wyjscie" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			MatrixMenu();
			break;
		case 1:
			ListMenu();
			break;
		case 2:
			return;
		}
	}

}


Menu::~Menu()
{
}

void Menu::MatrixMenu()
{
	matrixGraph = new MatrixGraph();
	int choice;
	while (true)
	{			
		system("cls");
		cout << "Co chcesz zrobic? " << endl;
		cout << "0. Wczytaj graf z pliku " << endl;
		cout << "1. Wygeneruj losowy graf" << endl;
		cout << "2. Wyswietl graf" << endl;
		cout << "3. Algorytm Prim" << endl;
		cout << "4. Algorytm Kurskala " << endl;
		cout << "5. Algorytm Dijkstry " << endl;
		cout << "6. Algorytm Bellmana-Forda " << endl;
		cout << "7. Wyjscie " << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			MatrixLoadFromFile();
			break;
		case 1:
			MatrixGenerateRandom();
			break;
		case 2:
			MatrixDisplayGraph();
			break;
		case 3:
			MatrixPrimAlgorithm();
			break;
		case 4:
			MatrixKruskalAlgorithm();
			break;
		case 5:
			MatrixDijkstraAlgorithm();
			break;
		case 6:
			MatrixBellmanFordAlgorithm();
			break;
		case 7:
			delete matrixGraph;
			return;
		}
	}

}

void Menu::MatrixLoadFromFile()
{
	delete matrixGraph;
	matrixGraph = new MatrixGraph();
	system("cls");
	string filename;
	cout << "Podaj nazwe pliku" << endl;
	cin >> filename;
	matrixGraph->LoadGraphFromFile(filename);
	matrixGraph->DisplayGraph();
	system("PAUSE");
	system("cls");
}

void Menu::MatrixGenerateRandom()
{
	delete matrixGraph;
	matrixGraph = new MatrixGraph();
	int choice;
	int numberOfVertexes;
	float density = 2;
	while (true)
	{
		system("cls");		
		cout << "0. Wygeneruj graf skierowany" << endl;
		cout << "1. Wygeneruj graf nieskierowany" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			system("cls");
			cout << "Podaj liczbe wierzcholkow: ";
			cin >> numberOfVertexes;
			while (density < 0 || density > 1)
			{
				cout << endl << "Podaj gestosc (Liczba z przedzialu od 0 do 1): ";
				cin >> density;
			}
			matrixGraph->GenerateRandomDirectedGraph(numberOfVertexes, density);
			system("cls");
			return;
		case 1:
			system("cls");
			cout << "Podaj liczbe wierzcholkow: ";
			cin >> numberOfVertexes;
			while (density < 0 || density > 1)
			{
				cout << endl << "Podaj gestosc (Liczba z przedzialu od 0 do 1): ";
				cin >> density;
			}
			matrixGraph->GenerateRandomNoDirectedGraph(numberOfVertexes, density);
			system("cls");
			return;
		}
	}
}

void Menu::MatrixDisplayGraph()
{
	system("cls");
	matrixGraph->DisplayGraph();
	system("PAUSE");
	system("cls");
}

void Menu::MatrixPrimAlgorithm()
{
	system("cls");
	prim = new Prim();
	prim->RunMatrix(matrixGraph->MakeNoDirected(), matrixGraph->numberOfVertexes);
	prim->DisplayMstSolution();
	system("PAUSE");
	delete prim;
	system("cls");
}

void Menu::MatrixKruskalAlgorithm()
{
	system("cls");
	kruskal = new Kruskal();
	kruskal->RunMatrix(matrixGraph->MakeNoDirected(), matrixGraph->numberOfVertexes);
	kruskal->DisplayMstSolution();
	system("PAUSE");
	delete kruskal;
	system("cls");
}

void Menu::MatrixDijkstraAlgorithm()
{
	system("cls");
	dijkstra = new Dijkstra();
	dijkstra->RunMatrix(matrixGraph->matrix, matrixGraph->numberOfVertexes, matrixGraph->startVertex);
	dijkstra->DisplaySolution();
	system("PAUSE");
	delete dijkstra;
	system("cls");
}

void Menu::MatrixBellmanFordAlgorithm()
{
	system("cls");
	bellmanFord = new BellmanFord();
	bellmanFord->RunMatrix(matrixGraph->matrix, matrixGraph->numberOfVertexes, matrixGraph->startVertex);
	bellmanFord->DisplaySolution();
	system("PAUSE");
	delete bellmanFord;
	system("cls");
}

void Menu::ListMenu()
{
	listGraph = new ListGraph();
	int choice;
	while (true)
	{
		system("cls");
		cout << "Co chcesz zrobic? " << endl;
		cout << "0. Wczytaj graf z pliku " << endl;
		cout << "1. Wygeneruj losowy graf" << endl;
		cout << "2. Wyswietl graf" << endl;
		cout << "3. Algorytm Prim" << endl;
		cout << "4. Algorytm Kurskala " << endl;
		cout << "5. Algorytm Dijkstry " << endl;
		cout << "6. Algorytm Bellmana-Forda " << endl;
		cout << "7. Wyjscie " << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			ListLoadFromFile();
			break;
		case 1:
			ListGenerateRandom();
			break;
		case 2:
			ListDisplayGraph();
			break;
		case 3:
			ListPrimAlgorithm();
			break;
		case 4:
			ListKruskalAlgorithm();
			break;
		case 5:
			ListDijkstraAlgorithm();
			break;
		case 6:
			ListBellmanFordAlgorithm();
			break;
		case 7:
			delete listGraph;
			return;
		}
	}

}

void Menu::ListLoadFromFile()
{
	delete listGraph;
	listGraph = new ListGraph();
	system("cls");
	string filename;
	cout << "Podaj nazwe pliku" << endl;
	cin >> filename;
	listGraph->LoadGraphFromFile(filename);
	listGraph->DisplayGraph();
	system("PAUSE");
	system("cls");
}

void Menu::ListGenerateRandom()
{
	delete listGraph;
	listGraph = new ListGraph();
	int choice;
	int numberOfVertexes;
	float density = 2;
	while (true)
	{
		system("cls");
		cout << "0. Wygeneruj graf skierowany" << endl;
		cout << "1. Wygeneruj graf nieskierowany" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			system("cls");
			cout << "Podaj liczbe wierzcholkow: ";
			cin >> numberOfVertexes;
			while (density < 0 || density > 1)
			{
				cout << endl << "Podaj gestosc (Liczba z przedzialu od 0 do 1): ";
				cin >> density;
			}
			listGraph->GenerateRandomDirectedGraph(numberOfVertexes, density);
			system("cls");
			return;
		case 1:
			system("cls");
			cout << "Podaj liczbe wierzcholkow: ";
			cin >> numberOfVertexes;
			while (density < 0 || density > 1)
			{
				cout << endl << "Podaj gestosc (Liczba z przedzialu od 0 do 1): ";
				cin >> density;
			}
			listGraph->GenerateRandomNoDirectedGraph(numberOfVertexes, density);
			system("cls");
			return;
		}
	}
}

void Menu::ListDisplayGraph()
{
	system("cls");
	listGraph->DisplayGraph();
	system("PAUSE");
	system("cls");
}

void Menu::ListPrimAlgorithm()
{
	system("cls");
	prim = new Prim();
	prim->RunList(listGraph->MakeNoDirected(), listGraph->numberOfVertexes);
	prim->DisplayMstSolution();
	system("PAUSE");
	delete prim;
	system("cls");
}

void Menu::ListKruskalAlgorithm()
{
	system("cls");
	kruskal = new Kruskal();
	kruskal->RunList(listGraph->MakeNoDirected(), listGraph->numberOfVertexes);
	kruskal->DisplayMstSolution();
	system("PAUSE");
	delete kruskal;
	system("cls");
}

void Menu::ListDijkstraAlgorithm()
{
	system("cls");
	dijkstra = new Dijkstra();
	dijkstra->RunList(listGraph->graphList, listGraph->numberOfVertexes, listGraph->startVertex);
	dijkstra->DisplaySolution();
	system("PAUSE");
	delete dijkstra;
	system("cls");
}

void Menu::ListBellmanFordAlgorithm()
{
	system("cls");
	bellmanFord = new BellmanFord();
	if (!bellmanFord->RunList(listGraph->graphList, listGraph->numberOfVertexes, listGraph->startVertex))
		cout << "Graf zawiera cykl ujemny!" << endl;
	bellmanFord->DisplaySolution();
	system("PAUSE");
	delete bellmanFord;
	system("cls");
}
