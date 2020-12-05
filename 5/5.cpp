#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string>* LoadFile(std::string fileName)
{
	std::vector<std::string>* boardingPasses = new std::vector<std::string>();

	std::fstream input;
	input.open(fileName, std::fstream::in);
	std::string fileLine;

	while (std::getline(input, fileLine))
	{
		boardingPasses->push_back(fileLine);

	}
	input.close();

	return boardingPasses;
}

uint32_t Star1(std::vector<std::string>* boardingPasses)
{
	uint32_t highestID = 0;

	for (size_t i = 0; i < boardingPasses->size(); i++)
	{
		uint32_t row, column, id;

		uint32_t start = 0, end = 127;
		for (size_t j = 0; j < boardingPasses->at(i).size() - 3; j++)
		{
			if (boardingPasses->at(i)[j] == 'B')
			{
				start = start + (end - start + 1) / 2;
			}
			else // F
			{
				end = start + (end - start + 1) / 2;
			}
		}
		row = start;

		start = 0, end = 7;
		for (size_t j = boardingPasses->at(i).size() - 3; j < boardingPasses->at(i).size(); j++)
		{
			if (boardingPasses->at(i)[j] == 'R')
			{
				start = start + (end - start + 1) / 2;
			}
			else // L
			{
				end = start + (end - start + 1) / 2;
			}
		}
		column = start;

		id = 8 * row + column;
		if (id > highestID)
			highestID = id;
	}

	return highestID;
}



uint32_t Star2(std::vector<std::string>* boardingPasses)
{
	uint32_t myID = 0;
	uint32_t planeSeats[128][8] = {0};

	for (size_t i = 0; i < boardingPasses->size(); i++)
	{
		uint32_t row, column, id;

		uint32_t start = 0, end = 127;
		for (size_t j = 0; j < boardingPasses->at(i).size() - 3; j++)
		{
			if (boardingPasses->at(i)[j] == 'B')
			{
				start = start + (end - start + 1) / 2;
			}
			else // F
			{
				end = start + (end - start + 1) / 2;
			}
		}
		row = start;

		start = 0, end = 7;
		for (size_t j = boardingPasses->at(i).size() - 3; j < boardingPasses->at(i).size(); j++)
		{
			if (boardingPasses->at(i)[j] == 'R')
			{
				start = start + (end - start + 1) / 2;
			}
			else // L
			{
				end = start + (end - start + 1) / 2;
			}
		}
		column = start;

		planeSeats[row][column] = 8 * row + column;
	}

	uint32_t startRow;

	bool stop = false;
	for (size_t i = 0; i < 128; ++i)
	{
		for (size_t j = 0; j < 8; ++j)
		{
			if (planeSeats[i][j] != 0)
			{
				startRow = i;
				stop = true;
				break;
			}
		}

		if (stop)
			break;
	}

	for (size_t i = startRow + 1; i < 128; ++i)
	{
		for (size_t j = 0; j < 8; ++j)
		{
			if (planeSeats[i][j] == 0)
			{
				return myID = 8 * i + j;
			}
		}
	}

	return myID;
}

int main()
{
	std::vector <std::string>* boardingPasses = LoadFile("5.txt");

	std::cout << "Star1: " << Star1(boardingPasses) << std::endl;
	std::cout << "Star2: " << Star2(boardingPasses) << std::endl;

	delete boardingPasses;

	return 0;
}