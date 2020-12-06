#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

std::vector<std::vector<std::string>>* LoadFile(std::string fileName)
{
	std::vector<std::vector<std::string>>* answers = new std::vector<std::vector<std::string>>();

	std::fstream input;
	input.open(fileName, std::fstream::in);
	std::string fileLine;
	
	std::vector<std::string> tempGroup;
	while (std::getline(input, fileLine))
	{
		if (fileLine == "")
		{
			answers->push_back(tempGroup);
			tempGroup.clear();
		}
		else
		{
			tempGroup.push_back(fileLine);
		}
	}
	answers->push_back(tempGroup);

	input.close();

	return answers;
}

uint32_t Star1(std::vector<std::vector<std::string>>* answers)
{
	uint32_t sum = 0;

	for (auto group : *answers)
	{
		std::set <char> tempGroup;

		for (auto person : group)
		{
			for (auto answer : person)
				if (tempGroup.find(answer) == tempGroup.end())
					tempGroup.insert(answer);
		}

		sum += tempGroup.size();
	}

	return sum;
}

uint32_t Star2(std::vector<std::vector<std::string>>* answers)
{
	uint32_t sum = 0;

	for (auto group : *answers)
	{
		std::map <char, uint32_t> tempGroup;

		for (auto person : group)
		{
			if (group.size() == 1)
			{
				sum += person.size();
				break;
			}

			for (auto answer : person)
				if (tempGroup.find(answer) == tempGroup.end())
					tempGroup.insert(std::pair <char, uint32_t> {answer, 1});
				else
				{
					tempGroup[answer] += 1;
					if (tempGroup[answer] == group.size())
						++sum;
				}
		}
	}

	return sum;
}

int main()
{
	std::vector <std::vector<std::string>>* answers = LoadFile("6.txt");

	std::cout << "Star1: " << Star1(answers) << std::endl;
	std::cout << "Star2: " << Star2(answers) << std::endl;

	delete answers;

	return 0;
}