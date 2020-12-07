#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == std::string::npos) pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		tokens.push_back(token);

		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

std::map<std::string, std::map<std::string, uint32_t>>* LoadFile(std::string fileName)
{
	std::map<std::string, std::map<std::string, uint32_t>>* rules = new std::map<std::string, std::map<std::string, uint32_t>>();

	std::fstream input;
	input.open(fileName, std::fstream::in);
	std::string fileLine;

	while (std::getline(input, fileLine))
	{
		// Parsing every line from file
		std::map<std::string, uint32_t> containBagsMap;

		std::string bag = split(fileLine, " bags contain")[0];

		std::string temp = split(fileLine, " contain ")[1];

		std::vector<std::string> containBags = split(temp, ", ");

		for (size_t i = 0; i < containBags.size(); ++i)
		{
			std::string temp = split(containBags[i], " bag")[0];

			if (temp.find("no other") != std::string::npos)
			{
				containBagsMap.insert(std::pair <std::string, uint32_t> {"no other", 0});
			}
			else
			{
				std::vector <std::string> tempVector = split(temp, " ");

				containBagsMap.insert(std::pair <std::string, uint32_t> {tempVector[1] + " " + tempVector[2], std::stol(tempVector[0])});
			}
		}

		rules->insert(std::pair <std::string, std::map<std::string, uint32_t>> {bag, containBagsMap});
	}
	input.close();

	return rules;
}

bool SearchForShinyGoldBag(std::string bagToCheck, std::map<std::string, std::map<std::string, uint32_t>>& rules)
{
	if (rules[bagToCheck].find("no other") != rules[bagToCheck].end())
		return false;

	for (auto rule : rules[bagToCheck])
	{
		if (rule.first == "shiny gold")
			return true;
		else
		{
			bool temp = SearchForShinyGoldBag(rule.first, rules);
			if (temp)
				return true;
		}
	}

	return false;
}

uint32_t Star1(std::map<std::string, std::map<std::string, uint32_t>>* rules)
{
	uint32_t shinyBagCount = 0;

	for (auto rule : *rules)
	{
		if (rule.first == "shiny gold")
		{
			continue;
		}
		else
		{
			if (SearchForShinyGoldBag(rule.first, *rules))
				++shinyBagCount;
		}
	}

	return shinyBagCount;
}

uint32_t CountBags(std::string bagToCheck, std::map<std::string, std::map<std::string, uint32_t>>& rules)
{
	uint32_t count = 0;

	if (rules[bagToCheck].find("no other") != rules[bagToCheck].end())
		return 0;

	for (auto rule : rules[bagToCheck])
	{
		count += rule.second + rule.second * CountBags(rule.first, rules);
	}

	return count;
}

uint32_t Star2(std::map<std::string, std::map<std::string, uint32_t>>* rules)
{
	uint32_t individualBagsCount = 0;

	for (auto rule : (*rules)["shiny gold"])
	{
		individualBagsCount += rule.second + rule.second * CountBags(rule.first, *rules);
	}

	return individualBagsCount;
}

int main()
{
	std::map<std::string, std::map<std::string, uint32_t>>* rules = LoadFile("7.txt");

	std::cout << "Star1: " << Star1(rules) << std::endl;
	std::cout << "Star2: " << Star2(rules) << std::endl;

	delete rules;

	return 0;
}