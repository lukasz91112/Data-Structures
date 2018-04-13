#pragma once
#include <string>
class Bagman
{
public:
	Bagman();
	~Bagman();
	const int range_of_weight = 20;
	int **map;
	int numberOfCities;
	void CreateRandomBagman(int numberOfCities);
	bool LoadMapFromFile(std::string filename);
	void DisplayMap();
private:
	void ClearMap();	
};

