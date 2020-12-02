#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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

uint32_t Star1(std::vector<std::string>* entries)
{
	uint32_t goodPasswords = 0;

	for (size_t i = 0; i < entries->size(); ++i)
	{
		size_t start = 0;
		size_t end = entries->at(i).find(" ");
		std::string numOfLetters = entries->at(i).substr(start, end);

		start = end + 1;
		end = entries->at(i).find(" ", start + 1);
		std::string letter = entries->at(i).substr(start, end);

		start = end + 1;
		std::string password = entries->at(i).substr(start);

		start = 0;
		end = numOfLetters.find("-", start + 1);
		std::string temp = numOfLetters.substr(start, end);
		uint32_t min = static_cast<uint32_t>(std::stoul(temp));

		start = end + 1;
		temp = numOfLetters.substr(start);
		uint32_t max = static_cast<uint32_t>(std::stoul(temp));

		char letterToCheck = letter[0];

		uint32_t counter = 0;
		for (size_t j = 0; j < password.size(); ++j)
		{
			if (password[j] == letterToCheck)
				++counter;
		}

		if (counter >= min && counter <= max)
			++goodPasswords;
	}

	return goodPasswords;
}

uint32_t Star2(std::vector<std::string>* entries)
{
	uint32_t goodPasswords = 0;

	for (size_t i = 0; i < entries->size(); ++i)
	{
		size_t start = 0;
		size_t end = entries->at(i).find(" ");
		std::string numOfLetters = entries->at(i).substr(start, end);

		start = end + 1;
		end = entries->at(i).find(" ", start + 1);
		std::string letter = entries->at(i).substr(start, end);

		start = end + 1;
		std::string password = entries->at(i).substr(start);

		start = 0;
		end = numOfLetters.find("-", start + 1);
		std::string temp = numOfLetters.substr(start, end);
		uint32_t first = static_cast<uint32_t>(std::stoul(temp));

		start = end + 1;
		temp = numOfLetters.substr(start);
		uint32_t second = static_cast<uint32_t>(std::stoul(temp));

		char letterToCheck = letter[0];

		if ((password[first - 1] == letterToCheck && password[second - 1] != letterToCheck) || (password[first - 1] != letterToCheck && password[second - 1] == letterToCheck))
			++goodPasswords;
	}

	return goodPasswords;
}

int main()
{
	std::vector <std::string>* passwords = LoadFile("2.txt");

	std::cout << "Star1: " << Star1(passwords) << std::endl;
	std::cout << "Star2: " << Star2(passwords) << std::endl;

	delete passwords;

	return 0;
}