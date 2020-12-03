#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Coordinates
{
	uint32_t x;
	uint32_t y;
};

struct PossibleWays
{
	uint32_t right;
	uint32_t down;
};

std::vector<std::string>* LoadFile(std::string fileName)
{
	std::vector<std::string>* entries = new std::vector<std::string>();

	std::fstream input;
	input.open(fileName, std::fstream::in);
	std::string fileLine;

	while (std::getline(input, fileLine))
	{
		entries->push_back(fileLine);
	}
	input.close();

	return entries;
}

uint32_t Star1(std::vector<std::string>* area)
{
	uint32_t numOfTrees = 0;
	Coordinates coordinates{
		0, // x
		0 // y
	};

	while (coordinates.y != area->size() - 1)
	{
		uint32_t tempX = coordinates.x;
		tempX += 3;

		if (tempX > area->at(coordinates.y).size() - 1)
			tempX -= area->at(coordinates.y).size();

		coordinates.x = tempX;
		coordinates.y += 1;

		if (area->at(coordinates.y)[coordinates.x] == '#')
			++numOfTrees;
	}

	return numOfTrees;
}

uint32_t Star2(std::vector<std::string>* area)
{
	PossibleWays possibleWays[] = {
		{
			1, // right
			1 // down
		},
		{
			3, // right
			1 // down
		},
		{
			5, // right
			1 // down
		},
		{
			7, // right
			1 // down
		},
		{
			1, // right
			2 // down
		},
	};

	uint32_t answer = 1;

	for (size_t i = 0; i < 5; ++i) // 5 -> possibleWays size
	{
		uint32_t numOfTrees = 0;
		Coordinates coordinates{
			0, // x
			0 // y
		};

		while (coordinates.y != area->size() - 1)
		{
			uint32_t tempX = coordinates.x;
			tempX += possibleWays[i].right;

			if (tempX > area->at(coordinates.y).size() - 1)
				tempX -= area->at(coordinates.y).size();

			coordinates.x = tempX;
			coordinates.y += possibleWays[i].down;

			if (area->at(coordinates.y)[coordinates.x] == '#')
				++numOfTrees;
		}

		answer *= numOfTrees;
	}

	return answer;
}

int main()
{
	std::vector <std::string>* area = LoadFile("3.txt");

	std::cout << "Star1: " << Star1(area) << std::endl;
	std::cout << "Star2: " << Star2(area) << std::endl;

	delete area;

	return 0;
}