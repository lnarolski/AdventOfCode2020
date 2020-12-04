#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string>* LoadFile(std::string fileName)
{
	std::vector<std::string>* passports = new std::vector<std::string>();

	std::fstream input;
	input.open(fileName, std::fstream::in);
	std::string fileLine;
	std::string temp;

	while (std::getline(input, fileLine))
	{
		if (fileLine == "")
		{
			passports->push_back(temp);
			temp = "";
		}
		else
		{
			temp += fileLine + "\n";
		}
			
	}
	input.close();

	passports->push_back(temp);

	return passports;
}

uint32_t Star1(std::vector<std::string>* passports)
{
	uint32_t validPasports = 0;

	std::string fields[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

	for (size_t i = 0; i < passports->size(); ++i)
	{
		bool valid = true;
		for (std::string field : fields)
		{
			if (passports->at(i).find(field) == std::string::npos)
			{
				valid = false;
				break;
			}
		}

		if (valid)
			++validPasports;
	}

	return validPasports;
}



uint32_t Star2(std::vector<std::string>* passports)
{
	uint32_t validPasports = 0;

	std::string fields[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

	for (size_t i = 0; i < passports->size(); ++i)
	{
		bool valid = true;

		for (std::string field : fields)
		{
			std::string temp = "";
			size_t start;
			size_t end;

			size_t position = passports->at(i).find(field);
			if (position == std::string::npos)
			{
				valid = false;
				break;
			}
			else
			{
				if (field == "byr")
				{
					start = position + 4;
					end = passports->at(i).find(" ", start) - 1;

				}
				else if (field == "iyr")
				{

				}
				else if (field == "eyr")
				{

				}
				else if (field == "hgt")
				{

				}
				else if (field == "hcl")
				{

				}
				else if (field == "ecl")
				{

				}
				else if (field == "pid")
				{

				}
			}
		}

		if (valid)
			++validPasports;
	}

	return validPasports;
}

int main()
{
	std::vector <std::string>* passports = LoadFile("4.txt");

	std::cout << "Star1: " << Star1(passports) << std::endl;
	//std::cout << "Star2: " << Star2(area) << std::endl;

	delete passports;

	return 0;
}